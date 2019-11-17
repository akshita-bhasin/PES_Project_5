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

char timestamp_format[100]; //report_format[1000],

uint8_t interrupt = 0;
uint32_t deciseconds = 0;

int main(void) {

	uint8_t charac;
	timestampt_t timestamp_value;
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    unit_test_cases();
  	/* Init FSL debug console. */
//    BOARD_InitDebugConsole();

    /*RTC_Init_Clock();
    while(1)
    {
    	if (interrupt)
    	{
    	RTC_Time();
    	interrupt = 0;
    	}
    } */

    Init_UART0(115200);
    SysTick_Config(48000000L/10L);
    log_string("Hello World");
    //Send_String_Poll("Hello World\n\r");
    //Send_String("Hello World\n\r");

    for(uint8_t i=0; i<126; i++)
    	char_array[i] = 0x0;
    while(1)
    {
/*    	if((deciseconds % 6) == 0) {
    		timestamp_value = get_timestamp();
    		Send_String_Poll("Time from SysTick: \t\n\r");
    		sprintf(timestamp_format,"Time from SysTick: \t%d: %d: %d: %d\n\r",  timestamp_value.hour, timestamp_value.minute, timestamp_value.second, timestamp_value.decisec);
    		Send_String_Poll(timestamp_format);
    		//deciseconds = 0;
    	} */
#if UART_ECHO
    	uart_echo(&charac);
#endif
#if UART_APPLICATION

    	if(uart_application(&charac) == 1)
    	{
    		count_characters(charac);
    	}
    	application_report(charac);
    	charac=0;

#endif
/*    	charac = uart0_getchar();
    	uart0_putchar(charac); */
//#endif
    }

    return 0 ;
}

void delay(uint16_t num)
{
	uint64_t numb = num * 1000*2.3;
	while(numb != 0)
	{
		numb--;
	}
}
