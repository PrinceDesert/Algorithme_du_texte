#include <stdio.h>
#include <stdlib.h>
#include <hash_table_trie.h>
	
	
// hash : niveau espace mémoire c'est plus économique mais temps recherche plus long

// trouver une fonction hachage performante pour génèrer une clé pour le couple


Trie createTrie(int maxNode) {
	Trie t = (Trie) malloc(sizeof(struct _trie));
	if (t == NULL) {
		perror("malloc");
		return NULL;
	}
	t->maxNode = maxNode + 1;
	t->nextNode = 1;
	t->transition = (List *) calloc((size_t) (maxNode) + 1, sizeof(int *));
	// a chaque couple une fonction math qui génèe une clé
	
	// il peut avoir des conflits qui correspondent à 2 tables
	return NULL;
}
	
void insertInTrie(Trie trie, unsigned char *w) {
	 // applique la fonction de hash si pour cette key, il y a un maillon
}
	
int isInTrie(Trie trie, unsigned char *w) {
	
	//  applique la fonction de hash si pour cette key, si y'a un maillon qui correspond au couple 
	
	
	return 0;
}
	
int main(void) {

	return EXIT_SUCCESS;
}
