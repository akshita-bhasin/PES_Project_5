/*
 * uart.h
 *
 *  Created on: Nov 12, 2019
 *      Author: akshh
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <stdbool.h>
#include "MKL25Z4.h"
#include "circularbuffer.h"
//#include "queue.h"

#define USE_UART_INTERRUPTS 	(1) // 0 for polled UART communications, 1 for interrupt-driven
#define UART_OVERSAMPLE_RATE 	(32)
#define BUS_CLOCK 				(24e6)
#define SYS_CLOCK				(48e6)

void Init_UART0(uint32_t baud_rate);

uint8_t uart0_getchar(void);
void uart0_putchar(char ch);
//void sendstring(char * string);

/*
void UART0_Transmit_Poll(uint8_t data);
uint8_t UART0_Receive_Poll(void); */

bool uart0_rx_chars_available(void);
bool uart0_get_rx_char(void);

void Send_String_Poll(char * str);
void Send_String(uint8_t * str);

uint32_t Rx_Chars_Available(void);
uint8_t	Get_Rx_Char(void);

uint8_t uart_echo(uint8_t * data);

#endif /* UART_H_ */
