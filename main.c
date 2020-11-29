#include <msp.h>
#include <stdint.h>
#include "state_machine.h"
#include "uart.h"

// Define UART ASCII vals for state transitions
#define UART_NEXT_STATE 0x30 // chose 0x30 to indicate next state
#define UART_PREV_STATE 0x31 // chose0x31 to indicate previous state
#define UART_CURR_STATE 0x32 // chose 0x32 to represent request for current state

// initialize state machine
sm_instance sm;

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



void EUSCIA0_IRQHandler(void){
	if (EUSCI_A0->IFG & UCTXIFG){
		EUSCI_A0->IFG &= ~UCTXIFG; // clear interrupt flag
		// Sent Succesful!
	}
	if (EUSCI_A0->IFG & UCRXIFG){
		EUSCI_A0->IFG &= ~UCRXIFG;
		transmit("hello World\0"); // Echo back
	}
}


int main(){
	// Enable gloabl interrupts for ISR's
	__ASM("CPSIE I") ;
	
	// INITIALIZE UART0, 115200 BAUD RATE, EVEN BIT PARITY
	init_uart0_pins();
	init_uart0();
	init_uart0_interrupts();
	
	// Initialize buttons and LED's
	init_switches();
	init_LED_rgb();
	init_LED_red();
	
	// create state machine instance
	 sm = sm_init();
	
	while(1){
	}
	return 1;
}
