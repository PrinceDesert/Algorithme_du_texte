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

int hash(int startNode, unsigned char letter, int maxNode);
List searchSameLink(List linkToFind);
List searchLink(List link, int startNode, unsigned char letter);
void appendLink(List first, List link);
Trie prefix(unsigned char *w); // les préfixes du mot w
Trie suffix(unsigned char *w); // les suffixes du mot w
// Trie factor(unsigned char *w); // les facteurs du mot w
	
#include <limits.h>
#define CHAR_LENGTH UCHAR_MAX + 1
	
#endif
