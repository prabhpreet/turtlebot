/*
 * servo.h
 *
 * Created: 20-01-2014 18:10:56
 *  Author: Admin
 */ 


#ifndef SERVO_H_
#define SERVO_H_

void servo_init();
void servo_elbow(unsigned char degrees);
void servo_grip(unsigned char degrees);
void servo_elbow_free();
void servo_grip_free();
//Servo control

void servo_init()
{
	TCCR1B = 0x00;
	DDRB|= 0b01100000;
	TCNT1H = 0xFC; //Counter high value to which OCR1xH value is to be compared with
	TCNT1L = 0x01; //Counter low value to which OCR1xH value is to be compared with
	OCR1AH = 0x03; //Output compare Register high value for servo 1
	OCR1AL = 0xFF; //Output Compare Register low Value For servo 1
	OCR1BH = 0x03; //Output compare Register high value for servo 2
	OCR1BL = 0xFF; //Output Compare Register low Value For servo 2
	ICR1H = 0x03;
	ICR1L = 0xFF;
	TCCR1A = 0xAB;
	TCCR1B = 0x0C;
	
}

void servo_elbow(unsigned char degrees)
{
	float ElbowPosition = 0;
	ElbowPosition = ((float)degrees / 1.86) + 35.0;
	OCR1AH = 0x00;
	OCR1AL = (unsigned char) ElbowPosition;
}
void servo_grip(unsigned char degrees)
{
	float GripPosition = 0;
	GripPosition = ((float)degrees / 1.86) + 35.0;
	OCR1BH = 0x00;
	OCR1BL = (unsigned char) GripPosition;
}
void servo_elbow_free()
{
	OCR1AH = 0x03;
	OCR1AL = 0xFF;
}
void servo_grip_free()
{
	OCR1BH = 0x03;
	OCR1BL = 0xFF;
}




#endif /* SERVO_H_ */