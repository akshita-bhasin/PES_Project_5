/*
 * timestamp.c
 *
 *  Created on: Nov 14, 2019
 *      Author: akshh
 */

#include "timestamp.h"

extern uint32_t deciseconds;

/*void Init_SysTick(void) {
	SysTick->LOAD = (48000000L/160);
	NVIC_SetPriority(SysTick_IRQn, 3);
	SysTick->VAL=0;
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
} */

void SysTick_Handler(void) {
	deciseconds++;
//	PRINTF("\r\nSysTick: %d\r\n", systick_count);
}

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
