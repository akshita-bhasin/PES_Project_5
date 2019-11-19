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

uint8_t a=1;

void unit_test_cases(void)
{
	buffer_init();
	buffer_put();
	buffer_get();
	buffer_overfill();
	buffer_overempty();
	buffer_data_push_pop();
	buffer_free();
	buffer_realloc();
}

void buffer_init(void)
{
	cbuf_handle_t test_buffer;

	UCUNIT_TestcaseBegin("Testing circular buffer - init\r\n");
	test_buffer= circular_buf_init(4);
	UCUNIT_CheckIsNotNull(test_buffer);
	UCUNIT_TestcaseEnd();
	circular_buf_free(test_buffer);
}

void buffer_put(void)
{
	cbuf_handle_t test_buffer;

	UCUNIT_TestcaseBegin("Testing circular buffer - put\r\n");
	test_buffer= circular_buf_init(4);
	for(uint8_t i=0; i<4; i++)
	{
		UCUNIT_CheckIsEqual(circular_buf_put2(&test_buffer, i), buffer_success);
	}
	UCUNIT_CheckIsEqual(circular_buf_put2(&test_buffer, a), buffer_full);
	UCUNIT_TestcaseEnd();
	circular_buf_free(test_buffer);
}

void buffer_get(void)
{
	cbuf_handle_t test_buffer;

	UCUNIT_TestcaseBegin("Testing circular buffer - get\r\n");
	test_buffer= circular_buf_init(4);
	for(uint8_t i=0; i<4; i++)
	{
		UCUNIT_CheckIsEqual(circular_buf_get(test_buffer, &i), buffer_success);
	}
	UCUNIT_CheckIsEqual(circular_buf_get(test_buffer, &a), buffer_empty);
	UCUNIT_TestcaseEnd();
	circular_buf_free(test_buffer);
}

void buffer_overfill(void)
{
	cbuf_handle_t test_buffer;

	UCUNIT_TestcaseBegin("Testing circular buffer overfill\r\n");
	test_buffer= circular_buf_init(4);
	for(uint8_t i=0; i<10; i++)
	{
		if(test_buffer->realloc_done == false)
			UCUNIT_CheckIsEqual(circular_buf_put2(&test_buffer, i), buffer_success);
	}
	UCUNIT_CheckIsEqual(circular_buf_put2(&test_buffer, a), buffer_full);
	UCUNIT_TestcaseEnd();
	circular_buf_free(test_buffer);
}

void buffer_overempty(void)
{
	cbuf_handle_t test_buffer;

	UCUNIT_TestcaseBegin("Testing circular buffer over empty \r\n");
	test_buffer= circular_buf_init(4);
	for(uint8_t i=0; i<10; i++)
	{
		UCUNIT_CheckIsEqual(circular_buf_get(test_buffer, &i), buffer_success);
	}
	UCUNIT_CheckIsEqual(circular_buf_get(test_buffer, &a), buffer_empty);
	UCUNIT_TestcaseEnd();
	circular_buf_free(test_buffer);
}

void buffer_data_push_pop(void)
{
	cbuf_handle_t test_buffer;

	UCUNIT_TestcaseBegin("Testing circular buffer data push/pop \r\n");
	test_buffer= circular_buf_init(4);
	UCUNIT_CheckIsEqual(circular_buf_put2(&test_buffer, 0xDD), buffer_success);
	uint8_t a;
	UCUNIT_CheckIsEqual(circular_buf_get(test_buffer, &a), buffer_success);
	UCUNIT_CheckIsEqual(a, 0xDD);
	UCUNIT_TestcaseEnd();
	circular_buf_free(test_buffer);
}

void buffer_free(void)
{
	cbuf_handle_t test_buffer;

	UCUNIT_TestcaseBegin("Testing circular buffer free\r\n");
	test_buffer = circular_buf_init(4);
	UCUNIT_CheckIsEqual(circular_buf_free(test_buffer), buffer_freed);
	UCUNIT_CheckIsNull(test_buffer);
	UCUNIT_TestcaseEnd();
	circular_buf_free(test_buffer);
}

void buffer_realloc(void)
{
	cbuf_handle_t test_buffer;

	UCUNIT_TestcaseBegin("Testing circular buffer Realloc\r\n");
	test_buffer = circular_buf_init(4);
	for(uint8_t i=0; i<5; i++)
	{
		UCUNIT_CheckIsEqual(circular_buf_put2(&test_buffer, i), buffer_success);
	}
	UCUNIT_CheckIsEqual(test_buffer->realloc_done, true);
	UCUNIT_TestcaseEnd();
	circular_buf_free(test_buffer);
}
