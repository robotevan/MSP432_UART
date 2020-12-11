/*
Code by Evan Pelletier, 101119347
*/

#ifndef UART_H
#define UART_H
#include <msp.h>
#include <stdlib.h>
#include <string.h>

#define UART0RXPIN (1<<2)  // pin 2 port 1
#define UART0TXPIN (1<<3)  // pin 3 port 1

void init_uart0_pins(void);
void init_uart0(void);
void init_uart0_interrupts(void);
void transmit(char msg);

#endif
