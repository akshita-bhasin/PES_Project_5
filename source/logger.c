/*
 * @File Name  : logger.c
 * @Brief : contains logger implementation
 * @Author : Akshita Bhasin and Madhukar Arora
 * @Created On : 11/10/2019
 */

#include "logger.h"

log_level log_level_a = 1;
char timestamp_format[100];

/* function name : log_string_detail
 * return type : void
 * parameters :logLevel - variable of enum type log_level, funcName - variable of enum type function_name, char *str - points to string
 * @brief : Uses the log level and the status of the function
 *          and prints the details
 */
void log_string_detail(log_level logLevel, function_name func_name, char * str)
{
	timestampt_t timestamp_value;
	timestamp_value = get_timestamp();
 	sprintf(timestamp_format,"\tTime from SysTick: \t%d: %d: %d: %d\t",  timestamp_value.hour, timestamp_value.minute, timestamp_value.second, timestamp_value.decisec);

	char * log = get_log_level(logLevel);
	char * func = get_func_name(func_name);
#if UART_APPLICATION
#if USE_UART_INTERRUPTS
	Send_String("\n\r");
	Send_String(log);
	Send_String(func);
	Send_String(timestamp_format);
	Send_String(str);
	Send_String("\n\r");
#else
	Send_String_Poll("\n\r");
	Send_String_Poll(log);
	Send_String_Poll(func);
	Send_String_Poll(timestamp_format);
	Send_String_Poll(str);
	Send_String_Poll("\n\r");
#endif
#endif
#if UART_ECHO
	Send_String_Poll("\n\r");
	Send_String_Poll(log);
	Send_String_Poll(func);
	Send_String_Poll(timestamp_format);
	Send_String_Poll(str);
	Send_String_Poll("\n\r");
#endif
}

/* function name : log_string
 * return type : void
 * parameters : char *str - pointer to a string
 * @brief : prints a debug message to the terminal
 */
void log_string(char * str)
{
#if UART_APPLICATION
#if USE_UART_INTERRUPTS
	Send_String(str);
#else
	Send_String_Poll(str);
#endif
#endif
#if UART_ECHO
	Send_String_Poll(str);
#endif
	timestampt_t timestamp_value;
	timestamp_value = get_timestamp();
 	sprintf(timestamp_format,"\tTime from SysTick: \t%d: %d: %d: %d\n\r",  timestamp_value.hour, timestamp_value.minute, timestamp_value.second, timestamp_value.decisec);
#if UART_APPLICATION
#if USE_UART_INTERRUPTS
 	Send_String(timestamp_format);
#else
 	Send_String_Poll(timestamp_format);
#endif
#endif
#if UART_ECHO
 	Send_String_Poll(timestamp_format);
#endif
}

/* function name : log_char
 * return type : void
 * parameters : char ch
 * @brief : prints a single character to the terminal
 */
void log_char(char ch)
{
#if UART_APPLICATION
#if USE_UART_INTERRUPTS
	Send_String(ch);
	Send_String("\n\r");
#else
	Send_String_Poll(ch);
	Send_String_Poll("\n\r");
#endif
#endif
#if UART_ECHO
	Send_String_Poll(ch);
	Send_String_Poll("\n\r");
#endif

	timestampt_t timestamp_value;
	timestamp_value = get_timestamp();
 	sprintf(timestamp_format,"Time from SysTick: \t%d: %d: %d: %d\n\r",  timestamp_value.hour, timestamp_value.minute, timestamp_value.second, timestamp_value.decisec);
#if UART_APPLICATION
#if USE_UART_INTERRUPTS
 	Send_String(timestamp_format);
#else
 	Send_String_Poll(timestamp_format);
#endif
#endif
#if UART_ECHO
 	Send_String_Poll(timestamp_format);
#endif
}

/* function name : log_integer
 * return type : void
 * parameters : uint8_t num - number, char type - number is decimal or hexadecimal
 * @brief : prints a number to the terminal depending on its type
 */
void log_integer(uint8_t num, char type)
{
	char print_format[100];
	if(type == 'd')
	{
		sprintf(print_format, "%d\n\r", num);
	}
	else if((type == 'h') | (type=='H'))
	{
		sprintf(print_format, "0x%X\n\r", num);
	}
	else
	{
		sprintf(print_format, "%d\n\r", num);
	}
#if UART_APPLICATION
#if USE_UART_INTERRUPTS
 	Send_String(print_format);
#else
 	Send_String_Poll(print_format);
#endif
#endif
#if UART_ECHO
	Send_String_Poll(print_format);
#endif
	timestampt_t timestamp_value;
	timestamp_value = get_timestamp();
 	sprintf(timestamp_format,"Time from SysTick: \t%d: %d: %d: %d\n\r",  timestamp_value.hour, timestamp_value.minute, timestamp_value.second, timestamp_value.decisec);
#if UART_APPLICATION
#if USE_UART_INTERRUPTS
 	Send_String(timestamp_format);
#else
 	Send_String_Poll(timestamp_format);
#endif
#endif
#if UART_ECHO
 	Send_String_Poll(timestamp_format);
#endif
}

/* function name : get_func_name
 * return type : char*
 * parameters : function_name func_name - func_name is an variable of enum type function_name
 * @brief : returns a string
 */
