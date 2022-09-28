#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <hash_table_trie.h>
	
	
// hash : niveau espace mémoire c'est plus économique mais temps recherche plus long
// trouver une fonction hachage performante pour génèrer une clé pour le couple
// il peut avoir des conflits qui correspondent à 2 tables


// appeler le hash pour le keyHash dans insert, isintrie
// vérifier 0.75

int hash(int startNode, unsigned char letter, int maxNode);
List searchSameLink(List linkToFind);
List searchLink(List link, unsigned char letter, int startNode);
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
	int keyHash = 0;
	List list = NULL;
	int startNode = 0; // pour le hash, pour le prochain maillon
	while (i < (size_t) trie->maxNode && w[idxW] != '\0') {
		for (size_t j = 0; j < LENGTH_ASCII_CHARS; j++) {
			if (j == w[idxW]) {
				keyHash = hash(startNode, (unsigned char) w[idxW], trie->maxNode);
				printf("Génération du hash : (%d,%c)=%d\n", (int) i, w[idxW], keyHash);
				list = (List) malloc(sizeof(struct _list));
				if (list == NULL) {
					perror("malloc");
					free(trie->transition);
					return;
				}
				// Positionne le maillon suivant
				if (trie->transition[keyHash] == NULL) {
					list->next = NULL;
				} else {
					list->next = trie->transition[keyHash];
				}
				list->startNode = (int) i;
				list->targetNode = trie->nextNode;
				list->letter = (unsigned char) j;
				/**
				 * Vérification s'il n'y a un couple identique déja inséré à cet emplacement (keyHash) 
				*/
				if (searchSameLink(list) == NULL) {
					// affecte en tête
					trie->transition[keyHash] = list;
					printf("couple (%d,%c)=%d, ajout du maillon = (%d,%c,%d)\n", 
						(int) i, w[idxW], keyHash, 
						list->startNode, list->letter, list->targetNode);
					// maillon suivant
					trie->nextNode++;
					startNode = list->targetNode;
				} else {
					printf("Le couple (%d,%c)=%d existe déja\n", (int) i, w[idxW], keyHash);
				}
				break;
			}
		}
		idxW++;
		i++;
	}
	trie->finite[trie->nextNode-1] = '1';
}

/** 
 * recherche dans list un maillon qui est le même que celui linkToFind
 * pour cela, regarde le linkToFind->next puis linkToFind->next->next ect..
 * retourne null si existe pas sinon retourne le suivant
*/
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

//  applique la fonction de hash si pour cette keyHash, si y'a un maillon qui correspond au couple 
int isInTrie(Trie trie, unsigned char *w) {
	size_t i = 0;
	int idxW = 0;
	int keyHash = 0;
	List list = NULL;
	int startNode = 0;
	while (i < (size_t) trie->maxNode && w[idxW] != '\0') {
		//keyHash = hash(startNode, (unsigned char) w[idxW], trie->maxNode);
		
		// récupère le maillon en tête
		list = trie->transition[keyHash];
		// recherche à partir de ce maillon, le maillon correspondant à la lettre mais je sais pas si il faut aussi le startNode
		/*x = getNode(l, w[idxW], 
		if (x == NULL) // error*/
		
		// Un problème est que si il y a déja deux insert, et là le startNode commence à 4 et pas à 0
		// mais jsp si c un pb car si c dans l'ordre (0,a; 1,b ect donc c ok)
		
		List tmp = searchLink(list, w[idxW], startNode);
		if (tmp == NULL) {
			return 0;
		}
		startNode = list->targetNode;
		idxW++;
		i++;
	}
	return trie->finite[startNode] == '1';
}

/**
 * retourne le maillon correspondant à la lettre et au startNode
*/
List searchLink(List link, unsigned char letter, int startNode) {
	List current = link;
	while (current != NULL) {
		if (current->letter == letter 
			&& current->startNode == startNode) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}

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
