/*
 * rtc.h
 *
 *  Created on: Nov 12, 2019
 *      Author: akshh
 */

#ifndef RTC_H_
#define RTC_H_

#include "fsl_common.h"
#include "fsl_rtc.h"

void RTC_Init_Clock(void);

void RTC_Time(void);

void RTC_Seconds_IRQHandler(void);

#endif /* RTC_H_ */
