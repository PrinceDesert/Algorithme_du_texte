#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <hash_table_trie.h>
	
	
// hash : niveau espace mémoire c'est plus économique mais temps recherche plus long
// trouver une fonction hachage performante pour génèrer une clé pour le couple
// il peut avoir des conflits qui correspondent à 2 tables


// appeler le hash pour le key dans insert, isintrie
// vérifier 0.75

int hash(int startNode, unsigned char letter, int maxNode);
List searchSameLink(List first);
// Trie prefix(unsigned char *w); // les préfixes du mot w
// Trie suffix(unsigned char *w); // les suffixes du mot w
// Trie factor(unsigned char *w); // les facteurs du mot w
#define LENGTH_ASCII_CHARS UCHAR_MAX + 1
	
Trie createTrie(int maxNode) {
	Trie t = (Trie) malloc(sizeof(struct _trie));
	if (t == NULL) {
		perror("malloc");
		return NULL;
	}
	t->maxNode = maxNode + 1;
	t->nextNode = 1;
	// pile de clé
	t->transition = (List *) malloc((size_t) (maxNode) * sizeof(List *));
	// printf("taille de la pile : %lu\n", (size_t) (maxNode) * sizeof(List *));
	if (t->transition == NULL) {
		perror("malloc");
		free(t->transition);
		return NULL;
	}
	// +1 : '\0'
	size_t lenFinite = (size_t) t->maxNode + 1;
	t->finite = (char *) calloc(lenFinite, sizeof(char));
	if (t->finite == NULL) {
		perror("calloc");
		free(t->finite);
		return NULL;
	}
	memset(t->finite, '0', lenFinite);
	return t;
}
	
void insertInTrie(Trie trie, unsigned char *w) {
	size_t i = 0;
	int idxW = 0;
	while (i < (size_t) trie->maxNode && w[idxW] != '\0') {
		for (size_t j = 0; j < LENGTH_ASCII_CHARS; j++) {
			if (j == w[idxW]) {
				int key = hash((int) i, (unsigned char) w[idxW], trie->maxNode);
				printf("Génération du hash : (%d,%c)=%d\n", (int) i, w[idxW], key);
				List list = (List) malloc(sizeof(struct _list));
				if (list == NULL) {
					perror("malloc");
					free(trie->transition);
					return;
				}
				// Positionne le maillon suivant
				if (trie->transition[key] == NULL) {
					list->next = NULL;
				} else {
					list->next = trie->transition[key];
				}
				list->startNode = trie->nextNode;
				list->targetNode = trie->nextNode + 1;
				list->letter = (unsigned char) j;
				/**
				 * Vérification s'il n'y a un couple identique déja inséré à cet emplacement (key) 
				*/
				if (searchSameLink(list) == NULL) {
					// affecte en tête
					trie->transition[key] = list;
				} else {
					printf("Le couple (%d,%c)=%d existe déja\n", (int) i, w[idxW], key);
				}
				break;
			}
		}
		idxW++;
		i++;
	}
}
	
	
// recherche dans list un maillon qui est le même que celui linkToFind
// pour cela, on regarde le first->next puis first->next->next ect..
// retourne null si existe pas, retourne le suivant
List searchSameLink(List linkToFind) {
	List current = linkToFind->next;
	while (linkToFind != NULL && current != NULL) {
		if (linkToFind->startNode == current->startNode 
			&& linkToFind->letter == current->letter 
			&& linkToFind->targetNode == current->targetNode) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}
/*
// Retourne le maillon de l correspondant au char c et startNode
List getNode(List l, char c, int startNode) {
	List current = l;
	while (current != NULL) {
		if (first->startNode == current->startNode && first->letter == current->letter) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}
	
int isInTrie(Trie trie, unsigned char *w) {
	
	//  applique la fonction de hash si pour cette key, si y'a un maillon qui correspond au couple 
	
	size_t i = 0;
	int idxW = 0;
	
	while (i < (size_t) trie->maxNode && w[idxW] != '\0') {
		int key = 0;
		// récupère le noeud correspondant à clé et égale à la lettre w[idxW]
		List l = trie->transition[key];
		// recherche le maillon correspondant à la lettre mais je sais pas si il faut aussi le startNode
		x = getNode(l, w[idxW], 
		if (x == NULL) // error
		
		
		idxW++;
	}
	
	// pour debug
	w[0] = '1';
	return w[0] == '1';
}*/

void freeTrie(Trie t) {
	if (t != NULL) {
		for (size_t i = 0; i < (size_t) t->maxNode; i++) {
			free(t->transition[i]);
		}
		free(t->transition);
		free(t->finite);
	}
}
	
int hash(int startNode, unsigned char letter, int maxNode) {
	return (startNode + letter) % (maxNode - 1);
	// 1 + 'a' % 50
}
	
int main(void) {
	int maxNode = 20;
	Trie trie = createTrie(maxNode);
	if (trie == NULL) {
		return EXIT_FAILURE;
	}
	insertInTrie(trie, (unsigned char *) "atcg");
	return EXIT_SUCCESS;
}
