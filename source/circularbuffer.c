/*
 * circularbuffer.c
 *
 *  Created on: Nov 11, 2019
 *      Author: madhu
 */

#include "circularbuffer.h"

/*
int circ_bbuf_push(circ_bbuf_t c*,uint8_t data)
{
	int next;
	next = c->head + 1; //next is where the circular buffer will point to
	if(next >= c->maxlen)
		next = 0;
	if(next == c->tail) // if head + 1 == tail, circular buffer is full
		return -1
	c->buffer[c->head] = data; // load data, then move
	c->head = next;
	return 0; //successful push
}


int circ_bbuf_pop(circ_bbuf_t c*,uint8_t *data)
{
	int next;

	if(c->head == c->tail) //if head = tail buffer is empty
		return -1;
	next = c->tail+1; // next is where the tail will point to after the read
	if(next >= c->maxlen)
		next = 0;
	*data = c->buffer[c->tail]; //read data and then move
	c->tail = next;
	return 0;	//return succesful read
}
*/

cbuf_handle_t circular_buf_init(uint8_t* buffer, size_t size)
{
//	assert(buffer && size);

	cbuf_handle_t cbuf;
	//cbuf->buffer = (uint8_t *)malloc(sizeof(uint8_t*)size);
//	assert(cbuf);

//	cbuf->buffer = buffer;
	cbuf->max = size;
	cbuf->head = buffer;
	cbuf->tail = buffer;
	cbuf->count = 0;
	cbuf->full = false;
//	circ_bbuf_t(cbuf);

//	assert(circular_buf_empty(cbuf));

	return cbuf;
}

void circular_buf_reset(cbuf_handle_t cbuf)
{
    //assert(cbuf);

    cbuf->head = 0;
    cbuf->tail = 0;
    cbuf->full = false;
}

buffer_errors circular_buf_free(cbuf_handle_t cbuf)
{
	free(cbuf->buffer);
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
/*	assert(cbuf);

    return cbuf->full; */
}

buffer_errors circular_buf_empty(cbuf_handle_t cbuf)
{
	if(cbuf == NULL)
		return buffer_null;
	else if((cbuf->count) == 0)
		return buffer_empty;
	else
		return buffer_not_empty;
/*	assert(cbuf);

    return (!cbuf->full && (cbuf->head == cbuf->tail)); */
}

buffer_errors circular_buf_initialized(cbuf_handle_t cbuf)
{
	/* Ensure the buffer pointers are all valid */
	if(cbuf->buffer && cbuf->head && cbuf->tail)
		return buffer_init_success;
	else
		return buffer_init_fail;
}

size_t circular_buf_capacity(cbuf_handle_t cbuf)
{
	assert(cbuf);

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

	/*
	assert(cbuf);

	size_t size = cbuf->max;

	if(!cbuf->full)
	{
		if(cbuf->head >= cbuf->tail)
		{
			size = (cbuf->head - cbuf->tail);
		}
		else
		{
			size = (cbuf->max + cbuf->head - cbuf->tail);
		}
	}

	return size; */
}

/*
static void advance_pointer(cbuf_handle_t cbuf)
{
	assert(cbuf);

	if(cbuf->full)
   	{
		cbuf->tail = (cbuf->tail + 1) % cbuf->max;
	}

	cbuf->head = (cbuf->head + 1) % cbuf->max;
	cbuf->full = (cbuf->head == cbuf->tail);
}


static void retreat_pointer(cbuf_handle_t cbuf)
{
	assert(cbuf);

	cbuf->full = false;
	cbuf->tail = (cbuf->tail + 1) % cbuf->max;
}
*/

buffer_errors circular_buf_put2(cbuf_handle_t cbuf, uint8_t data) //push
{
//    int r = -1;

//    assert(cbuf && cbuf->buffer);

    if(cbuf == NULL)
    	return buffer_null;
    else if(circular_buf_full(cbuf) == buffer_full)//cbuf->count == cbuf->max)
    		return buffer_full;
    else if(cbuf->head >= ((cbuf->buffer)+(cbuf->max)))
    {
    	*(cbuf->head) = data;
    	cbuf->head = cbuf->buffer;
    	cbuf->count++;
    	return buffer_success;
    }
    else
    {
    	*(cbuf->head) = data;
    	cbuf->head++;
    	cbuf->count++;
    	return buffer_success;
    }

    /*if(cbuf->head > cbuf->max)
    		{
    		}
    	}
    }
    if(!circular_buf_full(cbuf))
    {
        cbuf->buffer[cbuf->head] = data;
//      advance_pointer(cbuf);
        assert(cbuf);

		if(cbuf->full)
   		{
			cbuf->tail = (cbuf->tail + 1) % cbuf->max;
		}

		cbuf->head = (cbuf->head + 1) % cbuf->max;
		cbuf->full = (cbuf->head == cbuf->tail);
        r = 0;
    }

    return r;
    */
}

buffer_errors circular_buf_get(cbuf_handle_t cbuf, uint8_t * data) //pop
{

    if(cbuf == NULL)
    	return buffer_null;
    else if(circular_buf_empty(cbuf) == buffer_empty)//cbuf->count == cbuf->max)
    		return buffer_empty;
    else if(cbuf->tail > ((cbuf->buffer)+(cbuf->max)))
    {
    	*data = *(cbuf->tail);
    	cbuf->tail = cbuf->buffer;
    	cbuf->count--;
    	return buffer_success;
    }
    else
    {
    	*data = *(cbuf->tail);
    	cbuf->tail++;
    	cbuf->count--;
    	return buffer_success;
    }
 /*   assert(cbuf && data && cbuf->buffer);

    int r = -1;

    if(!circular_buf_empty(cbuf))
    {
        *data = cbuf->buffer[cbuf->tail];
    //    retreat_pointer(cbuf);
    	assert(cbuf);

    	cbuf->full = false;
    	cbuf->tail = (cbuf->tail + 1) % cbuf->max;

        r = 0;
    }

    return r; */
}

