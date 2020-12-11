/*
Code by Evan Pelletier, 101119347
*/

#include <msp.h>
#include <stdint.h>
// Import all my headers
#include "gpio_functions.h"
#include "state_machine.h"
#include "uart.h"

// Define UART ASCII vals for state transitions
#define UART_NEXT_STATE 'a'// char to indicate next state
#define UART_PREV_STATE 'b' // char to indicate previous state


// Define state values to send over uart
static char state_hex_vals[] ={
	'0',
	'1',
	'2',
	'3'
};


// Create State machine
struct state_machine sm;

/*
ISR for buttons
*/
void PORT1_IRQHandler(void){
	if(P1IFG & NEXT_STATE_BUTTON){ // if next state button is clicked
		P1IFG &= ~NEXT_STATE_BUTTON; // Clear the flag bit
		sm_trigger(&sm, EVT_FORWARDS); // advance to next state in sm
	}else if(P1IFG & PREVIOUS_STATE_BUTTON){// if switch 4 is clicked
		P1IFG &= ~PREVIOUS_STATE_BUTTON; // Clear the flag bit
		sm_trigger(&sm, EVT_BACKWARDS); // advance to next state in sm
	}
	transmit(state_hex_vals[sm.curr_state]); // update state on PC side
}

/*
ISR for UART
*/
void EUSCIA0_IRQHandler(void){
	if (EUSCI_A0->IFG & UCRXIFG){ // If a char fills receive buffer
		EUSCI_A0->IFG &= ~UCRXIFG;
		if (EUSCI_A0->RXBUF == UART_NEXT_STATE){ // if next state command incremement state
			sm_trigger(&sm, EVT_FORWARDS);
		}else if (EUSCI_A0->RXBUF == UART_PREV_STATE){ // if prev state go back
			sm_trigger(&sm, EVT_BACKWARDS);
		}
		// sending anything other than next/prev state will just echo back curr state!
		transmit(state_hex_vals[sm.curr_state]); // update state on PC side
	}
}


int main(){
	// Enable gloabl interrupts for ISR's
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;
	
	// INITIALIZE UART0, 115200 BAUD RATE, EVEN BIT PARITY
	init_uart0_pins();
	init_uart0();
	// Initialize buttons and LED's
	init_switches();
	init_LED_rgb();
	init_LED_red();
	set_red_led(0);
	set_rgb_led(0);
	// initialize state machine
	init_sm(&sm);
	
	// Enable all interrupts once initial setup is done
	init_uart0_interrupts();
	init_switch_interrupts();
	__ASM("CPSIE I") ;
	while(1){
	}
	return 1;
}
