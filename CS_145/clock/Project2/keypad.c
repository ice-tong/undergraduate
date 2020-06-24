#include "avr.h"
#include "keypad.h"

int pressed(int r, int c) {
	PORTC = 0;
	avr_wait(1);
	DDRC = 0;
	avr_wait(1);
	
	SET_BIT(DDRC, c);
	avr_wait(1);
	CLR_BIT(PORTC, c);
	avr_wait(1);
	
	SET_BIT(PORTC, r+4);
	avr_wait(1);
	if (GET_BIT(PINC, r+4))
	return 0;

	return 1;
}

int get_key() {
	int r, c;
	for (r = 0; r < 4; ++r) {
		for (c = 0; c < 4; ++c) {
			if (pressed(c,r))
			return 1 + (r*4) + c;
		}
	}
	return 0;
}