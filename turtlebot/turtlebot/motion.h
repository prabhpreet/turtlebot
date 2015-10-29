/*
 * motion.h
 *
 * Created: 20-01-2014 18:12:53
 *  Author: Admin
 */ 


#ifndef MOTION_H_
#define MOTION_H_
#include <stdbool.h>
bool motion;
volatile unsigned long int encoder_left, encoder_right;

void motion_timer5_init();
void motion_velocity(unsigned char left_motor, unsigned char right_motor);
void motion_pin_config(void);
void motion_set(unsigned char motion);
void motion_change_directions();
void motion_forward();
void motion_backward();
void motion_stop();
void motion_left();
void motion_right();
void motion_soft_left();
void motion_soft_right();
void motion_encoder_pin_config();
void motion_forward_mm(unsigned long int distance);
void motion_backward_mm(unsigned long int distance);
void motion_angle_degrees(unsigned long int degrees);
void motion_angle_left(unsigned long int degrees);
void motion_angle_right(unsigned long int degrees);
void motion_angle_soft_left(unsigned long int degrees);
void motion_angle_soft_right(unsigned long int degrees);

//Motion library

/*PWM*/
void motion_timer5_init()
{
	
	TCCR5A=0xA9;
	TCCR5B=0x0B;
	TCNT5H = 0xFF;
	TCNT5L = 0x00;
	OCR5AH = 0x00;
	OCR5AL = 0xFF;
	OCR5BH = 0x00;
	OCR5BL = 0xFF;
}
void motion_velocity (unsigned char left_motor, unsigned char right_motor)
{
	OCR5AL = (unsigned char)left_motor;
	OCR5BL = (unsigned char)right_motor;
}

void motion_pin_config(void)
{
	DDRA |= 0x0F; //Control the left/right/forward/backward
	DDRL |= (0b00011000); //Enable pins
	PORTA &= ~(0x0F);
	PORTL |= (0b00011000);
	motion = 0;
}
void motion_set(unsigned char motion)
{
	PORTA = (PORTA&(0xF0))|(motion&(0x0F));
}
void motion_change_directions()
{
	if(motion)
	{
		motion_set(0x00);
		_delay_ms(500);
	}
	motion = 1;
}
void motion_forward()
{
	motion_change_directions();
	motion_set(0x06);
}
void motion_backward()
{
	motion_change_directions();
	motion_set(0x09);
}
void motion_stop()
{
	motion_set(0x00);
}
void motion_left()
{
	motion_change_directions();
	motion_set(0x05);
}
void motion_right()
{
	motion_change_directions();
	motion_set(0x0A);
}
void motion_soft_left()
{
	motion_change_directions();
	motion_set(0x04);
}
void motion_soft_right()
{
	motion_change_directions();
	motion_set(0x02);
}


void motion_encoder_pin_config()
{
	DDRE &= ~(0b00110000);
	PORTE |= 0b00110000;
	encoder_left= 0;
	encoder_right= 0;
	//Interrupt initialization
	cli();
	EIMSK |= (0b00110000);
	EICRB |= (0b00001010);
	sei();
}
//Interrupt routines
ISR(INT4_vect)
{
	encoder_left++;
}
ISR(INT5_vect)
{
	encoder_right++;
}


void motion_forward_mm(unsigned long int distance)
{
	float num_temp = (float) distance/5.338;
	distance = (unsigned long int) num_temp;
	encoder_right = 0;
	motion_forward();
	for(;encoder_right < distance;);
	motion_stop();
}

void motion_backward_mm(unsigned long int distance)
{
	float num_temp = (float) distance/5.338;
	distance = (unsigned long int) num_temp;
	encoder_right = 0;
	motion_backward();
	for(;encoder_right < distance;);
	motion_stop();
}

void motion_angle_degrees(unsigned long int degrees)
{
	float num_temp = (float) degrees/4.090;
	degrees = (unsigned int) num_temp;
	encoder_left = 0;
	encoder_right= 0;
	for(;(encoder_left < degrees)&& (encoder_right < degrees););
	motion_stop();
	
}
void motion_angle_left(unsigned long int degrees)
{
	motion_left();
	motion_angle_degrees(degrees);
}
void motion_angle_right(unsigned long int degrees)
{
	motion_right();
	motion_angle_degrees(degrees);
}
void motion_angle_soft_left(unsigned long int degrees)
{
	motion_soft_left();
	motion_angle_degrees(degrees);
}
void motion_angle_soft_right(unsigned long int degrees)
{
	motion_soft_right();
	motion_angle_degrees(degrees);
}
#endif /* MOTION_H_ */
