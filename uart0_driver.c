#include "uart0_driver.h"

void init_uart0_pins(){
	// https://training.ti.com/ti-rslk-module-18-lecture-video-part-2-serial-communication-uart?context=1135347-1139309-1135341
	P1SEL0 |= (UART0RXPIN | UART0TXPIN); // 1100
	P1SEL1 &= ~(UART0RXPIN | UART0TXPIN);// 0000 Set pin as UART output
}

void init_uart0(){
	EUSCI_A0->CTLW0 = 0x0000;
	// Enable bit parity, set bit parity to even, select ACLK src clk
	// Enable software reset so baud rate can be changed.
	EUSCI_A0->CTLW0 |= (UCPEN | UCPAR | UCSSEL_2 | UCSWRST);
	EUSCI_A0->BRW = 0x001A;  // = 26      N = CLK_F  / BAUD_RATE   N = 32k/512
	EUSCI_A0->CTLW0 &= ~ UCSWRST; // Disable software reset once baud rate set
}

void init_uart0_interrupts(){
	// Enable interrupts on RX and TX
	EUSCI_A0->IE |= (UCTXIE | UCRXIE);
	NVIC_SetPriority(EUSCIA0_IRQn, 3);
	NVIC_EnableIRQ( EUSCIA0_IRQn );
	NVIC_ClearPendingIRQ(EUSCIA0_IRQn);
	__ASM("CPSIE I") ; // Enable global interrupts
}


void transmit(uint8_t msg){
	while (EUSCI_A0->STATW & UCBUSY); // Wait if busy sending/receiving
	EUSCI_A0->TXBUF = msg;
}

void EUSCIA0_IRQHandler(void){
	if (EUSCI_A0->IFG & UCTXIFG){
		EUSCI_A0->IFG &= ~UCTXIFG; // clear interrupt flag
		// Sent Succesful!
	}
	if (EUSCI_A0->IFG & UCRXIFG){
		EUSCI_A0->IFG &= ~UCRXIFG;
		transmit(EUSCI_A0->RXBUF); // Echo back
	}
}
