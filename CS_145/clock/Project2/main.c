/*
 * Project2.c
 *
 * Created: 1/29/2019 10:46:35 AM
 * Author : Kian
 */ 

#include <avr/io.h>
#include "avr.c"
#include "lcd.c"

#define JANUARY 31
#define FEBRUARY 28
#define MARCH 31
#define APRIL 30
#define MAY 31
#define JUNE 30
#define JULY 31
#define AUGUST 31
#define SEPTEMBER 30
#define OCTOBER 31
#define NOVEMBER 30
#define DECEMBER 31

#define HOTKEY 4

const int days_array[12] =  {JANUARY, FEBRUARY, MARCH, APRIL,
							MAY, JUNE, JULY, AUGUST, SEPTEMBER,
							OCTOBER, NOVEMBER, DECEMBER};

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

struct datetime {
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int subsecond;
	
	int days_in_month;
};
	
void keep_time(struct datetime * dt) {
	dt->subsecond++;
	if (10 == dt->subsecond) {
		dt->subsecond = 0;
		dt->second++;
		if (60 == dt->second) {
			dt->second = 0;
			dt->minute++;
			if (60 == dt->minute) {
				dt->minute = 0;
				dt->hour++;
				if (24 == dt->hour) {
					dt->hour = 0;
					dt->day++;
					if (dt->days_in_month+1 == dt->day) {
						dt->day = 1;
						dt->month++;
						if (13 == dt->month) {
							dt->month = 1;
							dt->year++;
						}
						dt->days_in_month = days_array[dt->month-1];
					}
				}
			}
		}
	}
}

void print_dt(struct datetime * dt) {
	char date[17];
	sprintf(date, "%02d/%02d/%04d", dt->month, dt->day, dt->year);
	lcd_pos(0,3);
	lcd_puts2(date);
	
	char time[17];
	sprintf(time, "%02d:%02d:%02d", dt->hour, dt->minute, dt->second);
	lcd_pos(1,4);
	lcd_puts2(time);
}

int set_datetime(struct datetime * dt) {
	
	dt->second = 0;
	dt->subsecond = 0;
	
	avr_wait(100);
	int key = get_key();
	
	if (HOTKEY == key)
		return 1;	
			
	switch(key) {
		//change month
		case 1:
			if (1 == dt->month)
				dt->month = 12;
			else
				--dt->month;
					
			dt->days_in_month = days_array[dt->month-1];
			
			if (dt->day > dt->days_in_month)
				dt->day = dt->days_in_month;
			break;
		case 2:
			dt->month = (dt->month % 12) + 1;
				
			dt->days_in_month = days_array[dt->month-1];
			
			if (dt->day > dt->days_in_month)
				dt->day = dt->days_in_month;
			break;
			
		//change day	
		case 5:
			if (1 == dt->day)
				dt->day = dt->days_in_month;
			else
				--dt->day;
			break;
		case 6:
			dt->day = (dt->day % dt->days_in_month) + 1;
			break;
				
		//change year
		case 9:
			if (0 != dt->year)
				--dt->year;
			break;
		case 10:
			if (9999 != dt->year)
				++dt->year;
			break;
				
		//change hour
		case 13:
			if (0 == dt->hour)
				dt->hour = 23;
			else
				--dt->hour;
			break;
		case 14:
			dt->hour = (++dt->hour % 24);
			break;
				
		//change minute
		case 15:
			if (0 == dt->minute)
				dt->minute = 59;
			else
				--dt->minute;
			break;
		case 16:
			dt->minute = (++dt->minute % 60);
			break;
			
		default:
			break;
	}
		
	print_dt(dt);
	return 0;
}

int main(void)
{
	struct datetime dt = {2019, 3, 31, 23, 59, 30, 0, 31};
	
	lcd_init();	
    while (1) 
    {
		avr_wait(20);
		keep_time(&dt);
		print_dt(&dt);
		
		int key = get_key();
		if (HOTKEY == key) {
			avr_wait(500);
			while (1) {
 				if (set_datetime(&dt)) {
					 avr_wait(500);
					break;
				}
			}
		}
    }
}