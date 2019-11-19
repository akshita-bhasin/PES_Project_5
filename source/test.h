/* @file test.h
 * @brief Unit test cases headers for PES_Project5
 * @author : Akshita Bhasin and Madhukar Arora
 * @date : 11/18/2019
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
void buffer_init(void);
void buffer_put(void);
void buffer_get(void);
void buffer_overfill(void);
void buffer_overempty(void);
void buffer_data_push_pop(void);
void buffer_free(void);
void buffer_realloc(void);
