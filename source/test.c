/* @file test.c
 * @brief Unit test cases for PES_Project4
 * @author : Akshita Bhasin and Madhukar Arora
 * @date : 11/03/2019
 * @version 1.0
 */

#include "test.h"

/*
 Function Name: unit_test_cases
 Function arguments: void
 Function return type: void
 Brief: performs unit tests on various memory functions
*/

void unit_test_cases(void)
{
	uint8_t a=1;
	cbuf_handle_t test_buffer;

	UCUNIT_TestcaseBegin("Testing circular buffer - init\r\n");
	test_buffer= circular_buf_init(4);

	UCUNIT_CheckIsNotNull(test_buffer);
	UCUNIT_TestcaseEnd();

	//Test case for allocate bytes
	UCUNIT_TestcaseBegin("Testing circular buffer - put\r\n");
	for(uint8_t i=0; i<4; i++)
	{
		UCUNIT_CheckIsEqual(circular_buf_put2(test_buffer, i), buffer_success);
	}
	UCUNIT_CheckIsEqual(circular_buf_put2(test_buffer, a), buffer_full);
	UCUNIT_TestcaseEnd();

	UCUNIT_TestcaseBegin("Testing circular buffer - get\r\n");
	for(uint8_t i=0; i<10; i++)
	{
		UCUNIT_CheckIsEqual(circular_buf_get(test_buffer, &i), buffer_success);
	}
	UCUNIT_CheckIsEqual(circular_buf_get(test_buffer, &a), buffer_empty);
	UCUNIT_TestcaseEnd();

	UCUNIT_TestcaseBegin("Testing circular buffer put again\r\n");
	for(uint8_t i=0; i<10; i++)
	{
		UCUNIT_CheckIsEqual(circular_buf_put2(test_buffer, i), buffer_success);
	}
	UCUNIT_CheckIsEqual(circular_buf_put2(test_buffer, a), buffer_full);
	UCUNIT_TestcaseEnd();

	circular_buf_free(test_buffer);

	UCUNIT_TestcaseBegin("Testing circular buffer free\r\n");
	test_buffer = circular_buf_init(4);
	UCUNIT_CheckIsEqual(circular_buf_free(test_buffer), buffer_freed);
	UCUNIT_CheckIsNull(test_buffer);
	UCUNIT_CheckIsNull(test_buffer->buffer);
	UCUNIT_TestcaseEnd();
	/*
	I2C_write_byte(0x01, 0x62);
	delay_loop(10000);
	uint8_t data = i2c_read_byte(0x90, 0x01);
	UCUNIT_CheckIsEqual(data, 0x62);
	UCUNIT_TestcaseEnd();

	UCUNIT_TestcaseBegin("Testing temperature register read byte setting\r\n");
	int8_t tempC = i2c_read_bytes(0x90, 0x00);
	UCUNIT_CheckIs8Bit(tempC);
	UCUNIT_TestcaseEnd();

	UCUNIT_TestcaseBegin("Testing post test case pass\r\n");
	uint8_t post_value = i2c_read_byte(0x90, 0x01);
	UCUNIT_CheckIsEqual(post_value,0x60);
	UCUNIT_CheckIsEqual(post_value,0x62);
	UCUNIT_TestcaseEnd();

	UCUNIT_TestcaseBegin("Testing disconnect test case\r\n");
	uint8_t discon_value = i2c_read_byte(0x90, 0x01);
	UCUNIT_CheckIsEqual(discon_value,0x00);
	UCUNIT_TestcaseEnd();

	UCUNIT_TestcaseBegin("Testing TL0 and TH0 before setting them\r\n");
	uint8_t tl0_value = i2c_read_byte(0x90, 0x02);
	UCUNIT_CheckIsEqual(tl0_value,0x20);
	uint8_t th0_value = i2c_read_byte(0x90, 0x03);
	UCUNIT_CheckIsEqual(th0_value,0x40);
	UCUNIT_TestcaseEnd();

	uint8_t tl0a=  0x1d;
	uint8_t tl0b= 0x00;

	uint8_t th0a = 0x3b;
	uint8_t th0b = 0x00;

	I2C_write_bytes(0x02, tl0a, tl0b);
	delay_loop(10000);
	I2C_write_bytes(0x03, th0a, th0b);

	UCUNIT_TestcaseBegin("Testing TL0 and TH0 after setting them\r\n");
	uint8_t tl0_value_1 = i2c_read_byte(0x90, 0x02);
	UCUNIT_CheckIsEqual(tl0_value_1,0x1d);
	uint8_t th0_value_1 = i2c_read_byte(0x90, 0x03);
	UCUNIT_CheckIsEqual(th0_value_1,0x3b);
	UCUNIT_TestcaseEnd();

	UCUNIT_TestcaseBegin("Testing Alert Pin Polarity\r\n");
	I2C_write_byte(0x01, 0x60);
	uint8_t alert_positive = i2c_read_byte(0x90, 0x01);
	UCUNIT_CheckIsEqual(alert_positive,0x60);
	I2C_write_byte(0x01, 0x64);
	uint8_t alert_negative = i2c_read_byte(0x90, 0x01);
	UCUNIT_CheckIsEqual(alert_negative,0x64);
	UCUNIT_TestcaseEnd();

	UCUNIT_TestcaseBegin("Testing Thermostat Mode bit pin\r\n");
	I2C_write_byte(0x01, 0x60);
	uint8_t comparator_mode = i2c_read_byte(0x90, 0x01);
	UCUNIT_CheckIsEqual(comparator_mode,0x60);
	I2C_write_byte(0x01, 0x62);
	uint8_t interrupt_mode = i2c_read_byte(0x90, 0x01);
	UCUNIT_CheckIsEqual(interrupt_mode,0x62);
	UCUNIT_TestcaseEnd();

	UCUNIT_TestcaseBegin("State Machine Test case\r\n");
	UCUNIT_TestcaseBegin("State Machine Init Test Case- Pass\r\n");
	log_string("Initial values test");
	UCUNIT_CheckIsEqual(current_event, Complete);
	UCUNIT_CheckIsEqual(current_state, Temp_Reading);
	UCUNIT_TestcaseEnd();

	UCUNIT_TestcaseBegin("State Machine Test case\r\n");
	UCUNIT_TestcaseBegin("State Machine Init Test Case- Fail\r\n");
	log_string("Initial values test");
	UCUNIT_CheckIsEqual(current_event, Disconnect);
	UCUNIT_CheckIsEqual(current_state, Disconnected);
	UCUNIT_TestcaseEnd();

	UCUNIT_TestcaseEnd();
 */
}

/*int main(void) {
	//Initializing board pins
//#ifdef TEST
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
//#endif
	//Calling function to run memory tests
	unit_test_cases();
	return 0;
} */
