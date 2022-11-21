#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include "./inc/transition_matrix_trie.h"

/*	
struct _transition {
	int startNode,
	char letter,
	int endNode
};
// Liste des transitions utilisés par la fonction compéter de aho-corasick
typedef struct _transition *Transitions;
*/

int ac_matrice(const char *filename_words, const char *filename_text);

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int main(void) {
	
	ac_matrice("./mots.txt", "./texte.txt");
	
	return EXIT_SUCCESS;
}

int ac_matrice(const char *filename_words, __attribute__((unused)) const char *filename_text) {
	
	
	// pour chaque mot
	FILE *fp;
	int size = 256;
	char line[size];
	
	fp = fopen(filename_words, "rb");
	if (!fp) {
		fprintf(stderr, "Cannot open %s to read\n", filename_words);
		exit(EXIT_FAILURE);
	}
	
	/*Trie trie = createTrie(25); 
	if (trie == NULL) {
		exit(EXIT_FAILURE);
	}*/
	
	while (!feof(fp)) {
		if (fgets(line, ARRAY_SIZE(line), fp) == NULL) {
			if (ferror(fp)) {
				fprintf(stderr, "fgets failed : %d\n", errno);
				exit(EXIT_FAILURE);
			}
		}
		line[strcspn(line, "\n")] = '\0';
		// insertInTrie(trie, (unsigned char *)  line);
		printf("line : %s\n", line);
		memset(line, '\0', sizeof(line));
	}
	// Algo AC
	/*
		printf("=======================\n");
		printf("== TRANSITION MATRIX ==\n");
		printf("=======================\n");
		for (size_t i = 0; i < (size_t) trie->maxNode; i++) {
			printf("%u:\n", (int) i);
			for (size_t j = 0; j < UCHAR_MAX + 1; j++) {
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
	*/
	if (fclose(fp) != 0) {
		fprintf(stderr, "Cannot close %s\n", filename_words);
		exit(EXIT_FAILURE);
	}
	
	return 0;
}

void pre_ac(const char *x, int k) {
	int maxNode = k + 1;
	Trie trie = createTrie(maxNode);
	if (trie == NULL) {
		exit(EXIT_FAILURE);
	}
	// La fonction entrer(entrer un état) est représenter par insertInTrie
	insertInTrie(trie, (unsigned char *) x);
}
	
// e = num état
int completer(int e) {
	//aho_queue q = new_aho_queue();
	// crée une liste des transitions de e
	Transitions transitions;
	transitions = (Transitions) malloc(sizeof(struct _transition));
	if (t == NULL) {
		perror("malloc");
		return;
	}
	return 0;
}

// La liste des transitions
// struct transition {int startNode, int endNode, char letter}
// *transition = list des transitions
// premier 
// suivant

// file d'entier p est l'état suivant de e ou a est la lettre de transition
// enfiler, defiler

// la fonction sup regarde le plus long suffixe pour trouver l'état où atterir

