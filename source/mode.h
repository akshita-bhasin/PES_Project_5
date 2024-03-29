/*
 * File : mode.h
 * Author : Akshita Bhasin & Madhukar Arora
 * Created on: Nov 18, 2019
 * Brief : header file for critical section implementation
 */

#ifndef MODE_H_
#define MODE_H_

#include "MKL25Z4.h"

#define START_CRITICAL UART0->C2 &= ~(UART0_C2_TIE_MASK | UART0_C2_RIE_MASK);

#define END_CRITICAL UART0->C2 |= (UART0_C2_TIE_MASK | UART0_C2_RIE_MASK);

#endif /* MODE_H_ */
