/*
 * File : timestamp.c
 * Created on: Nov 14, 2019
 * Author: Akshita Bhasin & Madhukar Arora
 * Brief : Contains code for timestamp implementation
 */

#include "timestamp.h"

extern uint32_t deciseconds;

/*
 * File : timestamp.c
 * Created on: Nov 14, 2019
 * Author: Akshita Bhasin & Madhukar Arora
 * Brief : Contains code for timestamp implementation
 */
void SysTick_Handler(void) {
	deciseconds++;
}

/*
 * function name : get_timestamp
 * parameters : void
 * return type : timestamp_t - returns a structure
 * brief : function to get time elapsed since the start of the application
 */
timestampt_t get_timestamp(void)
{
	timestampt_t timestamp_value;
	uint16_t seconds, minutes, hours;
	seconds = deciseconds / 10;
	minutes = seconds / 60;
	hours = minutes / 60;

	timestamp_value.hour = hours;
	timestamp_value.minute = (minutes - (hours*60));
	timestamp_value.second = (seconds - (minutes*60));
	timestamp_value.decisec = (deciseconds - (seconds*10));

	return timestamp_value;
}
