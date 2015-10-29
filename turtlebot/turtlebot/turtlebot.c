/*
 * turtlebot.c
 *
 * Created: 10/27/2015 11:45:49 PM
 *  Author: Prabhpreet
 */ 
#include "settings.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "uart_library.h"
#include "lcd.h"
#include "motion.h"
#include "servo.h"


int main(void)
{
	char input, string[100], command = 'n';
	int letter = -1;
	cli(); //Clear global interrupts
	lcd_port_config();
	lcd_init();
	uart_init();
	//motor config
	motion_timer5_init();
	motion_pin_config();
	motion_encoder_pin_config();
	//servo config
	servo_init();
	sei();

	motion_velocity(150,150);	
	servo_elbow(180);
	lcd_string("READY");
    while(1)
    {
		while((input = uart_getchar()) != '\n')
		{
			if(letter == -1)
				command = input;
			else
				string[letter] = input;
			letter++;
		}
		string[letter] = '\0';
		letter = atol(string);
		switch(command)
		{
			case 'l':
			case 'r':
			case 'f':
			case 'b':
				if(letter == 0)
				{
					uart_putchar('E');
					uart_putchar('\n');
					letter = -1;
					continue;
				}
				switch(command)
				{
					case 'l': motion_angle_left(letter);
								break;
					case 'r': motion_angle_right(letter);
								break;
					case 'f': motion_forward_mm(letter);
								break;
					case 'b': motion_backward_mm(letter);
								break;
					
				}
				uart_putchar(command);
				uart_putchar('\n');
				break;
			case 'u': servo_elbow(90);
						uart_putchar(command);
						uart_putchar('\n');
						break;
			case 'd': servo_elbow(180);
					
			uart_putchar(command);
			uart_putchar('\n');
			break;
			default:
			uart_putchar('E');
			uart_putchar('\n');
			break;
		}
		
		
		letter = -1;
	}
	return 0;
}