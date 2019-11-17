/*
 * count_characters.c
 *
 *  Created on: Nov 14, 2019
 *      Author: akshh
 */

#include "count_characters.h"

uint8_t character_count[126];
char report_format[1000];

void count_characters(uint8_t charac)
{
	if((charac>=97) && (charac<=122))
	    character_count[charac-97]++;
	else if((charac>=65) && (charac<=90))
	    character_count[charac-39]++;
}

void application_report(uint8_t charac)
{
	if(charac == 13)
	{
		log_string("\n\rApplication mode Character report");
		//Send_String_Poll("\n\rApplication mode Character report\n\r");
		//Send_String("\n\rApplication mode Character report\n\r");
		for(uint8_t i=0; i<126; i++)
		{
			if(character_count[i] > 0)
			{
				if((i>=0) && (i<=25))
					sprintf(report_format, "%c - %d; ", (i+97), character_count[i]);
				else if((i>=26) && (i<=51))
					sprintf(report_format, "%c - %d; ", (i+39), character_count[i]);
#if USE_UART_INTERRUPTS
				Send_String(report_format);
#else
				Send_String_Poll(report_format);
#endif
				//Send_String(report_format);
			}
		}
	}
}

