#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <transition_list.h>
#include <transition_matrix_trie.h>
	
	
// La liste des transitions
// struct transition {int startNode, int endNode, char letter}
// *transition = list des transitions
// premier 
// suivant

// file d'entier p est l'état suivant de e ou a est la lettre de transition
// enfiler, defiler

// la fonction sup regarde le plus long suffixe pour trouver l'état où atterir
	
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
	
	int maxNode = nombreLetters + 1; 
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
	complete(0);
}
	
// e = num état
int complete(int e) {
	//aho_queue q = new_aho_queue();
	// crée une liste des transitions de e
	
	// f = file vide
	Queue f;
	f = initQueue();
	// l = liste des transitions (e, a, p) telles que p != e (e & p = numéro de noeud, a = lettre)
	int p, r;
	unsigned char a;
	List precedent = NULL;
	List transition = NULL;
	for (int j = 0; j < LENGTH_ASCII_CHARS; j++) {
		if (trie->transition[0][j] != 0) {
			p = trie->transition[0][j];
			transition = (List) malloc(sizeof(struct _list));
			if (transition == NULL) {
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			transition->startNode = e;
			transition->targetNode = p;
			a = (unsigned char) j;
			transition->letter = a;
			transition->next = precedent != NULL ? transition : NULL;
			precedent = transition;
		}
	}
	List l = precedent;
	List first = NULL;
	// tant que l est non vide faire
	while (l != NULL) {
		// (r,a,p) = premier(l)
		first = l;
		r = first->startNode;
		a = first->letter;
		p = first->endNode;
		// l = suivant(l)
		l = l->next;
		// enfile(f, p)
		queuePush(queue, p);
		// sup(p) = e
	}
	// tant que f est non vide faire
	while (!queueIsEmpty(f)) {
		r = queuePop(f);
		// l = liste des transitions (r,a,p)
		// récupère les transitions ayant pour noeud de départ r
		precedent = NULL;
		for (int j = 0; j < LENGTH_ASCII_CHARS; j++) {
			if (trie->transition[r][j] != 0) {
				p = trie->transition[r][j];
				a = (unsigned char) j;
				transition = (List) malloc(sizeof(struct _list));
				if (transition == NULL) {
					perror("malloc");
					exit(EXIT_FAILURE);
				}
				transition->startNode = r;
				transition->letter = a;
				transition->targetNode = p;
				transition->next = precedent != NULL ? transition : NULL;
				precedent = transition;
			}
		}
		l = precendent;
		// tant que l est non vide faire
		while (l != NULL) {
			// (r,a,p) = premier(l)
			first = l;
			r = first->startNode;
			a = first->letter;
			p = first->endNode;
			// l = suivant(l)
			l = l->next;
			// enfile(f, p)
			queuePush(queue, p);
			// s = sup(r)
			// int s = 
			// faire la fonction de sup
		}
	}
	return 0;
}

int sup(Trie t, int q) {
	int current = q;
	// Tant que pas revenu à la racine
	while (current != 0) {
		unsigned char parentLetter;
		int parentNode;
		// Récupère la lettre
		for (int i = 0; i < t->maxNode; i++) {	 
			for (int j = 0; j < LENGTH_ASCII_CHARS; j++) {
				if (t->transition[i][j] == current) {
					parentLetter = (unsigned char) j;
					parentNode = i;
					break;
				}
			}
		}
		// Cherche le plus long suffixe 
	} 
	return 0;
}

