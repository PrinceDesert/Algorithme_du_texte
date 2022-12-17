#include <stdio.h>
#include <stdlib.h>
#include <queue.h>

/*
int main(void) {
	
	Queue queue;
	queue = initQueue();
	
	fprintf(stdout, "Queue length : %d\n", queueLength(queue));
	int nbElements = 10;
	fprintf(stdout, "Queue push : %d  (nbElements to push)\n", nbElements);
	for (int i = 0; i < nbElements; i++) {
		queuePush(queue, i+1);
	}
	
	queueToString(queue);
	fprintf(stdout, "Queue first : %d\n", queueFirst(queue));
	fprintf(stdout, "Queue last : %d\n", queueLast(queue));
	int pop = nbElements - ((int) nbElements/2);
	fprintf(stdout, "Queue pop : %d (nbElements to pop) \n", pop);
	for (int i = 0; i < pop; i++) {
		queuePop(queue);
	}
	queueToString(queue);
	fprintf(stdout, "Queue clear\n");
	queueClear(queue);
	fprintf(stdout, "Queue length : %d\n", queueLength(queue));
}
*/
	
Queue initQueue() {
	Queue queue = (Queue) malloc(sizeof(_Queue));
	if (queue == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	queue->first = NULL;
	queue->last = NULL;
	queue->nbElements = 0;
	return queue;
}
	
int queueIsEmpty(Queue queue) {
	if (queue->first == NULL && queue->last == NULL) {
		return 1;
	}
	return 0;
}
	
int queueLength(Queue queue) {
	return queue->nbElements;
}
	
int queueFirst(Queue queue) {
	if (queueIsEmpty(queue)) {
		exit(EXIT_FAILURE);
	}
	return queue->first->value;
}
	
int queueLast(Queue queue) {
	if (queueIsEmpty(queue)) {
		exit(EXIT_FAILURE);
	}
	return queue->last->value;
}
	
void queuePush(Queue queue, int value) {
	QueueElement *element = (QueueElement *) malloc(sizeof(QueueElement));
	if (element == NULL) {
		fprintf(stderr, "Error : malloc to queuePush\n");
		exit(EXIT_FAILURE);
	}
	element->value = value;
	element->next = NULL;
	if (queueIsEmpty(queue)) {
		queue->first = element;
		queue->last = element;
	} else {
		queue->last->next = element;
		queue->last = element;
	}
	queue->nbElements++;
}
	
void queuePop(Queue queue) {
	if (queueIsEmpty(queue)) {
		fprintf(stdout, "queuePop : Queue is empty\n");
		return;
	}
	QueueElement *tmp = queue->first;
	if (queue->first == queue->last) {
		queue->first = NULL;
		queue->last = NULL;
	} else {
		queue->first = queue->first->next;
	}
	free(tmp);
	queue->nbElements--;
}
	
void queueClear(Queue queue) {
	if (queueIsEmpty(queue)) {
		fprintf(stdout, "queueClear : Queue is empty\n");
		return;
	}
	while (!queueIsEmpty(queue)) {
		queuePop(queue);
	}
}
	
void queueDestroy(Queue queue) {
	queueClear(queue);
	if (queue != NULL) {
		free(queue);
	}
}
	
void queueToString(Queue queue) {
	if (queueIsEmpty(queue)) {
		fprintf(stdout, "queueToString : Queue is empty\n");
		return;
	}
	fprintf(stdout, "Queue : ");
	QueueElement *tmp = queue->first;
	while (tmp != NULL) {
		fprintf(stdout, "|%d|->", tmp->value);
		tmp = tmp->next;
	}
	fprintf(stdout, "NULL\n");
}
	
