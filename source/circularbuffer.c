/*
 * circularbuffer.c
 *
 *  Created on: Nov 11, 2019
 *      Author: madhu
 *      https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/
 */

#include "circularbuffer.h"

extern log_level log_level_a;

cbuf_handle_t circular_buf_init(size_t size)
{
	uint8_t* buffer_init;
	cbuf_handle_t cbuf = (circ_bbuf_t*)malloc(sizeof(circ_bbuf_t));
	buffer_init = (uint8_t*)malloc(sizeof(uint8_t)*size);
	cbuf->buffer = buffer_init;
	cbuf->max = size;
	cbuf->head = buffer_init;
	cbuf->tail = buffer_init;
	cbuf->count = 0;
	cbuf->realloc_done = false;

	return cbuf;
}

void circular_buf_reset(cbuf_handle_t cbuf)
{

    cbuf->head = cbuf->buffer;
    cbuf->tail = cbuf->buffer;
    cbuf->count = 0;
    cbuf->realloc_done = false;
}

buffer_errors circular_buf_free(cbuf_handle_t cbuf)
{
	//free(cbuf->buffer);
	free(cbuf);
	return buffer_freed;
}

buffer_errors circular_buf_full(cbuf_handle_t cbuf)
{

	if(cbuf == NULL)
		return buffer_null;
	else if(cbuf->count == cbuf->max)
		return buffer_full;
	else
		return buffer_not_full;
}

buffer_errors circular_buf_empty(cbuf_handle_t cbuf)
{
	if(cbuf == NULL)
		return buffer_null;
	else if((cbuf->count) == 0)
		return buffer_empty;
	else
		return buffer_not_empty;
}

buffer_errors circular_buf_initialized(cbuf_handle_t cbuf)
{
	if(cbuf->buffer && cbuf->head && cbuf->tail && (cbuf->count == 0))
		return buffer_init_success;
	else
		return buffer_init_fail;
}

buffer_errors circular_buf_valid(cbuf_handle_t cbuf)
{
	if(cbuf->buffer == NULL)
		return buffer_invalid;
	else
		return buffer_valid;
}
size_t circular_buf_capacity(cbuf_handle_t cbuf)
{

	return cbuf->max;
}

buffer_errors circular_buf_size(cbuf_handle_t cbuf)
{
    if(cbuf == NULL)
    	return buffer_null;
    else if(circular_buf_full(cbuf) == buffer_full)//cbuf->count == cbuf->max)
    		return buffer_full;
    else if(cbuf->head >= cbuf->tail)
    {
    	cbuf->max = (cbuf->head - cbuf->tail);
    	return buffer_success;
    }
    else
    {
    	cbuf->max = (cbuf->max + cbuf->head - cbuf->tail);
    	return buffer_success;
    }
}

buffer_errors circular_buf_put2(cbuf_handle_t * cbuf, uint8_t data) //push
{
	cbuf_handle_t cbuf1 = *cbuf;
    if(cbuf == NULL)
    	return buffer_null;
    else if(circular_buf_full(*cbuf) == buffer_full) //cbuf->count == cbuf->max)
    {
    	if(circular_buffer_realloc(*cbuf, (cbuf1->max)*3) == buffer_realloc_success)
    		cbuf1 = *cbuf;
    	return buffer_full;
    }
    else if(cbuf1->head >= ((cbuf1->buffer)+(cbuf1->max)))
    {
    	START_CRITICAL;
    	*(cbuf1->head) = data;
    	cbuf1->head = cbuf1->buffer;
    	cbuf1->count++;
    	END_CRITICAL;
    	return buffer_success;
    }
    else
    {
    	START_CRITICAL;
    	*(cbuf1->head) = data;
    	cbuf1->head++;
    	cbuf1->count++;
    	END_CRITICAL;
    	return buffer_success;
    }

}

buffer_errors circular_buf_get(cbuf_handle_t cbuf, uint8_t * data) //pop
{

    if(cbuf == NULL)
    	return buffer_null;
    else if(circular_buf_empty(cbuf) == buffer_empty)//cbuf->count == cbuf->max)
    		return buffer_empty;
    else if(cbuf->tail >= ((cbuf->buffer)+(cbuf->max)))
    {
    	START_CRITICAL;
    	*data = *(cbuf->tail);
    	cbuf->tail = cbuf->buffer;
    	cbuf->count--;
    	END_CRITICAL;
    	return buffer_success;
    }
    else
    {
    	START_CRITICAL;
    	*data = *(cbuf->tail);
    	cbuf->tail++;
    	cbuf->count--;
    	END_CRITICAL;
    	return buffer_success;
    }
}

buffer_errors circular_buffer_realloc(cbuf_handle_t * cbuf, size_t newSize)
{
	//used pointers to keep value of buffer when realloc called
	uint8_t data;
	if(circular_buf_full(*cbuf) == buffer_full)
	{
		cbuf_handle_t buffer_realloc;
		buffer_realloc = circular_buf_init(newSize);
		while(circular_buf_get(*cbuf, &data) == buffer_success)
			circular_buf_put2(buffer_realloc, data);

		circular_buf_free(*cbuf);
		*cbuf = buffer_realloc;
		cbuf_handle_t cbuf1;
		cbuf1 = *cbuf;
		cbuf1->realloc_done = true;

		return buffer_realloc_success;
	}

	log_string("Realloc not done, cause buffer is not full yet");

	return buffer_realloc_fail;

}


