/*
 * File : timestamp.h
 * Created on: Nov 14, 2019
 * Author: Akshita Bhasin & Madhukar Arora
 * Brief : Contains header files for timestamp implementation
 */

#ifndef TIMESTAMP_H_
#define TIMESTAMP_H_

#include <stdint.h>
#include "MKL25Z4.h"

typedef struct {
    uint8_t hour;   /*!< Range from 0 to 23.*/
    uint8_t minute; /*!< Range from 0 to 59.*/
    uint8_t second;
    uint8_t decisec;
}timestampt_t;

timestampt_t get_timestamp(void);

#endif /* TIMESTAMP_H_ */
