#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <transition_matrix_trie.h>

void printTransition(Trie trie);
Trie prefix(unsigned char *w);
Trie suffix(unsigned char *w);
// Trie factor(unsigned char *w);

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
	size_t idxW = 0;
	printf("Insertion in trie : %s\n", w);
	for (size_t i = 0; i < (size_t) trie->maxNode && w[idxW] != '\0'; i = (size_t) trie->nextNode) {
		for (size_t j = 0; j < LENGTH_ASCII_CHARS; j++) {
			if (!trie->transition[i][j] && j == w[idxW]) {
				trie->transition[i][j] = trie->nextNode++;
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
	int num_node = 0;
	int idxW = 0;
	int lastIdxW = -1;
	for (size_t i = 0; i < (size_t) trie->maxNode && w[idxW] != '\0'; i++) {
		for (size_t j = 0; j < LENGTH_ASCII_CHARS; j++) {
			if (w[idxW] == j) {
				lastIdxW = idxW;
				printf("transition[%lu][%lu]=%d - %c : ", i, j, trie->transition[i][j], w[idxW]);
				if (trie->transition[i][j] != 0) {
					num_node = trie->transition[i][j];
					idxW++;
					printf("%d != %d\n", lastIdxW, idxW);
				}
				printf("\n");
				break;
			}
		}
		// Node not found
		if (lastIdxW == idxW) {
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

Trie prefix(unsigned char *w) {
	int maxNode = (int) (strlen((const char *) w) << 1);
	Trie t = createTrie(maxNode);
	size_t w_len = strlen((const char *) w); 
	for (size_t i = 0; i < w_len; i++) {
		char tmp[i + 2];
		memcpy(tmp, w, i + 1);
		tmp[i + 1] = '\0';
		insertInTrie(t, (unsigned char *) tmp);
	}
	return t;
}

Trie suffix(unsigned char *w) {
	int maxNode = (int) (strlen((const char *) w) << 1);
	Trie t = createTrie(maxNode);
	for (long int i = (long int) (strlen((const char *) w) - 1); i >= 0; i--) {
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
			/* DEBUG : remove transition != 0 to see all */
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
	int maxNode = 20;
	Trie trie = createTrie(maxNode);
	if (trie == NULL) {
		return EXIT_FAILURE;
	}
	const char *words[] = {"gtagct", "tag", "gagct", "ctagt", NULL};
	//const char *test_words[] = {"ag", "atcg", "gv", "atc", "av", "agv", NULL};
	for (size_t i = 0; words[i] != NULL; i++)
		insertInTrie(trie, (unsigned char *) words[i]);
	printTransition(trie);
	/*for (size_t i = 0; test_words[i] != NULL; i++) {
		if (isInTrie(trie, (unsigned char *) test_words[i])) {
			printf("Word %s is in trie\n", test_words[i]);
		} else {
			printf("Word %s isn't in trie\n", test_words[i]);
		}
	}*/
	freeTrie(trie);
	return EXIT_SUCCESS;
}
