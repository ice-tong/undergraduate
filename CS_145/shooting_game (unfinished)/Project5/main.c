/*
 * Project5.c
 *
 * Created: 3/7/2019 2:59:31 PM
 * Author : Kian
 */ 

#include <avr/io.h>
#include "avr.c"
#include "keypad.c"
#include "lcd.c"

#define BULLET 4
#define BOMB 8
#define CHANGE 1

#define SPEED 25


struct enemy {
	int health;
	int row;
	int column;
};


void play_note(int ammo) {
	float TH; 
	float duration;
	if (ammo == BULLET) {
		TH = (1.0 / 880) * 1000;
		duration = 1;
	}
	else if(ammo == BOMB) {
		TH = (1.0 / 440) * 1000;
		duration = 2;
	}
	float TL = TH;
	
	float i;
	for (i = 0; i < duration; i += 0.1) {
		SET_BIT(PORTA, 1);
		wait_avr(TH);
		CLR_BIT(PORTA, 1);
		wait_avr(TL);
	}
}

void fire(int position, int ammo) {
	CLR_BIT(PORTA, 0);
	play_note(ammo);
	for (int i = 1; i < 16; ++i) {
		lcd_pos(position,i);
		if (ammo == BULLET) {
			wait_avr(SPEED);
			lcd_puts2("-");
		}
		else if (ammo == BOMB) {
			wait_avr(SPEED*2);
			lcd_puts2("o");
		}	
			
		if (i >= 2) {
			lcd_pos(position,i-1);
			lcd_puts2(" ");
		}
		if (i == 15) {
			lcd_pos(position,15);
			lcd_puts2(" ");
		}
	}
	SET_BIT(PORTA, 0);
}

int change_row(int position) {
	lcd_pos(position,0);
	wait_avr(200);
	lcd_puts2(" ");
	return (!position);
}

void print_enemy(struct enemy * baddie) {
	if (baddie->column != 15) {
		lcd_pos(baddie->row, baddie->column + 1);
		lcd_puts2(" ");
	}
	lcd_pos(baddie->row, baddie->column);
	char s[10];
	sprintf(s, "%01d", baddie->health);
	lcd_puts2(s);
}

void move_enemy(struct enemy * baddie) {
	--baddie->column;
}

int main(void)
{
	DDRA = 0x03;
	lcd_init();
	int position = 0;
	struct enemy baddie = {5,0,15};
    while (1) 
    {
		SET_BIT(PORTA,0);
		
		print_enemy(&baddie);
		if (get_key() == CHANGE) {
			position = change_row(position);
		}
		lcd_pos(position,0);
		lcd_puts2("~");
		
		int ammo = get_key();
		if (ammo == BULLET) {
			fire(position, BULLET);
		}
		else if (ammo == BOMB) {
			fire(position, BOMB);
		}
		move_enemy(&baddie);
    }
}

