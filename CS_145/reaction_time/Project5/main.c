/*
 * Project5.c
 *
 * Created: 3/17/2019 2:00:01 PM
 * Author : Kian
 */ 

#include <avr/io.h>
#include "avr.c"
#include "keypad.c"
#include "lcd.c"

#define A_LOW  220
#define E      659
#define Fs     740
#define C_HIGH 1047

#define UPPER 75
#define LOWER 10

#define BASE_EASY 8
#define BASE_HARD 4
#define SPEED_EASY 0.2
#define SPEED_HARD 0.3

#define HOTKEY 1


void print_play(void) {
	lcd_pos(0,3);
	lcd_puts2("Press 1 to");
	lcd_pos(1,1);
	lcd_puts2("test reactions");
}

void play_note(int freq, int duration) {
	float TH = (1.0 / freq) * 1000;
	float TL = TH;
	for (float i = 0; i < duration; i += 0.1) {
		SET_BIT(PORTA, 1);
		wait_avr(TH);
		CLR_BIT(PORTA, 1);
		wait_avr(TL);
	}
}

void print_ready(void) {
	lcd_clr();
	lcd_pos(0,3);
	lcd_puts2("GET READY");
	wait_avr(1500);
	lcd_clr();
}

int check_early_press(int upper, int lower) {
	lcd_pos(0,3);
	lcd_puts2("-look  at-");
	lcd_pos(1,2);
	lcd_puts2("-the  light-");
	float wait_time = (rand() % (upper - lower + 1)) + lower;
	for (int i = 0; i < wait_time; ++i) {
		if (get_key() == HOTKEY) {
			lcd_clr();
			return 1;
		}
	}
	return 0;
}

void print_early_press(void) {
	lcd_pos(0,3);
	lcd_puts2("TOO EARLY!");
	wait_avr(2000);
	lcd_clr();
}

void print_late_press(void) {
	lcd_pos(0,3);
	lcd_puts2("TOO LATE!!");
	wait_avr(2000);
	lcd_clr();
}

void print_game_over(int high_score) {
	lcd_pos(0,0);
	lcd_puts2("!!!GAME  OVER!!!");
	lcd_pos(1,0);
	char s[20];
	sprintf(s, "High Score: %04d", high_score);
	lcd_puts2(s);
	wait_avr(5000);
	lcd_clr();
}

int check_correct_press(int wait_time) {
	SET_BIT(PORTA,0);
	for (int i = 0; i < wait_time; ++i) {
		if (get_key() == HOTKEY) {
			CLR_BIT(PORTA,0);
			lcd_clr();
			return 1;
		}
	}
	CLR_BIT(PORTA,0);
	lcd_clr();
	return 0;
}

void print_correct_press(int score) {
	lcd_pos(0,0);
	lcd_puts2("CORRECT!!!!");
	lcd_pos(1,0);
	char s[20];
	sprintf(s, "Your Score: %04d", score);
	lcd_puts2(s);
	wait_avr(3000);
	lcd_clr();
}


int main(void)
{
	DDRA = 0x03;
	lcd_init();
	int high_score = 0;
	int current_score = 0;
	float base_speed;
	float base_decrease;
	float user_speed;
	
	while (1)
	{
		lcd_pos(0,0);
		lcd_puts2("Press A for Easy");
		lcd_pos(1,0);
		lcd_puts2("Press B for Hard");
		int key = get_key();
		if (key == 4) {
			base_speed = BASE_EASY;
			base_decrease = SPEED_EASY;
			lcd_clr();
			break;
		}
		else if (key == 8) {
			base_speed = BASE_HARD;
			base_decrease = SPEED_HARD;
			lcd_clr();
			break;
		}
	}
	
    while (1) 
    {
		user_speed = base_speed;
		print_play();
		
		if (HOTKEY == get_key())
			while (1) {
				// prints GET READY
				print_ready();
		
				//prints GAME OVER if pressed too early
				if (check_early_press(UPPER, LOWER)) {
					if (current_score > high_score)
						high_score = current_score;
					play_note(A_LOW, 5);
					print_early_press();
					print_game_over(high_score);
					current_score = 0;
					user_speed = base_speed;
					break;
				}
		
				//prints CORRECT if pressed on time
				else if (check_correct_press(user_speed)) {
					++current_score;
					play_note(E, 3);
					play_note(Fs, 3);
					play_note(C_HIGH, 3);
					print_correct_press(current_score);
					user_speed -= base_decrease;
				}
		
				//prints GAME OVER if pressed too late
				else {
					if (current_score > high_score)
						high_score = current_score;
					play_note(A_LOW, 10);
					print_late_press();
					print_game_over(high_score);
					current_score = 0;
					user_speed = base_speed;
					lcd_clr();
					break;
				}
			}
	}
}

