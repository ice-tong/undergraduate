/*
 * Project4.c
 *
 * Created: 3/2/2019 4:24:40 PM
 * Author : Kian
 */ 

#include <avr/io.h>
#include "avr.c"
#include "keypad.c"
#include "lcd.c"

#define HOTKEY 1
#define N 20

int buf[N];
int i,j,sz;

void push(int x) {
	buf[i] = x;
	i = (i+1) % N;
	sz++;
}

int pop() {
	int temp = buf[j];
	j = (j+1) % N;
	sz--;
	return temp;
}

struct voltmeter {
	int max;
	int min;
	int sum;
	int current;
};

void init(void) {
	lcd_init();
	SET_BIT(ADMUX, 6);
	SET_BIT(ADCSRA, 7);
	SET_BIT(ADCSRA, 2);
	SET_BIT(ADCSRA, 1);
}

int get_sample(void) {
	SET_BIT(ADCSRA, 6);
	while (GET_BIT(ADCSRA, 6));
	return ADC;
}

void update_vm(struct voltmeter * vm) {
	int adc = get_sample();
	
	vm->current = adc;
	if (sz == N-1)
		vm->sum -= pop();
	push(adc);
	if (adc > vm->max)
		vm->max = adc;
	if (adc < vm->min)
		vm->min = adc;
	vm->sum += adc;
}

void vm_print(struct voltmeter * vm) {
	char s[10];
	float volt;
	int v_left;
	int v_right;
	
	volt = vm->current/204.6;
	v_left = volt;
	v_right = (int)(volt*10) % 10;
	sprintf(s, "%01d.%01dV", v_left, v_right);
	lcd_pos(0,0);
	lcd_puts2(s);
	
	volt = vm->max/204.6;
	v_left = volt;
	v_right = (int)(volt*10) % 10;
	sprintf(s, "MAX%01d.%01dV", v_left, v_right);
	lcd_pos(0,9);
	lcd_puts2(s);
	
	volt = vm->min/204.6;
	v_left = volt;
	v_right = (int)(volt*10) % 10;
	sprintf(s, "MIN%01d.%01dV", v_left, v_right);
	lcd_pos(1,9);
	lcd_puts2(s);
	
	volt = (vm->sum/204.6) / (sz);
	v_left = volt;
	v_right = (int)(volt*10) % 10;
	sprintf(s, "AVE%01d.%01dV", v_left, v_right);
	lcd_pos(1,0);
	lcd_puts2(s);
}

void reset_print() {
	lcd_pos(0,0);
	lcd_puts2("----");
	lcd_pos(0,9);
	lcd_puts2("-------");
	lcd_pos(1,0);
	lcd_puts2("-------");
	lcd_pos(1,9);
	lcd_puts2("-------");
}

int main(void)
{
	init();
	struct voltmeter vm = {0,1023,0,0};
		
    while (1) 
    {
		reset_print();
		wait_avr(500);
		
		if (HOTKEY == get_key()) {
			while (1) {
				update_vm(&vm);
				vm_print(&vm);
				wait_avr(500);
				if (HOTKEY == get_key()) {
					break;
				}
			}
		}
    }
}

