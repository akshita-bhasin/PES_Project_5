/*
 * File : count_characters.h
 * Created on: Nov 14, 2019
 * Author: Akshita Bhasin & Madhukar Arora
 * Brief : Contains header files for application mode implementation
 */

#ifndef COUNT_CHARACTERS_H_
#define COUNT_CHARACTERS_H_

#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "logger.h"

void count_characters(uint8_t char_data);
void application_report(uint8_t charac);

#endif /* COUNT_CHARACTERS_H_ */
