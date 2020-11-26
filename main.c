#include "uart0_driver.h"

int main(){
	init_uart0_pins();
	init_uart0();
	init_uart0_interrupts();
	
	
	while(1){
	}
	return 1;
}
