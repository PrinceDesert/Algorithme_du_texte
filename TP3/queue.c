#include <stdio.h>
#include <stdlib.h>
	
typedef struct QueueElement {
	int value;
	struct QueueElement *next;
} QueueElement;
QueueElement *first = NULL;
QueueElement *last = NULL;
int nbElements = 0;
int queueIsEmpty();
int queueLength();
int queueFirst();
int queueLast();
void queuePush(int value);
void queuePop();
void queueClear();
void queueToString();
	
int main(void) {
	fprintf(stdout, "Queue length : %d\n", queueLength());
	int nbElements = 10;
	fprintf(stdout, "Queue push : %d  (nbElements to push)\n", nbElements);
	for (int i = 0; i < nbElements; i++) {
		queuePush(i+1);
	}
	queueToString();
	fprintf(stdout, "Queue first : %d\n", queueFirst());
	fprintf(stdout, "Queue last : %d\n", queueLast());
	int pop = nbElements - ((int) nbElements/2);
	fprintf(stdout, "Queue pop : %d (nbElements to pop) \n", pop);
	for (int i = 0; i < pop; i++) {
		queuePop();
	}
	queueToString();
	fprintf(stdout, "Queue clear\n");
	queueClear();
	fprintf(stdout, "Queue length : %d\n", queueLength());
}
	
int queueIsEmpty() {
	if (first == NULL && last == NULL) {
		return 1;
	}
	return 0;
}
	
int queueLength() {
	return nbElements;
}
	
int queueFirst() {
	if (queueIsEmpty()) {
		exit(EXIT_FAILURE);
	}
	return first->value;
}
	
int queueLast() {
	if (queueIsEmpty()) {
		exit(EXIT_FAILURE);
	}
	return last->value;
}
	
void queuePush(int value) {
	QueueElement *element = (QueueElement *) malloc(sizeof(QueueElement));
	if (element == NULL) {
		fprintf(stderr, "Error : malloc to queuePush\n");
		exit(EXIT_FAILURE);
	}
	element->value = value;
	element->next = NULL;
	if (queueIsEmpty()) {
		first = element;
		last = element;
	} else {
		last->next = element;
		last = element;
	}
	nbElements++;
}
	
void queuePop() {
	if (queueIsEmpty()) {
		fprintf(stdout, "queuePop : Queue is empty\n");
		return;
	}
	QueueElement *tmp = first;
	if (first == last) {
		first = NULL;
		last = NULL;
	} else {
		first = first->next;
	}
	free(tmp);
	nbElements--;
}
	
void queueClear() {
	if (queueIsEmpty()) {
		fprintf(stdout, "queueClear : Queue is empty\n");
		return;
	}
	while (!queueIsEmpty()) {
		queuePop();
	}
}
	
void queueToString() {
	if (queueIsEmpty()) {
		fprintf(stdout, "queueToString : Queue is empty\n");
		return;
	}
	fprintf(stdout, "Queue : ");
	QueueElement *tmp = first;
	while (tmp != NULL) {
		fprintf(stdout, "|%d|->", tmp->value);
		tmp = tmp->next;
	}
	fprintf(stdout, "NULL\n");
}
	
