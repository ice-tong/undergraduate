/*
 * Project5.c
 *
 * Created: 3/16/2019 1:12:28 PM
 * Author : Kian
 */ 

#include <avr/io.h>
#include "avr.c"
#include "keypad.c"
#include "lcd.c"

#define ENTER    13
#define CLEAR    15
#define ADD      4
#define SUBTRACT 8
#define MULTIPLY  12
#define DIVIDE   16
#define N      20


char buf[N];
int i,j,sz;

void push(char x) {
	buf[i] = x;
	i = (i+1) % N;
	sz++;
}

int pop() {
	char temp = buf[j];
	j = (j+1) % N;
	sz--;
	return temp;
}

void clear() {
	for (int x = 0; x < sz; ++x)
		buf[x] = 0;
	sz = 0;
	i = 0;
	j = 0;
}

void add_char(int key) {
	if (sz == 16)
		return;
	switch(key) {
		case ADD:
			push('+');
			break;
		case SUBTRACT:
			push('-');
			break;
		case MULTIPLY:
			push('*');
			break;
		case DIVIDE:
			push('/');
			break;
		case 1:
			push('1');
			break;
		case 2:
			push('2');
			break;
		case 3:
			push('3');
			break;
		case 5:
			push('4');
			break;
		case 6:
			push('5');
			break;
		case 7:
			push('6');
			break;
		case 9:
			push('7');
			break;
		case 10:
			push('8');
			break;
		case 11:
			push('9');
			break;
		case 14:
			push('0');
			break;
		default:
			break;
	}
}

void clear_calc(void) {
	lcd_clr();
	clear();
}

int main(void)
{
	lcd_init();
    while (1) 
    {
		int key = get_key();
		add_char(key);
		lcd_pos(0,0);
		lcd_puts2(buf);
		if (key == ENTER) {
			//calculate();
		}
		if (key == CLEAR) {
			clear_calc();
		}
		wait_avr(250);
    }
}