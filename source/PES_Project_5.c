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
#include "uart.h"
#include "timestamp.h"
#include "test.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */

uint8_t int_flag = 0;
uint8_t char_array[126];
void delay(uint16_t num);

char report_format[1000], timestamp_format[100];

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
    Send_String_Poll("Hello World\n\r");
    SysTick_Config(48000000L/100L);

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
#ifdef UART_ECHO
    	uart_echo(&charac);
#endif
//#ifdef UART_APPLICATION

    	if(uart_echo(&charac) == 1)
    	{
    		if((charac>=97) && (charac<=122))
    			char_array[charac-97]++;
    		else if((charac>=65) && (charac<=90))
    			char_array[charac-39]++;
    	}
    	if(charac == 13)
    	{
    		Send_String_Poll("\n\rApplication mode Character report\n\r");
    		for(uint8_t i=0; i<126; i++)
    		{
    			if(char_array[i] > 0)
    			{
    				if((i>=0) && (i<=25))
    					sprintf(report_format, "%c - %d; ", (i+97), char_array[i]);
    				else if((i>=26) && (i<=51))
    					sprintf(report_format, "%c - %d; ", (i+39), char_array[i]);
    				Send_String_Poll(report_format);
    			}
    		}
    		charac=0;
    	}
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
