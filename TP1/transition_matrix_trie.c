#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <transition_matrix_trie.h>

void printTransition(Trie trie);

#define LENGTH_ASCII_CHARS UCHAR_MAX + 1

// demander comment construit matrice transition
	
Trie createTrie(int maxNode) {
	Trie t = (Trie) malloc(sizeof(struct _trie));
	if (t == NULL) {
		perror("malloc");
		return NULL;
	}
	t->maxNode = maxNode + 1; // somme des longeurs des noeuds + 1 pour la racine
	t->nextNode = 1;
	t->transition = (int **) calloc((size_t) (maxNode) + 1, sizeof(int *));
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
	size_t len_finite = (size_t) t->maxNode + 1;
	t->finite = (char *) calloc(len_finite, sizeof(char));
	if (t->finite == NULL) {
		perror("calloc");
		free(t->finite);
		return NULL;
	}
	memset(t->finite, '0', len_finite);
	return t;
}
	
void insertInTrie(Trie trie, unsigned char *w) {
	size_t n = 0;
	for (size_t i = 0; i < (size_t) trie->maxNode; i++) {
		for (size_t j = 0; j < LENGTH_ASCII_CHARS; j++) {
			if (j == w[n]) {
				trie->transition[i][j] = trie->nextNode++;
				printf("%c==%c : %d\n", (char) j, w[n], trie->transition[i][j]);
				break;
			}
		}
		if (w[n+1] == '\0') {
			break;
		}
		n++;
	}
	printf("n : %lu\n", n);
	trie->finite[n] = '1';
}
	
int isInTrie(Trie trie, unsigned char *w) {
	int n = 1; // 0 : root
	int idx_w = 0;
	for (int i = 0; i < trie->maxNode; i++) {
		for (size_t j = 0; j < LENGTH_ASCII_CHARS; j++) {
			if (trie->transition[i][j] != 0 && w[idx_w] == j) {
				n++;
				idx_w++;
			}
		}
	}
	printf("n : %d\n", n);
	return n != 1 && trie->finite[n] == '1';
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

void printTransition(Trie trie) {
	for (size_t i = 0; i < (size_t) trie->maxNode; i++) {
		printf("%u:\n", (int) i);
		for (size_t j = 0; j < LENGTH_ASCII_CHARS; j++) {
			if (isprint(j)) {
				printf("printable char(ascii:%lu) %c : %d\n", j, (char) j, trie->transition[i][j]);
			} else {
				printf("non printable char(ascii:%lu) : %d\n", j, trie->transition[i][j]);
			}
		}
		printf("\n");
	}
	printf("finite :\n");
	for (size_t i = 0; i < (size_t) trie->maxNode; i++) {
		printf("%c|", trie->finite[i]);
	}
	printf("\n");
}

int main(void) {
	int maxNode = 11;
	Trie trie = createTrie(maxNode);
	if (trie == NULL) {
		return EXIT_FAILURE;
	}
	const char *str = "atcgjilh";
	const char *substr = "atcgjilh";
	insertInTrie(trie, (unsigned char *) str);
	//printTransition(trie); 
	if (isInTrie(trie, (unsigned char *) substr)) {
		printf("Word %s is in %s trie\n", substr, str);
	} else {
		printf("Word %s isn't in %s trie\n", substr, str);
	}
	freeTrie(trie);
	return EXIT_SUCCESS;
}
