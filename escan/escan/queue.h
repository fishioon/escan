#ifndef _LOCK_QUEUE_
#define _LOCK_QUEUE_

typedef struct _queue
{
	int element_size;
	int element_num;
	int length;
	int index_head;
	int index_tail;
	char *flags;
	char *data;
} Queue;

Queue* QueueInit(int element_size, int queue_size);
int EnQueue(Queue *queue, void *element);
int DeQueue(Queue *queue, void *element);
void QueueFree(Queue *queue);

#endif