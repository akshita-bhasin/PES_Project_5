/* @file System.c
 * @brief System dependent functions used by uCUnit.                 *
 *                This file runs with arm-elf-run
 * @author : Akshita Bhasin and Madhukar Arora
 * @date : 10/18/2019
 * @version 1.0
 *
 ** Referred to uCUnit from mcuoneclipse for the uCUnit case files

*****************************************************************************
 *                                                                           *
 *  uCUnit - A unit testing framework for microcontrollers                   *
 *                                                                           *
 *  (C) 2007 - 2008 Sven Stefan Krauss                                       *
 *                  https://www.ucunit.org                                   *
                                     *
 *****************************************************************************/

/*
 * This file is part of ucUnit.
 *
 * You can redistribute and/or modify it under the terms of the
 * Common Public License as published by IBM Corporation; either
 * version 1.0 of the License, or (at your option) any later version.
 *
 * uCUnit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Common Public License for more details.
 *
 * You should have received a copy of the Common Public License
 * along with uCUnit.
 *
 * It may also be available at the following URL:
 *       http://www.opensource.org/licenses/cpl1.0.txt
 *
 * If you cannot obtain a copy of the License, please contact the
 * author.
 */
#include <stdio.h>
#include <stdlib.h>
#include "System.h"

void System_exit(int val) {
	for(;;) {
		/* we don't do a shutdown with exit(), as this is will affect debugging.
		 * Instead, we stay here in an endless loop.
		 */
		__asm("nop"); /* burning some CPU cycles here */
	}
	// exit(val);
}

/* Stub: Initialize your hardware here */
void System_Init(void)
{
	printf("Init of hardware finished.\r\n");
}

/* Stub: Shutdown your hardware here */
void System_Shutdown(void)
{
	/* asm("\tSTOP"); */

	printf("System shutdown.\r\n");
	System_exit(0);
}

/* Stub: Recover the system */
void System_Recover(void)
{
	/* Stub: Recover the hardware */
	/* asm("\tRESET"); */
	printf("System reset.\r\n");
	System_exit(0);
}

/* Stub: Put system in a safe state */
void System_Safestate(void)
{
	/* Disable all port pins */
	/* PORTA = 0x0000; */
	/* PORTB = 0x0000; */
	/* PORTC = 0x0000; */

	/* Disable interrupts */
	/* DIE(); */

	/* Put processor into idle state */
	/* asm("\tIDLE"); */
	printf("System safe state.\r\n");
	System_exit(0);
}

/* Stub: Transmit a string to the host/debugger/simulator */
void System_WriteString(char * msg)
{
	printf(msg);
	printf("\n\r");
}

void System_WriteInt(int n)
{
	printf("%d", n);

}
