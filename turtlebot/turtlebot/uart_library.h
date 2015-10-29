/*
 * uart_library.h
 *
 * Created: 04-12-2014 20:48:36
 *  Author: Prabhpreet
 */ 


#ifndef UART_LIBRARY_H_
#define UART_LIBRARY_H_

void uart_init(void);
void uart_putchar(char c);
char uart_getchar();


char tx_buffer[MAX_BUFFER], rx_buffer[MAX_BUFFER];
volatile int tx_buff_start, tx_buff_end, rx_buff_start, rx_buff_end;
#endif /* UART_LIBRARY_H_ */