/*
 * uart_library.c
 *
 * Created: 10/28/2015 12:02:22 AM
 *  Author: Prabhpreet
 */ 

#include "settings.h"
#include <avr/io.h>
#include <avr/interrupt.h>

char tx_buffer[MAX_BUFFER], rx_buffer[MAX_BUFFER];
volatile int tx_buff_start, tx_buff_end, rx_buff_start, rx_buff_end;

void uart_init(void) {
	UBRR2H = BAUDRATE >> 8;
	UBRR2L = BAUDRATE;
	UCSR2A &= ~(_BV(U2X2));
	UCSR2C = _BV(UCSZ21) | _BV(UCSZ20); /* 8-bit data */
	UCSR2B = _BV(RXCIE2) | _BV(RXEN2) | _BV(TXEN2);   /* Enable RX and TX */
	rx_buff_start = 0;
	rx_buff_end = 0;
}

void uart_putchar(char c) {
	while (!( UCSR2A & (1<<UDRE2)));  
	UDR2 = c;
}

char uart_getchar() {
	while(rx_buff_start == rx_buff_end);	
	return rx_buffer[++rx_buff_start % MAX_BUFFER];
}

ISR(USART2_RX_vect)
{
	cli();
	rx_buffer[++rx_buff_end % MAX_BUFFER] = UDR2;
	sei();
}