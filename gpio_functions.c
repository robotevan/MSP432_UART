#include "gpio_functions.h"

void init_switches(void){
	// Set buttons to GPIO mode
	P1SEL0 &= ~(NEXT_STATE_BUTTON | PREVIOUS_STATE_BUTTON);
	P1SEL1 &= ~(NEXT_STATE_BUTTON | PREVIOUS_STATE_BUTTON);
	// Set Buttons to input
	P1DIR &= ~(NEXT_STATE_BUTTON | PREVIOUS_STATE_BUTTON);  // Set Port 1 inputs
	// Use pull up to avoid floating input
	P1REN |= (NEXT_STATE_BUTTON | PREVIOUS_STATE_BUTTON);
	P1OUT |= (NEXT_STATE_BUTTON | PREVIOUS_STATE_BUTTON);
}


void init_LED_rgb(void){
	P2SEL0 &= ~(RGB_LED_R | RGB_LED_G | RGB_LED_B); // set as GPIO
	P2SEL0 &= ~(RGB_LED_R | RGB_LED_G | RGB_LED_B);
	P2DIR |= (RGB_LED_R | RGB_LED_G | RGB_LED_B); // set as output
}

void init_LED_red(void){
	P1SEL0 &= ~(RED_LED); // set as GPIO
	P1SEL1 &= ~(RED_LED);
	P1DIR |= (RED_LED);
	set_red_led(0); // why not reuse function if i wrote it
	set_rgb_led(0);
}


void set_red_led(bool on){
	P1OUT = (uint8_t)0;
	if (on){
		P1OUT |= RED_LED;
	}else{
		P1OUT &= ~RED_LED;
	}
}

void set_rgb_led(uint8_t colour){
	P2OUT = (uint8_t)0;
	if (colour == 0){
		P2OUT = (uint8_t)0;
	}else if (colour == 0){ // set colour to red
		P2OUT |= RGB_LED_R;
	}else if (colour == 1){ // set colour to green
		P2OUT |= RGB_LED_G;
	}else if (colour == 2){ // set colour to blue
		P2OUT |= RGB_LED_B;
	}else{ // if incorrect turn off
		P2OUT = (uint8_t)0;
	}
}

void init_switch_interrupts(void){
	NVIC_SetPriority(PORT1_IRQn, 2); // Set priority of port 1 interrupts
	NVIC_ClearPendingIRQ(PORT1_IRQn); //  Clear pending interrupts for port1
	NVIC_EnableIRQ(PORT1_IRQn); // Enable interrupts for port 1 in nvic
}
