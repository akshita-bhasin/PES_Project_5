/* @file test.c
 * @brief Unit test cases for PES_Project5
 * @author : Akshita Bhasin and Madhukar Arora
 * @date : 11/10/2019
 * @version 1.0
 */

#include "test.h"

uint8_t a=1;

/*
 Function Name: unit_test_cases
 Function arguments: void
 Function return type: void
 Brief: calls various test case functions for the circular buffer
*/
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

/*
 Function Name: buffer_init
 Function arguments: void
 Function return type: void
 Brief: testing buffer initialization
*/
void buffer_init(void)
{
	cbuf_handle_t test_buffer;

	UCUNIT_TestcaseBegin("Testing circular buffer - init\r\n");
	test_buffer= circular_buf_init(4);
	UCUNIT_CheckIsNotNull(test_buffer);
	UCUNIT_TestcaseEnd();
	circular_buf_free(test_buffer);
}


/*
 Function Name: buffer_put
 Function arguments: void
 Function return type: void
 Brief: testing adding an element to the circular buffer
*/
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


/*
 Function Name: buffer_get
 Function arguments: void
 Function return type: void
 Brief: testing removing an element from the circular buffer
*/
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

/*
 Function Name: buffer_overfill
 Function arguments: void
 Function return type: void
 Brief: testing full condition of the circular buffer
*/
void buffer_overfill(void)
{
	cbuf_handle_t test_buffer;

	UCUNIT_TestcaseBegin("Testing circular buffer overfill\r\n");
	test_buffer= circular_buf_init(4);
	for(uint8_t i=0; i<10; i++)
	{
		if((test_buffer->realloc_done) == false)
		{
			UCUNIT_CheckIsEqual(circular_buf_put2(&test_buffer, i), buffer_success);
		}
	}
	UCUNIT_CheckIsEqual(circular_buf_put2(&test_buffer, a), buffer_full);
	UCUNIT_TestcaseEnd();
	circular_buf_free(test_buffer);
}

/*
 Function Name: buffer_overempty
 Function arguments: void
 Function return type: void
 Brief: testing empty condition of the circular buffer
*/
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

/*
 Function Name: buffer_data_push_pop
 Function arguments: void
 Function return type: void
 Brief: testing if the added and removed element to the circular buffer are same
*/
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


/*
 Function Name: buffer_free
 Function arguments: void
 Function return type: void
 Brief: testing freeing of the circular buffer
*/
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

/*
 Function Name: buffer_realloc
 Function arguments: void
 Function return type: void
 Brief: reallocating the circular buffer
*/
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
