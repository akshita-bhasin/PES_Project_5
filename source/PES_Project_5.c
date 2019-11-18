/**
 * @file    PES_Project_5.c
 * @brief   Application entry point.
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

uint8_t int_flag = 0;
uint8_t char_array[126];
void delay(uint16_t num);

//char timestamp_format[100]; //report_format[1000],

uint8_t interrupt = 0;
uint32_t deciseconds = 0;

int main(void) {

	uint8_t charac;
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    unit_test_cases();
  	/* Init FSL debug console. */


    Init_UART0(115200);
    SysTick_Config(48000000L/10L);
#if USE_UART_INTERRUPTS
   	Send_String("Hey There! Welcome to our PES Project 5 :) (interrupt based UART)\n\r");
#else
   	Send_String_Poll("Hey There! Welcome to our PES Project 5 :) (polling based UART)\n\r");
#endif

#if UART_ECHO
#if USE_UART_INTERRUPTS
    Send_String("Type string of characters, and just see them echo back\n\r");
#else
    Send_String_Poll("Type string of characters, and just see them echo back\n\r");
#endif
#endif
#if UART_APPLICATION
#if USE_UART_INTERRUPTS
    Send_String("Type string of characters, press Enter when you want to see a report of the characters you've typed\n\r");
#else
    Send_String_Poll("Type string of characters, press Enter when you want to see a report of the characters you've typed\n\r");
#endif
#endif

    for(uint8_t i=0; i<126; i++)
    	char_array[i] = 0x0;
    while(1)
    {
#if UART_ECHO
    	uart_echo(&charac);
#endif

#if UART_APPLICATION

    	if(uart_application(&charac) == 1)
    	{
    		count_characters(charac);
    	}
    	application_report(charac);
    	//charac=0;

#endif
    }

    return 0 ;
}
