#ifndef _QUEUE_H
#define _QUEUE_H
	
typedef struct _QueueElement {
	int value;
	struct _QueueElement *next;
} _QueueElement;

typedef struct _QueueElement QueueElement;
	
typedef struct _Queue {
	QueueElement *first;
	QueueElement *last;
	int nbElements;
} _Queue;
	
typedef struct _Queue *Queue;
	
void initQueue(Queue queue);
int queueIsEmpty(Queue queue);
int queueLength(Queue queue);
int queueFirst(Queue queue);
int queueLast(Queue queue);
void queuePush(Queue queue, int value);
void queuePop(Queue queue);
void queueClear(Queue queue);
void queueToString(Queue queue);
	
#endif
