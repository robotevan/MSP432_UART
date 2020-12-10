#include <msp.h>
#include <stdint.h>
#include "gpio_functions.h"
#include "state_machine.h"
#include "uart.h"

// Define UART ASCII vals for state transitions
#define UART_NEXT_STATE 'a'// chose 0x30 to indicate next state
#define UART_PREV_STATE 'b' // chose0x31 to indicate previous state
#define UART_CURR_STATE 'c' // chose 0x32 to represent request for current state

// initialize state machine
struct state_machine sm;

/*
void PORT1_IRQHandler(void) // ISR for port 1
{
	if((P1IFG & NEXT_STATE_BUTTON) != 0){ // if next state button is clicked
		P1IFG &= ~NEXT_STATE_BUTTON; // Clear the flag bit
		sm_trigger(sm, EVT_FORWARDS); // advance to next state in sm
	}else if((P1IFG & PREVIOUS_STATE_BUTTON) != 0){// if switch 4 is clicked
		P1IFG &= ~PREVIOUS_STATE_BUTTON; // Clear the flag bit
		sm_trigger(sm, EVT_FORWARDS); // advance to next state in sm
	}
}

*/

void EUSCIA0_IRQHandler(void){
	if (EUSCI_A0->IFG & UCRXIFG){
		EUSCI_A0->IFG &= ~UCRXIFG;
		if (EUSCI_A0->RXBUF == UART_NEXT_STATE){
			sm_trigger(&sm, EVT_FORWARDS);
			transmit("done!\0");
		}else if (EUSCI_A0->RXBUF == UART_PREV_STATE){
			sm_trigger(&sm, EVT_BACKWARDS);
		}
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
	
	// create state machine instance
	init_sm(&sm);
	// Enable all interrupts once initial setup is done
	init_uart0_interrupts();
	init_switch_interrupts();
	__ASM("CPSIE I") ;
	while(1){
	}
	return 1;
}
