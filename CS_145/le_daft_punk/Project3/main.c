/*
 * Project3.c
 *
 * Created: 2/13/2019 8:10:16 PM
 * Author : Kian
 */ 

#include <avr/io.h>
#include "avr.c"
#include "lcd.c"
#include "keypad.c"

#define W   40
#define H   (W/2)
#define Q   (H/2)
#define EI  (Q/2)
#define S   (EI/2)


#define GL  415

#define A   440
#define As  466
#define B   494
#define C   523
#define Cs  554
#define D   587
#define Ds  622
#define E   659
#define F   698
#define Fs  740
#define G   784
#define Gs  834

#define AH  880
#define AsH 932
#define BH  988

#define PAUSE 1

#define STOP 4

struct note {
	int freq;
	float duration;
	};
	
	const struct note DA_FUNK[] = {
			{G,H*1.1}, {F,EI}, {G,EI}, {AsH,EI}, {Ds,H*1.3},
			{Cs,EI}, {Ds,EI}, {Fs,EI}, {As,H*1.3},
			{A,EI}, {As,EI}, {Ds,EI}, {GL,H*1.3}, {A,Q}, {As,Q}
			};
			
	const struct note STAR_MAN[] = {
			{F,EI}, {PAUSE,S/4}, {F,EI}, {PAUSE,S/4}, {F,EI}, {D,S}, {F,S},
			{PAUSE,S}, {F,EI}, {D,S}, {F,S}, {D,S}, {F,EI},
			{E,EI}, {PAUSE,S/4}, {E,EI}, {PAUSE,S/4}, {E,EI}, {C,S}, {E,S},
			{PAUSE,S}, {E,EI}, {C,S}, {E,S}, {C,S}, {E,EI}
			};
void play_note(int freq, float duration) {
	if (PAUSE != freq) {
		float TH = (1.0 / freq) * 1000;
		float TL = TH;
		duration = duration + (duration*( 2000*(1.0/GL) - (TL+TH) ) / (TL+TH));
		float i;
		for (i = 0; i < duration; i += 0.1) {
			SET_BIT(PORTA, 0);
			wait_avr(TH);
			CLR_BIT(PORTA, 0);
			wait_avr(TL);
		}
	}
	else
		wait_avr(duration * (1.0/GL) * 20000);
}

int play_song(int key) {
	int i;
	int n;
	
	switch(key) {
		case 1:
			n = sizeof(DA_FUNK)/ sizeof(DA_FUNK[0]);
			for (i = 0; i < n; ++i)
				play_note(DA_FUNK[i].freq, DA_FUNK[i].duration);
			break;
		case 2:
			n = sizeof(STAR_MAN)/ sizeof(STAR_MAN[0]);
			for (i = 0; i < n; ++i)
				play_note(STAR_MAN[i].freq, STAR_MAN[i].duration);
			break;
		default:
			n = sizeof(DA_FUNK)/ sizeof(DA_FUNK[0]);
			for (i = 0; i < n; ++i)
				play_note(DA_FUNK[i].freq, DA_FUNK[i].duration);
			break;
	}
	return 0;
}

void print_song(int key) {
	switch(key) {
		case 1:
			lcd_pos(0,0);
			lcd_puts2("Da Funk");
			lcd_pos(1,0);
			lcd_puts2("by Daft Punk");
			break;
		case 2:
			lcd_pos(0,0);
			lcd_puts2("Star Theme");
			lcd_pos(1,0);
			lcd_puts2("by Nintendo");
			break;
		default:
			lcd_pos(0,0);
			lcd_puts2("Da Funk");
			lcd_pos(1,0);
			lcd_puts2("by Daft Punk");
			break;
	}
}

int main(void)
{
	DDRA = 0x01;
	lcd_init();
    while (1) 
    {
		lcd_pos(0,0);
		lcd_puts2("Press a number");
		lcd_pos(1,0);
		lcd_puts2("to choose a song");
		
		int key = get_key();
		wait_avr(200);
		if (key != 0) {
			while (1) {
				lcd_clr();
				print_song(key);
				play_song(key);
			}
		}
    }
}

