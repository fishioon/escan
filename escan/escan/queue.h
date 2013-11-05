#ifndef _LOCK_QUEUE_
#define _LOCK_QUEUE_

typedef struct _queue Queue;

Queue* QueueInit(int power_num, int element_size);
int QueuePush(Queue *queue, void *element);
int QueuePop(Queue *queue, void *element);
void QueueFree(Queue *queue);

#endif