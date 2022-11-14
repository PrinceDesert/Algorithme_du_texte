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
	
#endif
