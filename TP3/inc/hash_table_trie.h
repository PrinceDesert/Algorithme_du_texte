#ifndef _HASH_TABLE_TRIE_H
#define _HASH_TABLE_TRIE_H
	
#include "transition_list.h"
	
struct _trie {
	int maxNode; /* Nombre maximal de noeuds du trie */
	int nextNode; /* Indice du prochain noeud disponible */
	List *transition; /* listes d’adjacence */
	char *finite; /* etats terminaux */
};
	
typedef struct _trie *Trie;
	
Trie createTrie(int maxNode);
void insertInTrie(Trie trie, unsigned char *w);
int isInTrie(Trie trie, unsigned char *w);
	
#endif
