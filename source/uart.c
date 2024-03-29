/*
 * File : uart.c
 * Created on: Nov 12, 2019
 * Author: Akshita Bhasin & Madhukar Arora
 * Brief : Contains code for UART Communication
 * Leveraged Code : https://github.com/alexander-g-dean/ESF/blob/master/Code/Chapter_8/Serial-Demo/src/UART.c
 */

#include "uart.h"

#define UART_MAX_SIZE (254)

cbuf_handle_t TxBuffer = NULL;
cbuf_handle_t RxBuffer = NULL;

extern uint8_t int_flag;
extern log_level log_level_a;
uint8_t while_flag=0;


/*
 * function name : Init_UART0
 * parameters : baud_rate - baud rate value
 * return type : void
 * brief : initializes the UART0 Module on KL25Z
 */
void Init_UART0(uint32_t baud_rate) {
	uint16_t sbr;
	//uint8_t temp;
	turn_on_led_color('B');

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

#if UART_APPLICATION
	do
	{
		while_flag = 0;
		TxBuffer = circular_buf_init(UART_MAX_SIZE);
		RxBuffer = circular_buf_init(UART_MAX_SIZE);
		if(circular_buf_initialized(TxBuffer) == buffer_init_fail)
		{
			Send_String_Poll("Buffer init for Tx buffer failed");
			while_flag = 1;
		}
		else if(circular_buf_initialized(RxBuffer) == buffer_init_fail)
		{
			Send_String_Poll("Buffer init for Rx Buffer failed");
			while_flag = 1;
		}
		else if(circular_buf_valid(TxBuffer) == buffer_invalid)
		{
			Send_String_Poll("Tx Buffer not initialized correct, hence invalid");
			while_flag = 1;
		}
		else if(circular_buf_valid(RxBuffer) == buffer_invalid)
		{
			Send_String_Poll("Rx Buffer not initialized correct, hence invalid");
			while_flag = 1;
		}
	}while(while_flag==1);
#endif
#if USE_UART_INTERRUPTS
	// Enable interrupts. Listing 8.11 on p. 234
	NVIC_SetPriority(UART0_IRQn, 2); // 0, 1, 2, or 3
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);

	// Enable receive interrupts but not transmit interrupts yet
	UART0->C2 |= UART_C2_RIE(1);// | UART_C2_TIE(1);

#endif

	// Enable UART receiver and transmitter
	UART0->C2 |= UART0_C2_RE(1) | UART0_C2_TE(1);

	// Clear the UART RDRF flag
	//temp = UART0->D;
	UART0->S1 &= ~UART0_S1_RDRF_MASK;

}

/*
 * function name : uart0_putchar
 * parameters : ch - character to be transmited
 * return type : void
 * brief : receives a character and stores in UART data register
 */
void uart0_putchar(char ch)
{
#if !USE_UART_INTERRUPTS
	while(!(tx_available()));
#endif
	UART0->D = (uint8_t)ch;
	turn_on_led_color('G');
}

/*
 * function name : uart0_getchar
 * parameters : void
 * return type : uint8_t - returns the data
 * brief : transmits the character in UART data register
 */
uint8_t uart0_getchar(void) {
	turn_on_led_color('B');
#if !USE_UART_INTERRUPTS
	while(!(rx_available()));
#endif
	return UART0->D;
}

/*
 * function name : tx_available
 * parameters : void
 * return type : uint8_t - returns the if transmission buffer is available or not
 * brief : checks the transmission buffer and returns its status
 */
uint8_t tx_available(void)
{
	if (UART0->S1 & UART0_S1_TDRE_MASK)
		return 1;
	else
		return 0;

}

/*
 * function name : rx_available
 * parameters : void
 * return type : uint8_t - returns the if receive buffer is available or not
 * brief : checks the receive buffer and returns its status
 */
uint8_t rx_available(void)
{
	if(UART0->S1 & UART0_S1_RDRF_MASK)
		return 1;
	else
		return 0;
}

/*
 * function name : Send_String_Poll
 * parameters : char * str - pointer to a string
 * return type : void
 * brief : output characters till null character in polling mode
 */
void Send_String_Poll(char * str) {
	// enqueue string
	while (*str != '\0') { // Send characters up to null terminator
		uart0_putchar(*str++);
	}
}

/*
 * function name : Send_String
 * parameters : uint8_t * str - pointer to a string
 * return type : void
 * brief : output characters till null character
 */
void Send_String(uint8_t * str) {
	// enqueue string
	uint8_t data;
	while (*str != '\0') { // copy characters up to null terminator
		while(circular_buf_full(TxBuffer) == buffer_full)
			;
		circular_buf_put2(&TxBuffer, *str);
		str++;
	}
	// start transmitter if it isn't already running
	if (!(UART0->C2 & UART0_C2_TIE_MASK)) {
		if(circular_buf_get(TxBuffer, &data) == buffer_success)
			UART0->D = data;
		UART0->C2 |= UART0_C2_TIE(1);
	}
}

/*
 * function name : uart0_rx_chars_available
 * parameters : void
 * return type : bool
 * brief : returns if character available to read from buffer
 */
bool uart0_rx_chars_available(void)
{
	return circular_buf_size(RxBuffer);
}

