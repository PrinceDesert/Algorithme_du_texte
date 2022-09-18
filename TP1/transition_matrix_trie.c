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
	size_t idx_w = 0;
	for (size_t i = 0; i < (size_t) trie->maxNode && w[idx_w] != '\0'; i++) {
		for (size_t j = 0; j < LENGTH_ASCII_CHARS; j++) {
			if (!trie->transition[i][j] && j == w[idx_w]) {
				trie->transition[i][j] = trie->nextNode++;
				printf("%c==%c : transition[%lu][%lu]=%d\n", (char) j, w[idx_w], i, j, trie->transition[i][j]);
				break;
			}
		}
		idx_w++;
	}
	trie->finite[trie->nextNode-1] = '1';
	printf("finite :\n");
	for (size_t i = 0; i < (size_t) trie->maxNode + 1; i++) {
		printf("%c|", trie->finite[i]);
	}
	printf("\n");
}
	
int isInTrie(Trie trie, unsigned char *w) {
	int num_node = 0;
	int idx_w = 0;
	int last_idx_w = -1;
	for (size_t i = 0; i < (size_t) trie->maxNode && w[idx_w] != '\0'; i++) {
		for (size_t j = 0; j < LENGTH_ASCII_CHARS; j++) {
			if (w[idx_w] == j) {
				last_idx_w = idx_w;
				printf("transition[%lu][%lu]=%d - %c : ", i, j, trie->transition[i][j], w[idx_w]);
				if (trie->transition[i][j] != 0) {
					num_node = trie->transition[i][j];
					idx_w++;
					printf("%d != %d", last_idx_w, idx_w);
					break;
				}
				printf("\n");
				// break ici au lieu de en haut ?
			}
		}
		// Node not found
		if (last_idx_w == idx_w) {
			printf("NOT : %d - %d\n", last_idx_w, idx_w);
			return 0;
		}
	}
	return trie->finite[num_node] == '1';
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
			/* DEBUG : remove transition != 0 when finish debug */
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

int main(void) {
	int maxNode = 6;
	Trie trie = createTrie(maxNode);
	if (trie == NULL) {
		return EXIT_FAILURE;
	}
	const char *words[] = {"atcg", "agv", NULL};
	const char *test_words[] = {"ag", "atcg", "gv", "atc", "av", "agv", NULL};
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
	freeTrie(trie);
	return EXIT_SUCCESS;
}
