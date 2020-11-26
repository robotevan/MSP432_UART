#ifndef UART0_DRIVER_H
#include <msp.h>
#include <stdint.h>
#include <stdlib.h>

#define UART0RXPIN (1<<2)  // pin 2 port 1
#define UART0TXPIN (1<<3)  // pin 3 port 1

void init_uart0_pins(void);
void init_uart0(void);
void init_uart0_interrupts(void);
void transmit(uint8_t msg);

#endif
