#include <msp.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_RGB_COL 256 // MAX COLOUR FOR R G or B
// Define buttons for state transitions
#define NEXT_STATE_BUTTON (1<<1)
#define PREVIOUS_STATE_BUTTON (1<<4)

#define RED_LED (1<<0) // port 1 pin 0
#define RGB_LED_R (1<<0) // port 2 pin 0
#define RGB_LED_G (1<<1) // port 2 pin 1
#define RGB_LED_B (1<<2) // port 2 pin 2


void init_switches(void);
void init_LED_rgb(void);
void init_LED_red(void);
void set_red_led(bool on);
void set_rgb_led(uint8_t r, uint8_t g, uint8_t b); // r = 0, g = 1, b = 2