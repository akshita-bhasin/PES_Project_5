/*
 * rtc.c
 *
 *  Created on: Nov 12, 2019
 *      Author: akshh
 */

#include "rtc.h"

extern uint8_t interrupt;
/*
int main(void)
{
	sysinit();    //This configures the MCG mode as PEE and UART0
	myprintf("Hello World\r\n");
	Clock_Configuration();
	//EnableInterrupts;
	rtc_init();

	while(1)
	{
		if (interrupt){
			myprintf("Timer  %2d:%2d\n\r",minutes,seconds);
			interrupt = 0;
		}
	}
	return 0;
}

void Clock_Configuration (void)
{
	MCG_C1 |= MCG_C1_IRCLKEN_MASK; //Enable internal reference clock
	MCG_C2 &= ~(MCG_C2_IRCS_MASK);  //Internal Reference Clock -->Slow

	//**RTC_CLKIN**/
/*	PORTC_PCR1 |= (PORT_PCR_MUX(0x1));       //PTC1 as RTC_CLKIN
	SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL(0b10);  //32 Khz clock source for RTC

	//**32KHz Frequency**/
/*	SIM_SOPT2 |= SIM_SOPT2_CLKOUTSEL(0b100); //Clockout pin --> 32 KHz

	PORTC_PCR3 |= (PORT_PCR_MUX(0x5)); //PTC3 as CLKOUT
}

void rtc_init()
{
    /*enable the clock to SRTC module register space*/
/*	SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;

	/*Clear Registers*/
/*    RTC_CR  = RTC_CR_SWR_MASK;
    RTC_CR  &= ~RTC_CR_SWR_MASK;

    if (RTC_SR & RTC_SR_TIF_MASK){
        RTC_TSR = 0x00000000;   //  this action clears the TIF
    }

    /*Set time compensation parameters*/
//    RTC_TCR = RTC_TCR_CIR(1) | RTC_TCR_TCR(0xFF);

    /*Enable RTC seconds irq*/
//    enable_irq(INT_RTC_Seconds - 16);

    /*Enable Seconds Interrupt*/
//    RTC_IER |= RTC_IER_TSIE_MASK; //Seconds interrupt enable

    /*Timer enable*/
//    RTC_SR |= RTC_SR_TCE_MASK;

    /*Configure the timer seconds and alarm registers*/
//    RTC_TSR = 0xFF;

/*}

void RTC_isr_Seconds(void)
{
	interrupt = 1;

	seconds = RTC_TSR;
    if (seconds >59){
    	minutes++;
    	RTC_SR &= ~RTC_SR_TCE_MASK;
    	RTC_TSR = 0x00; //Reset counter
    	seconds = RTC_TSR;
    	RTC_SR |= RTC_SR_TCE_MASK;
    }
}
*/


void RTC_Init_Clock(void)
{
	rtc_config_t config_register = {0};
	rtc_datetime_t timeForRTC = {2019, 11, 12, 10, 40, 40};
	RTC_GetDefaultConfig(&config_register);
	RTC_Init(RTC, &config_register);
	RTC_SetDatetime(RTC, &timeForRTC);

	EnableIRQ(RTC_Seconds_IRQn);
	RTC_EnableInterrupts(RTC, kRTC_SecondsInterruptEnable | kRTC_TimeOverflowFlag);
	RTC_StartTimer(RTC);
}

void RTC_Time(void)
{
	rtc_datetime_t timeForRTC;
	RTC_GetDatetime(RTC, &timeForRTC);
	printf("Time from RTC: \t%d: %d: %d\n\r", timeForRTC.hour, timeForRTC.minute, timeForRTC.second);
}

void RTC_Seconds_IRQHandler(void)
{
	interrupt=1;
	//PRINTF("RTC timestamp interrupt Yo!\n\r");
}
