#include "stdafx.h"
#include "queue.h"
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define FLAG_EMPTY	0
#define FLAG_ENTER	1
#define FLAG_READY	2
#define FLAG_DEQUE	3
		

Queue* QueueInit(int power_num, int element_size)
{
	Queue *q = (Queue *)calloc(1, sizeof(Queue));
	q->element_size = element_size;
	q->length = (1 << power_num);
	q->data = (char *)malloc(q->element_size * q->length);
	q->flags = (char *)calloc(1, q->length);
	return q;
}
int EnQueue(Queue *queue, void *element)
{
	if (queue->element_num >= queue->length)
		return -1;
	int index;
	char *flag;
	do {
		index = queue->index_tail;
		flag = queue->flags + index;
#ifdef _MSC_VER
	} while (FLAG_ENTER == InterlockedCompareExchange((unsigned *)flag, FLAG_ENTER, FLAG_EMPTY));
#else
	} while (!__sync_bool_compare_swap(flag, FLAG_EMPTY, FLAG_ENTER));
#endif
	memcpy(queue->data+queue->element_size*index, element, queue->element_size);
	int update_index = (index + 1) & (queue->length - 1);

#ifdef _MSC_VER
	InterlockedCompareExchange((unsigned *)&queue->index_tail, update_index, index);
	InterlockedExchange((unsigned *)flag, FLAG_READY);
	InterlockedIncrement((unsigned *)&queue->element_num);
#else
	__sync_bool_compare_and_swap(&queue->index_head, index, update_index);
	__sync_fetch_and_add(flag, 1);
	__sync_fetch_and_add(&queue->element_num, 1);
#endif

	return queue->element_num;
}
int DeQueue(Queue *queue, void *element)
{
	if (queue->element_num <= 0)
		return -1;
	int index;
	char *flag;
	do {
		index = queue->index_head;
		flag = queue->flags + index;
#ifdef _MSC_VER
	} while (FLAG_DEQUE == InterlockedCompareExchange((unsigned *)flag, FLAG_DEQUE, FLAG_READY));
#else
	} while (!__sync_bool_compare_swap(flag, FLAG_READY, FLAG_DEQUE));
#endif
	memcpy(element, queue->data + queue->element_size*index, queue->element_size);
	int update_index = (index + 1) & (queue->length - 1);
#ifdef _MSC_VER
	InterlockedCompareExchange((unsigned *)&queue->index_head, update_index, index);
	InterlockedExchange((unsigned *)flag, FLAG_EMPTY);
	InterlockedDecrement((unsigned *)&queue->element_num);
#else
	__sync_bool_compare_and_swap(&queue->index_head, index, update_index);
	__sync_fetch_and_sub(flag, 3);
	__sync_fetch_and_sub(&queue->element_num, 1);
#endif

	return queue->element_num;
}
void QueueFree(Queue *queue)
{
	if (queue->flags)
		free(queue->flags);
	if (queue->data)
		free(queue->data);
	free(queue);
}