char* get_func_name(function_name func_name)
{
	switch(func_name)
	{
		case init_UART0: if(log_level_a == 1)
							return "Init_UART0- initializes UART0: ";
						else if(log_level_a == 2)
		 	 	 	 	 return "Init_UART0: ";
							break;
		case Uart0_getchar: if(log_level_a == 1)
								return "UART0_getchar- gets a character from the user when receiver is ready to receive: ";
							else if(log_level_a ==2)
								return "UART0_getchar: ";
							break;
		case Uart0_putchar: if(log_level_a == 1)
								return "UART0_putchar- puts character back on terminal when transmitter is ready to transmit: ";
							else if(log_level_a == 2)
								return "UART0_putchar: ";
							break;
		case Tx_available: if(log_level_a == 1)
								return "Tx_available- checks if transmitter available: ";
							else if(log_level_a == 2)
								return "Tx_available: ";
							break;
		case Rx_available: if(log_level_a == 1)
								return "Rx_available- checks if receiver available: ";
							else if(log_level_a == 2)
								return "Rx_available: ";
							break;
		case Uart0_rx_chars_available: if(log_level_a == 1)
											return "Uart0_rx_chars_available- size of receiver circular buffer available: ";
										else if(log_level_a == 2)
											return "Uart0_rx_chars_available: ";
									break;
		case Uart0_get_rx_char: if(log_level_a == 1)
									return "Uart0_get_rx_char- pops one item from the receiver buffer: ";
								else if(log_level_a == 2)
									return "Uart0_get_rx_char: ";
								break;
		case send_String_Poll: if(log_level_a == 1)
									return "send_String_Poll- sends entire string of characters using UART polling: ";
								else if(log_level_a == 2)
									return "send_String_Poll: ";
								break;
		case send_String: if(log_level_a == 1)
								return "send_String- sends string of characters using UART interrupt: ";
							else if(log_level_a == 2)
								return "send_String: ";
							break;
		case Uart_echo: if(log_level_a == 1)
							return "Uart_echo- echo mode operations performed: ";
						else if(log_level_a == 2)
							return "Uart_echo: ";
						break;
		case Uart_application: if(log_level_a == 1)
									return "Uart_application- application mode operations performed: ";
								else if(log_level_a == 2)
									return "Uart_application: ";
								break;
		case Circular_buf_init: if(log_level_a == 1)
									return "Circular_buf_init- uses malloc and initializes circular buffer: ";
								else if(log_level_a == 2)
									return "Circular_buf_init: ";
								break;
		case Circular_buf_free: if(log_level_a == 1)
									return "Circular_buf_free- frees allocated buffer and circular buffer pointer: ";
								else if(log_level_a == 2)
									return "Circular_buf_free: ";
								break;
		case Circular_buf_reset: if(log_level_a == 1)
									return "Circular_buf_reset- resets the circular buffer to init state: ";
								else if(log_level_a == 2)
										return "Circular_buf_reset: ";
								break;
		case Circular_buf_put2: if(log_level_a == 1)
									return "Circular_buf_put2- writes data into buffer: ";
								else if(log_level_a == 2)
									return "Circular_buf_put2- writes data into buffer: ";
								break;
		case Circular_buf_get: if(log_level_a == 1)
									return "Circular_buf_get- reads data from buffer: ";
								else if(log_level_a == 2)
									return "Circular_buf_get: ";
								break;
		case Circular_buf_empty: if(log_level_a == 1)
									return "Circular_buf_empty- checks if circular is empty: ";
								else if(log_level_a == 2)
									return "Circular_buf_empty: ";
								break;
		case Circular_buf_full: if(log_level_a == 1)
									return "Circular_buf_full- checks if circular is full: ";
								else if(log_level_a == 2)
									return "Circular_buf_full: ";
								break;
		case Circular_buf_capacity: if(log_level_a == 1)
										return "Circular_buf_capacity- returns capacity of circular buffer: ";
									else if(log_level_a == 2)
										return "Circular_buf_capacity: ";
									break;
		case Circular_buf_size: if(log_level_a == 1)
									return "Circular_buf_size- gets size of circular buffer: ";
								else if(log_level_a == 2)
									return "Circular_buf_size: ";
								break;
		case Circular_buf_initialized: if(log_level_a == 1)
											return "Circular_buf_initialized- checks if circular buffer is initialized or not: ";
										else if(log_level_a == 2)
											return "Circular_buf_initialized: ";
										break;
		case Circular_buf_valid: if(log_level_a == 1)
									return "Circular_buf_valid- check if circular buffer is valid or not: ";
								else if(log_level_a == 2)
									return "Circular_buf_valid: ";
								break;
		case Circular_buffer_realloc: if(log_level_a == 1)
											return "Circular_buffer_realloc - reallocates memeory when an overflow happens: ";
										else if(log_level_a == 2)
											return "Circular_buffer_realloc: ";
										break;
		case Count_characters: if(log_level_a == 1)
									return "Count_characters- keeps a count of alphabets received on UART: ";
								else if(log_level_a == 2)
									return "Count_characters: ";
								break;
		case Application_report: if(log_level_a == 1)
									return "Application_report- used to print report in application mode: ";
								else if(log_level_a == 2)
									return "Application_report: ";
								break;
		case Get_timestamp: if(log_level_a == 1)
								return "Get_timestamp- gets timestamp using SysTick Timer with a 0.1 second and displays in HH:mm:ss:n!: ";
							else if(log_level_a == 2)
								return "Get_timestamp: ";
							break;
		case Turn_on_LED_color: if(log_level_a == 1)
									return "turn_on_LED_Color- turns on chosen color of LED: ";
								else if(log_level_a == 2)
									return "turn_on_LED_Color: ";
								break;

	}
	return " ";
}

/* function name : get_log_level
 * return type : char*
 * parameters : log_level logLevel- logLevel is a variable of enum type log_level
 * @brief : returns a string
 */
char* get_log_level(log_level logLevel)
{
	switch(logLevel)
	{
		case Test: return "Test: ";
					break;
		case Status: return "Status: ";
					break;
		case Debug: return "Debug: ";
					break;
	}
	return " ";
}



