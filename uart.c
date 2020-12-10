#include "uart.h"


/*
Initialize the Tx and Rx pins, Primary Module Function select
*/
void init_uart0_pins(void){
	P1SEL0 |= (uint8_t)(UART0RXPIN | UART0TXPIN);
	P1SEL1 &= (uint8_t)~(UART0RXPIN | UART0TXPIN); 
}


/*
Initialize UART, using even bit parity, SMCLK (3.0MHZ) source clock, 8 bit data mode
*/
void init_uart0(void){
	EUSCI_A0->CTLW0 = 0x0000;
	// Enable bit parity, set bit parity to even, select ACLK src clk
	// Enable software reset so baud rate can be changed.
	EUSCI_A0->CTLW0 |= (UCPEN | UCPAR | UCSSEL_2 | UCSWRST);
	// CHANGE BAUD RATE //
	EUSCI_A0->BRW = 0x0001;  // = INT(26/16)   N = 3MHz / 115200 = 26.041666 / 16 = 1.6276    BRW = 1
	EUSCI_A0->MCTLW |= UCOS16;  // Need to use over sampling 
	EUSCI_A0->MCTLW |= (0x00A0); // set first modulattion stage to 0.16276*16 = 10.0416  UCBRFx = 10
	EUSCI_A0->MCTLW |= (0x0100); // Fractional remaining = 10.0416 - 10 = 0.0416, choose UCBRSx = 0x01 = 0.0529
	EUSCI_A0->CTLW0 &= ~ UCSWRST; // Disable software reset once baud rate set
}

/*
Enable interrupts for UART0, GLOBAL INTERRUPTS NOT ENABLED HERE!
*/
void init_uart0_interrupts(void){
	// Enable interrupts on RX and TX
	EUSCI_A0->IE |= (UCRXIE);
	NVIC_SetPriority(EUSCIA0_IRQn, 3);
	NVIC_EnableIRQ( EUSCIA0_IRQn );
	NVIC_ClearPendingIRQ(EUSCIA0_IRQn);
}

/*
Function to send a string,  takes a char array (null terminated string)
*/
void transmit(char *msg){
	int index;
	for (index = 0; index < strlen(msg); index ++){  // Iterate over every char (charlen = 8bit, same as TXBUF)
		while (!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG)); // Wait fop register to become empty
		EUSCI_A0->IFG &= ~EUSCI_A_IFG_TXIFG; // Reset flag
		EUSCI_A0->TXBUF = msg[index]; // Load char to TXBUF for send
	}
}
