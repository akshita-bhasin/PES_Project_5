/*
 * count_characters.c
 *
 *  Created on: Nov 14, 2019
 *      Author: akshh
 */

#include "count_characters.h"

uint8_t character_count[10000];

uint8_t * count_characters(char data)
{
	if((data >= 'A' && data<='Z') || (data >= 'a' && data <='z'))
		character_count[data]++;
	return character_count;
}

