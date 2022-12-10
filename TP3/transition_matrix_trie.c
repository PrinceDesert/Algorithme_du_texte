#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <transition_matrix_trie.h>
	
Trie createTrie(int maxNode) {
	Trie t = (Trie) malloc(sizeof(struct _trie));
	if (t == NULL) {
		perror("malloc");
		return NULL;
	}
	t->maxNode = maxNode + 1; // somme des longeurs des noeuds + 1 pour la racine
	t->nextNode = 1;
	t->transition = (int **) calloc((size_t) (t->maxNode), sizeof(int *));
	if (t->transition == NULL) {
		perror("calloc");
		free(t->transition);
		return NULL;
	}
	for (size_t i = 0; i < (size_t) t->maxNode; i++) {
		t->transition[i] = (int *) calloc(LENGTH_ASCII_CHARS, sizeof(int));
		if (t->transition[i] == NULL) {
			perror("calloc");
			free(t->transition);
			return NULL;
		}
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
	if (isInTrie(trie, w)) {
		printf("Insertion : le mot %s est déja dans le trie\n", w);
		return;
	}
	size_t idxW = 0;
	printf("Insertion in trie : %s\n", w);
	size_t i = 0;
	while (i < (size_t) trie->maxNode && w[idxW] != '\0') {
		for (size_t j = 0; j < LENGTH_ASCII_CHARS; j++) {
			if (j == w[idxW]) {
				if (!trie->transition[i][j]) {
					trie->transition[i][j] = trie->nextNode++;
				}
				i = (size_t) trie->transition[i][j]; 
				printf("%c==%c : transition[%lu][%lu]=%d\n", (char) j, w[idxW], i, j, trie->transition[i][j]);
				break;
			}
		}
		idxW++;
	}
	trie->finite[trie->nextNode-1] = '1';
	printf("finite :\n");
	for (size_t i = 0; i < (size_t) trie->maxNode + 1; i++) {
		printf("%c|", trie->finite[i]);
	}
	printf("\n");
}
	
	
int isInTrie(Trie trie, unsigned char *w) {
	size_t i = 0;
	size_t idxW = 0;
	long int lastIdxW = -1;
	while (i < (size_t) trie->maxNode && w[idxW] != '\0') {
		for (size_t j = 0; j < LENGTH_ASCII_CHARS; j++) {
			if (w[idxW] == j) {
				lastIdxW = (long int) idxW;
				i = (size_t) trie->transition[i][j];
				idxW++;
			}
		}
		// Node not found
		if ((size_t) lastIdxW == idxW) {
			return 0;
		}
	}
	printf("%s i=%lu\n", w, i);
	return trie->finite[i] == '1';
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
 * factor
Trie factor(unsigned char *w) {
	return NULL;
}*/
	
void printTransition(Trie trie) {
	printf("=======================\n");
	printf("== TRANSITION MATRIX ==\n");
	printf("=======================\n");
	for (size_t i = 0; i < (size_t) trie->maxNode; i++) {
		printf("%u:\n", (int) i);
		for (size_t j = 0; j < LENGTH_ASCII_CHARS; j++) {
			/* DEBUG : remove this condition statement to see all */
			if (trie->transition[i][j] != 0) {
				if (isprint(j)) {
					printf("printable char(ascii:%lu) %c : %d\n", j, (char) j, trie->transition[i][j]);
				} else {
					printf("non printable char(ascii:%lu) : %d\n", j, trie->transition[i][j]);
				}
			}
		}
		printf("\n");
	}
	printf("finite :\n");
	for (size_t i = 0; i < (size_t) trie->maxNode + 1; i++) {
		printf("%c|", trie->finite[i]);
	}
	printf("\n");
}
	
