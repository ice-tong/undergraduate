/*
 * Project1.c
 *
 * Created: 1/18/2019 7:50:43 PM
 * Author : Kian Farsany
 */ 

#include <avr/io.h>
#include "avr.c"

void wait_half() {
	volatile int i,n = 17000;
	
	for (i = 0; i < n; ++i) {
		//blah
	}
}

int main(void)
{
	DDRB = 1;
    while (1) 
    {
		if (GET_BIT(PINB, 1) == 0) {
			PORTB = 1;
			//wait_half();
			wait_avr(500);
			PORTB = 0;
			//wait_half();
			wait_avr(500);
		}
		else {
			PORTB = 0;
		}
    }
}

