#ifndef _TRANSITION_MATRIX_TRIE_H
#define _TRANSITION_MATRIX_TRIE_H
	
// Matrice de transitions
struct _trie {
	int maxNode; /* Nombre maximal de noeuds du trie */
	int nextNode; /* Indice du prochain noeud disponible */
	int **transition; /* matrice de transition */
	char *finite; /* etats terminaux */
};
	
typedef struct _trie *Trie;
	
Trie createTrie(int maxNode);
void insertInTrie(Trie trie, unsigned char *w);
int isInTrie(Trie trie, unsigned char *w);

void printTransition(Trie trie);
void freeTrie(Trie t);
Trie prefix(unsigned char *w); // les préfixes du mot w
Trie suffix(unsigned char *w); // les suffixes du mot w
// Trie factor(unsigned char *w); // les facteurs du mot w

#define FIRST_STATE 0
#define EMPTY_TRANSITION -1

#include <limits.h>
#define LENGTH_ASCII_CHARS UCHAR_MAX + 1
	
#endif
