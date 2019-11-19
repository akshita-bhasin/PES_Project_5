/*
 * File : uart.h
 * Created on: Nov 12, 2019
 * Author: Akshita Bhasin & Madhukar Arora
 * Brief : Contains header files for UART Communication
 * Leveraged Code : https://github.com/alexander-g-dean/ESF/blob/master/Code/Chapter_8/Serial-Demo/src/UART.c
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <stdbool.h>
#include "MKL25Z4.h"
#include "circularbuffer.h"
#include "led_control.h"

#define USE_UART_INTERRUPTS 	(0) // 0 for polled UART communications, 1 for interrupt-driven
#define UART_OVERSAMPLE_RATE 	(32)
#define BUS_CLOCK 				(24e6)
#define SYS_CLOCK				(48e6)

#define UART_ECHO 				(0)
#define UART_APPLICATION 		(1)

void Init_UART0(uint32_t baud_rate);

uint8_t uart0_getchar(void);
void uart0_putchar(char ch);
uint8_t tx_available(void);
uint8_t rx_available(void);

bool uart0_rx_chars_available(void);
bool uart0_get_rx_char(void);

void Send_String_Poll(char * str);
void Send_String(uint8_t * str);

uint8_t uart_echo(uint8_t * data);
uint8_t uart_application(uint8_t * data);

#endif /* UART_H_ */
