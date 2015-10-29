/*
 * settings.h
 *
 * Created: 10/28/2015 10:13:50 AM
 *  Author: Prabhpreet
 */ 


#ifndef SETTINGS_H_
#define SETTINGS_H_


#define F_CPU 14745600
#define BAUD 9600
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1) 
#define MAX_BUFFER 1000

#endif /* SETTINGS_H_ */