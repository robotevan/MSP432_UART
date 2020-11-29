#include "gpio_functions.h"

void init_switches(void){
	// Set buttons to GPIO mode
	P1SEL0 &= (uint8_t)~(NEXT_STATE_BUTTON | PREVIOUS_STATE_BUTTON);
	P1SEL1 &= (uint8_t)~(NEXT_STATE_BUTTON | PREVIOUS_STATE_BUTTON);
	// Set Buttons to input
	P1DIR &= (uint8_t)~(NEXT_STATE_BUTTON | PREVIOUS_STATE_BUTTON);  // Set Port 1 inputs
	// Use pull up to avoid floating input
	P1REN |= (uint8_t)(NEXT_STATE_BUTTON | PREVIOUS_STATE_BUTTON);
	P1OUT |= (uint8_t)(NEXT_STATE_BUTTON | PREVIOUS_STATE_BUTTON);
}


void init_LED_rgb(void){
	P2SEL0 &= (uint8_t)~(RGB_LED_R | RGB_LED_G | RGB_LED_B); // set as GPIO
	P2SEL0 &= (uint8_t)~(RGB_LED_R | RGB_LED_G | RGB_LED_B);
	P2DIR |= (uint8_t)(RGB_LED_R | RGB_LED_G | RGB_LED_B); // set as output
}

void init_LED_red(void){
	P1SEL0 &= (uint8_t)~(RED_LED); // set as GPIO
	P1SEL1 &= (uint8_t)~(RED_LED);
	P1DIR |= (uint8_t)(RED_LED);
}




void set_rgb_led(uint8_t r, uint8_t g, uint8_t b){
	
	
}
