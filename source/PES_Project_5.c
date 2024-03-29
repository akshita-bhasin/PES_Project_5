/**
 * file:    PES_Project_5.c
 * author : Akshita Bhasin & Madhukar Arora
 * brief:   Application entry point.
 * created on: Nov 11, 2019
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "logger.h"
#include "uart.h"
#include "timestamp.h"
#include "count_characters.h"
#include "test.h"

/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */

extern log_level log_level_a;
uint8_t int_flag = 0;
uint8_t char_array[126];
void delay(uint16_t num);

uint8_t interrupt = 0;
uint32_t deciseconds = 0;

int main(void) {

	uint8_t charac;
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();
    Init_UART0(115200);
    if(log_level_a == 0)
    	unit_test_cases();
  	/* Init FSL debug console. */

    else if((log_level_a == 1) || (log_level_a == 2))
	{
		SysTick_Config(48000000L/10L);

#if UART_ECHO
#if USE_UART_INTERRUPTS
		Send_String_Poll("Hey There! Welcome to our PES Project 5 :) (interrupt based UART)\n\r");
#else
		Send_String_Poll("Hey There! Welcome to our PES Project 5 :) (polling based UART)\n\r");
#endif
		Send_String_Poll("Type string of characters, and just see them echo back\n\r");
#endif

#if UART_APPLICATION
#if USE_UART_INTERRUPTS
		Send_String("Hey There! Welcome to our PES Project 5 :) (interrupt based UART)\n\r");
#else
		Send_String_Poll("Hey There! Welcome to our PES Project 5 :) (polling based UART)\n\r");
#endif
		Send_String_Poll("Type string of characters, press Enter when you want to see a report of the characters you've typed\n\r");

#endif

		for(uint8_t i=0; i<126; i++)
			char_array[i] = 0x0;
		while(1)
		{
//when in echo mode
#if UART_ECHO
			uart_echo(&charac);
#endif

//when in application mode
#if UART_APPLICATION

			if(uart_application(&charac) == 1)
			{
				count_characters(charac);
			}
			application_report(charac);
    	charac=0;

#endif
		}
	}
    return 0 ;
}
