/*
Code by Evan Pelletier, 101119347
*/

#ifndef GPIO_FUNCTIONS_H
#define GPIO_FUNCTIONS_H
#include <msp.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_RGB_COL 256 // MAX COLOUR FOR R G or B
// Define buttons for state transitions
#define NEXT_STATE_BUTTON (uint8_t)(1<<1)
#define PREVIOUS_STATE_BUTTON (uint8_t)(1<<4)

#define RED_LED (uint8_t)(1<<0) // port 1 pin 0
#define RGB_LED_R (uint8_t)(1<<0) // port 2 pin 0
#define RGB_LED_G (uint8_t)(1<<1) // port 2 pin 1
#define RGB_LED_B (uint8_t)(1<<2) // port 2 pin 2


void init_switch_interrupts(void);
void init_switches(void);
void init_LED_rgb(void);
void init_LED_red(void);
void set_red_led(bool on);
void set_rgb_led(uint8_t colour); // off = 0 r = 1, g = 2, b =3

#endif
