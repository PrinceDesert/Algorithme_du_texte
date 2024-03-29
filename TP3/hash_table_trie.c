#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <hash_table_trie.h>
	
	
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
	for (int i = 0; i < maxNode; i++) {
		t->transition[i] = NULL;
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
		for (size_t j = 0; j < CHAR_LENGTH; j++) {
			if (j == w[idxW]) {
				keyHash = hash(startNode, (unsigned char) w[idxW], trie->maxNode);
				// printf("Génération du hash : (%d,%c)=%d\n", (int) i, w[idxW], keyHash);
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
				list->startNode = startNode;
				list->targetNode = trie->nextNode;
				list->letter = (unsigned char) j;
				// printf("|%d| => [%d,%c,%d]\n", keyHash, list->startNode, list->letter, list->targetNode);
				/**
				 * Vérification s'il n'y a un couple identique déja inséré à cet emplacement (keyHash) 
				*/
				if (searchSameLink(list) == NULL) {
					// affecte en tête
					trie->transition[keyHash] = list;
					/*
					printf("Pair : (%d,%c)=%d, adding link to %d => (%d,%c,%d)\n", 
						(int) i, w[idxW], keyHash, keyHash,
						list->startNode, list->letter, list->targetNode);
					*/
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
		keyHash = hash(startNode, (unsigned char) w[idxW], trie->maxNode);
		
		// récupère le maillon en tête
		list = trie->transition[keyHash];
		// recherche à partir de ce maillon, le maillon correspondant à la lettre mais je sais pas si il faut aussi le startNode
		// printf("searchLink (%d,%c)=%d\n", startNode, w[idxW], keyHash);
		List x = searchLink(list, startNode, w[idxW]);
		if (x == NULL) {
			// printf("Link not found for (%d,%c)=%d\n", startNode, w[idxW], keyHash);  
			return 0;
		}
		startNode = x->targetNode;
		idxW++;
		i++;
	}
	return trie->finite[startNode] == '1';
}

/**
 * retourne le maillon correspondant à la lettre et au startNode
*/
List searchLink(List link, int startNode, unsigned char letter) {
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

/**
 * ajoute le maillon link au dernière élement de first
*/
void appendLink(List first, List link) {
	if (first == NULL || link == NULL) return;
	List tmp = first;
	List last = tmp;
	while (tmp != NULL) {
		last = tmp;
		tmp = tmp->next;
	}
	last->next = link;
}

void freeTrie(Trie t) {
	if (t != NULL) {
		for (size_t i = 0; i < (size_t) t->maxNode; i++) {
			List current = t->transition[i];
			List next = NULL;
			while (current != NULL) {
				next = current->next;
				current = next;
				free(next);
			}
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

void printTransition(Trie trie) {
	printf("===========================\n");
	printf("== TRANSITION HASH TABLE ==\n");
	printf("===========================\n");
	size_t key = 0;
	List link = NULL;
	while (key < (size_t) trie->maxNode) {
		link = trie->transition[key];
		printf("[%lu] : ", key);
		if (link == NULL) {
			printf("NULL");
		}
		while (link != NULL) {
			printf("(%d,%c,%d) - ", link->startNode, link->letter, link->targetNode);
			if (link->next == NULL) {
				printf("NULL");
			}
			link = link->next;
		}
		printf("\n");
		key++;
	}
	printf("finite : ");
	for (size_t i = 0; i < (size_t) trie->maxNode + 1; i++) {
		printf("%c|", trie->finite[i]);
	}
	printf("\n");
}

Trie prefix(unsigned char *w) {
	if (w == NULL) return NULL;
	size_t w_len = strlen((const char *) w);
	int maxNode = (int) (w_len << 1);
	Trie t = createTrie(maxNode);
	for (size_t i = 0; i < w_len; i++) {
		char tmp[i + 2];
		memcpy(tmp, w, i + 1);
		tmp[i + 1] = '\0';
		insertInTrie(t, (unsigned char *) tmp);
	}
	return t;
}

Trie suffix(unsigned char *w) {
	if (w == NULL) return NULL;
	size_t w_len = strlen((const char *) w); 
	int maxNode = (int) (w_len << 1);
	Trie t = createTrie(maxNode);
	for (long int i = (long int) (w_len - 1); i >= 0; i--) {
		const char *suffix = (const char *) w + i;
		size_t suffix_len = strlen(suffix);
		char tmp[suffix_len + 1];
		memcpy(tmp, suffix, suffix_len);
		tmp[suffix_len] = '\0';
		insertInTrie(t, (unsigned char *) tmp);
	}
	return t;	
}
/*
int main(void) {
	int maxNode = 20;
	Trie trie = createTrie(maxNode);
	if (trie == NULL) {
		return EXIT_FAILURE;
	}
	const char *words[] = {"gtagct", "agv", "ag", NULL};
	const char *test_words[] = {"gtagct", "agv", "ag", NULL};
	for (size_t i = 0; words[i] != NULL; i++)
		insertInTrie(trie, (unsigned char *) words[i]);
	printTransition(trie);
	for (size_t i = 0; test_words[i] != NULL; i++) {
		if (isInTrie(trie, (unsigned char *) test_words[i])) {
			printf("Word %s is in trie\n", test_words[i]);
		} else {
			printf("Word %s isn't in trie\n", test_words[i]);
		}
	}
	Trie triePrefix = prefix((unsigned char *) words[0]);
	if (triePrefix == NULL) {
		return EXIT_FAILURE;
	}
	printTransition(triePrefix);
	for (size_t i = 0; i < strlen(words[0]); i++) {
		char tmp[i + 2];
		memcpy(tmp, words[0], i + 1);
		tmp[i + 1] = '\0';
		if (isInTrie(trie, (unsigned char *) tmp)) {
			printf("Prefix %s is in the word %s\n", tmp, words[0]);
		} else {
			printf("Prefix %s is in the word %s\n", tmp, words[0]);
		}
	}
	freeTrie(trie);
	return EXIT_SUCCESS;
}
*/
