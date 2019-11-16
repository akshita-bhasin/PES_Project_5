/*
 * uart.c
 *
 *  Created on: Nov 12, 2019
 *      Author: akshh
 */

#include "uart.h"

#define UART_MAX_SIZE (4)

cbuf_handle_t TxBuffer = NULL;
cbuf_handle_t RxBuffer = NULL;

int getchar(void);
int putchar(int c);

extern uint8_t int_flag;

void Init_UART0(uint32_t baud_rate) {
	uint16_t sbr;
	uint8_t temp;

	// Enable clock gating for UART0 and Port A
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	// Make sure transmitter and receiver are disabled before init
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

	// Set UART clock to 48 MHz clock
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
	SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;

	// Set pins to UART0 Rx and Tx
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Rx
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Tx

	// Set baud rate and oversampling ratio
	sbr = (uint16_t)((SYS_CLOCK)/(baud_rate * UART_OVERSAMPLE_RATE));
	UART0->BDH &= ~UART0_BDH_SBR_MASK;
//	UART0->BDH |= UART0_BDH_SBR(sbr>>8);
	UART0->BDL = UART0_BDL_SBR(sbr);
	UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE-1);

	// Disable interrupts for RX active edge and LIN break detect, select one stop bit
//	UART0->BDH |= UART0_BDH_RXEDGIE(0) | UART0_BDH_SBNS(0) | UART0_BDH_LBKDIE(0);

	UART0->C1 = 0;

	UART0->C3 =0;

	// Clear error flags
	UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);

	// Send LSB first, do not invert received data
	UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);

#if USE_UART_INTERRUPTS
	// Enable interrupts. Listing 8.11 on p. 234
	TxBuffer = circular_buf_init(UART_MAX_SIZE);
	RxBuffer = circular_buf_init(UART_MAX_SIZE);
	//Q_Init(&TxQ); // add circular buffer init for Tx
	//Q_Init(&RxQ); // add circular buffer init for Rx

	NVIC_SetPriority(UART0_IRQn, 2); // 0, 1, 2, or 3
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);

	// Enable receive interrupts but not transmit interrupts yet
	UART0->C2 |= UART_C2_RIE(1);// | UART_C2_TIE(1);

#endif

	// Enable UART receiver and transmitter
	UART0->C2 |= UART0_C2_RE(1) | UART0_C2_TE(1);

	// Clear the UART RDRF flag
	temp = UART0->D;
	UART0->S1 &= ~UART0_S1_RDRF_MASK;

}

void uart0_putchar(char ch)
{
//#if (USE_UART_INTERRUPTS == 0)
		while (!(UART0->S1 & UART0_S1_TDRE_MASK));
//#endif
		UART0->D = (uint8_t)ch;
}

uint8_t uart0_getchar(void) {
//#if (USE_UART_INTERRUPTS == 0)
		while (!(UART0->S1 & UART0_S1_RDRF_MASK));
//#endif
		return UART0->D;
}

void Send_String_Poll(char * str) {
	// enqueue string
	while (*str != '\0') { // Send characters up to null terminator
		uart0_putchar(*str++);
	}
}

void Send_String(uint8_t * str) {
	// enqueue string
	while (*str != '\0') { // copy characters up to null terminator
		while(circular_buf_full(TxBuffer) == buffer_full)
			;
		circular_buf_put2(TxBuffer, *str);
		//while (Q_Full(&TxQ))
			; // wait for space to open up
		//Q_Enqueue(&TxQ, *str);
		str++;
	}
	// start transmitter if it isn't already running
	if (!(UART0->C2 & UART0_C2_TIE_MASK)) {
		//UART0->D = Q_Dequeue(&TxQ);
		UART0->C2 |= UART0_C2_TIE(1);
	}
}

bool uart0_rx_chars_available(void)
{
	return (UART0->S1 & UART0_S1_TDRE_MASK);
}

bool uart0_get_rx_char(void)
{
	return (UART0->S1 & UART0_S1_RDRF_MASK);
}

uint32_t Rx_Chars_Available(void) {
	return circular_buf_size(RxBuffer);
	//return Q_Size(&RxQ);
}

uint8_t	Get_Rx_Char(void) {
	uint8_t data;
	return circular_buf_get(RxBuffer, &data);
	//return Q_Dequeue(&RxQ);
}

void UART0_IRQHandler(void) {
	uint8_t chara, tx_read;

/*	if (UART0->S1 & UART0_S1_RDRF_MASK) {
		chara = UART0->D;
		UART0->C2 |= UART0_C2_TIE_MASK;
		UART0->S1 &= ~UART0_S1_RDRF_MASK;
	}
	else if((UART0->S1 & UART0_S1_TDRE_MASK))// && (UART0->C2 & UART0_C2_TIE_MASK))
	{
		UART0->D = chara;
		UART0->C2 &= ~UART0_C2_TIE_MASK;
		UART0->S1 |= UART0_S1_RDRF_MASK;
	}

	if ((UART0->C2 & UART0_C2_TIE_MASK) && // transmitter interrupt enabled
				(UART0->S1 & UART0_S1_TDRE_MASK)) { // tx buffer empty
				UART0->D = chara;
				UART0->S1 |= UART0_S1_RDRF_MASK;
	} */

	if (UART0->S1 & (UART_S1_OR_MASK |UART_S1_NF_MASK |
		UART_S1_FE_MASK | UART_S1_PF_MASK)) {
			// clear the error flags
			UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
									UART0_S1_FE_MASK | UART0_S1_PF_MASK;
			// read the data register to clear RDRF
			chara = UART0->D;
	}

	if (UART0->S1 & UART0_S1_RDRF_MASK) {
		// received a character
		chara = UART0->D;
		if(circular_buf_full(RxBuffer) == buffer_not_full) {// (!Q_Full(&RxQ)) { check if circular buffer not full
			circular_buf_put2(RxBuffer, chara); // Q_Enqueue(&RxQ, ch); // dp push in circular buffer
		} else {
			// error - queue full.
			// discard character
		}
		UART0->S1 &= ~UART0_S1_RDRF_MASK;
		UART0->C2 |= UART0_C2_TIE_MASK;
	}
	if ( (UART0->C2 & UART0_C2_TIE_MASK) && // transmitter interrupt enabled
			(UART0->S1 & UART0_S1_TDRE_MASK) ) { // tx buffer empty
		//UART0->D = chara;
		// can send another character
		if(circular_buf_empty(TxBuffer) == buffer_not_empty) { // (!Q_Empty(&TxQ)) { //check if cicrular buffer not empty
			if(circular_buf_get(TxBuffer, &tx_read) == buffer_success)
				UART0->D = tx_read;
			//UART0->D = Q_Dequeue(&TxQ); // pop from buffer
		} else {
			// queue is empty so disable transmitter interrupt
			UART0->C2 &= ~UART0_C2_TIE_MASK;
		}
		UART0->S1 |= UART0_S1_RDRF_MASK;
	}
}

uint8_t uart_echo(uint8_t * data)
{
	int_flag=0;
#if USE_UART_INTERRUPTS
	if((circular_buf_get(RxBuffer, data)) == buffer_success)
	//if(cicular_buffer_put)
	{
		circular_buf_put2(TxBuffer, *data);
		UART0->C2 |= UART0_C2_TIE_MASK;
		//circularbufferpush
		int_flag=1;
	}
#else
	{
		uint8_t ch;
		ch = uart0_getchar();
		* data = ch;
		uart0_putchar(ch);
		int_flag=0;
	}
#endif
	return int_flag;
}