/*
 * function name : uart0_get_rx_char
 * parameters : void
 * return type : bool
 * brief : returns true if character read from circular buffer
 */
bool uart0_get_rx_char(void)
{
	uint8_t data;
	return circular_buf_get(RxBuffer, &data);
}

/*
 * function name : uart0_irqhandler
 * parameters : void
 * return type : void
 * brief : interrupt service routine for UART 0
 */
#if USE_UART_INTERRUPTS
void UART0_IRQHandler(void) {
	uint8_t chara, tx_read;
#if UART_ECHO

	if (UART0->S1 & UART0_S1_RDRF_MASK) {
		turn_on_led_color('B');
		chara = UART0->D;
		UART0->C2 |= UART0_C2_TIE_MASK;
		UART0->S1 &= ~UART0_S1_RDRF_MASK;
	}
	else if((UART0->S1 & UART0_S1_TDRE_MASK))// && (UART0->C2 & UART0_C2_TIE_MASK))
	{
		turn_on_led_color('G');
		UART0->D = chara;
		UART0->C2 &= ~UART0_C2_TIE_MASK;
		UART0->S1 |= UART0_S1_RDRF_MASK;
	}
#endif

#if UART_APPLICATION
	if (UART0->S1 & (UART_S1_OR_MASK |UART_S1_NF_MASK |
		UART_S1_FE_MASK | UART_S1_PF_MASK)) {
			// clear the error flags
			UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
									UART0_S1_FE_MASK | UART0_S1_PF_MASK;
			// read the data register to clear RDRF
			chara = UART0->D;
			turn_on_led_color('R');
	}

	if (UART0->S1 & UART0_S1_RDRF_MASK) {
		turn_on_led_color('B');
		// received a character
		chara = UART0->D;
		if(circular_buf_full(RxBuffer) == buffer_not_full) {// check if circular buffer not full
			circular_buf_put2(&RxBuffer, chara); // do push in circular buffer
		} else {
			log_string_detail(log_level_a, Uart_application, "Interrupt: Circular buffer is full, remove some items if needed");
		}
		UART0->S1 &= ~UART0_S1_RDRF_MASK;
		UART0->C2 |= UART0_C2_TIE_MASK;
	}
	if ( (UART0->C2 & UART0_C2_TIE_MASK) && // transmitter interrupt enabled
			(UART0->S1 & UART0_S1_TDRE_MASK) ) { // tx buffer empty

		turn_on_led_color('G');
		if(circular_buf_empty(TxBuffer) == buffer_not_empty) { //check if circular buffer not empty
			if(circular_buf_get(TxBuffer, &tx_read) == buffer_success)
				UART0->D = tx_read;
		} else {
			log_string_detail(log_level_a, Uart_application, "Interrupt: Circular buffer is empty, add some items if needed");
			// queue is empty so disable transmitter interrupt
			UART0->C2 &= ~UART0_C2_TIE_MASK;
		}
		UART0->S1 |= UART0_S1_RDRF_MASK;
	}
#endif
}
#endif

/*
 * function name : uart_echo
 * parameters : void
 * return type : uint8_t
 * brief : runs the UART in echo mode
 */
uint8_t uart_echo(uint8_t * data)
{
	int_flag=0;
#if USE_UART_INTERRUPTS
		int_flag=1;
#else
	{
		uint8_t ch;
		ch = uart0_getchar();
		* data = ch;
		uart0_putchar(ch);
		int_flag=1;
	}
#endif
	return int_flag;
}

/*
 * function name : uart_application
 * parameters : uint8_t * data
 * return type : uint8_t
 * brief : runs the UART in application mode
 */
uint8_t uart_application(uint8_t * data)
{
	int_flag=0;
#if USE_UART_INTERRUPTS
	if((circular_buf_get(RxBuffer, data)) == buffer_success)
	{
		circular_buf_put2(&TxBuffer, *data);
		UART0->C2 |= UART0_C2_TIE_MASK;
		int_flag=1;
	}
#else
	{
		uint8_t chara, tx_read;
		chara = uart0_getchar();
		if(circular_buf_full(RxBuffer) == buffer_not_full) {// check if circular buffer not full
				circular_buf_put2(&RxBuffer, chara); // do push in circular buffer
		} else {
			log_string_detail(log_level_a, Uart_application, "Polling: Circular buffer is full, remove some items if needed");
		}

		if((circular_buf_get(RxBuffer, data)) == buffer_success)
		{
			circular_buf_put2(&TxBuffer, *data);
		}


		if(circular_buf_empty(TxBuffer) == buffer_not_empty) { // (!Q_Empty(&TxQ)) { //check if cicrular buffer not empty
				if(circular_buf_get(TxBuffer, &tx_read) == buffer_success) {
					uart0_putchar(tx_read);
			} else {
				log_string_detail(log_level_a, Uart_application, "Polling: Circular buffer is empty, add some items if needed");
				// queue is empty so disable transmitter interrupt
				UART0->C2 &= ~UART0_C2_TIE_MASK;
			}
			UART0->S1 |= UART0_S1_RDRF_MASK;
		}
		int_flag=1;
	}
#endif
	return int_flag;
}


