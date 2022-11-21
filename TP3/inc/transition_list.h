#ifndef _TRANSITION_LIST_H
#define _TRANSITION_LIST_H
	
struct _list {
	int startNode, /* etat de depart de la transition */
	targetNode; /* cible de la transition */
	unsigned char letter; /* etiquette de la transition */
	struct _list *next; /* maillon suivant */
};
typedef struct _list *List;
	
	
#endif
