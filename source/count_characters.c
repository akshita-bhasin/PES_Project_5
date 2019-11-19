/*
 * count_characters.c
 *
 *  Created on: Nov 14, 2019
 *      Author: akshh
 */

#include "count_characters.h"

extern log_level log_level_a;
uint8_t character_count[126];
char report_format[1000];

void count_characters(uint8_t charac)
{
	if((charac>=97) && (charac<=122))
	    character_count[charac-71]++;
	else if((charac>=65) && (charac<=90))
	    character_count[charac-65]++;
	else if((charac>=33) && (charac<=64))
	    character_count[charac+19]++;
	else if((charac>=91) && (charac<=96))
	    character_count[charac-7]++;
	else if((charac>=123) && (charac<=126))
	    character_count[charac-34]++;
}

void application_report(uint8_t charac)
{
	if(charac == 13)
	{
		if((log_level_a == 1) || (log_level_a == 2))
			log_string_detail(log_level_a, Application_report, "\n\rApplication mode Character report");

		for(uint8_t i=0; i<126; i++)
		{
			if(character_count[i] > 0)
			{
				if((i>=0) && (i<=25))
					sprintf(report_format, "%c - %d; ", (i+65), character_count[i]);
				else if((i>=26) && (i<=51))
					sprintf(report_format, "%c - %d; ", (i+71), character_count[i]);
				else if((i>=52) && (i<=83))
					sprintf(report_format, "%c - %d; ", (i-19), character_count[i]);
				else if((i>=83) && (i<=88))
					sprintf(report_format, "%c - %d; ", (i+7), character_count[i]);
				else if((i>=89) && (i<=92))
					sprintf(report_format, "%c - %d; ", (i+34), character_count[i]);
#if USE_UART_INTERRUPTS
				Send_String(report_format);
#else
				Send_String_Poll(report_format);
#endif
			}
		}
	}
}

