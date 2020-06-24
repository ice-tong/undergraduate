#include "avr.h"

void
wait_avr(float msec)
{
	TCCR0 = 3;
	while (msec > 0) {
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 64) * 0.0001);
		SET_BIT(TIFR, TOV0);
		while (!GET_BIT(TIFR, TOV0));
		msec -= 0.1;
	}
	TCCR0 = 0;
}