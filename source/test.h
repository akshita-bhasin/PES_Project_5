/* @file test.h
 * @brief Unit test cases headers for PES_Project4
 * @author : Akshita Bhasin and Madhukar Arora
 * @date : 11/03/2019
 * @version 1.0
 **/

//#ifdef TEST
#include <stdio.h>
#include "uCUnit.h"
#include "circularbuffer.h"
#include <stdint.h>
#include "timestamp.h"
#include "uart.h"
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "MKL25Z4.h"
//#endif

void unit_test_cases(void);
void delay_loop(uint16_t num);
