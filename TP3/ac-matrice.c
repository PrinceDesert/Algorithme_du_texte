#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <assert.h>
#include <transition_list.h>
#include <transition_matrix_trie.h>
#include <queue.h>
	

// La liste des transitions
// struct transition {int startNode, int endNode, char letter}
// *transition = list des transitions
// premier 
// suivant

// file d'entier p est l'état suivant de e ou a est la lettre de transition
// enfiler, defiler

// la fonction sup regarde le plus long suffixe pour trouver l'état où atterir
	
char** lire_mots(const char *fichier_mots, size_t *nbMots);
char* lire_texte(const char *fichier_texte);

int ac_matrice(const char **mots, size_t nbMots, const char *texte, size_t n);
int pre_ac(Trie trie, const char **mots, size_t k, int *sup, int tailleSup);
void complete(Trie trie, int e, int *sup, int tailleSup);
List liste_transitions(Trie trie, int e, int verification);

#define SUPPLEANT_NON_DEFINIE 0

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Usage : %s <fichier mot> <fichier texte>\n", argv[0]);
		return EXIT_FAILURE;
	}
	const char *fichier_mots = argv[1]; // "./mots.txt"
	const char *fichier_texte = argv[2]; // "./texte.txt"
	size_t nbMots = 0;
	const char **mots = (const char **) lire_mots(fichier_mots, &nbMots);
	const char *texte = (const char *) lire_texte(fichier_texte);
	ac_matrice(mots, nbMots, texte, strlen(texte));
	return EXIT_SUCCESS;
}

int ac_matrice(const char **mots, size_t nbMots, const char *texte, size_t n) {
	assert(mots != NULL);
	assert(nbMots >= 1);
	assert(texte != NULL);
	assert(n == strlen(texte));
	Trie trie = createTrie(100);
	if (trie == NULL) {
		exit(EXIT_FAILURE);
	}
	int nbOcc = 0;
	int tailleSup = trie->maxNode + 1;
	int sup[tailleSup];
	for (int i = 0; i < tailleSup; i++) {
		sup[i] = SUPPLEANT_NON_DEFINIE;
	}
	int e = pre_ac(trie, mots, nbMots, sup, tailleSup);
	printf("pre ac - e = %d\n", e);
	for (int i = 0; i < tailleSup; i++) {
		printf("sup[%d] = %d\n", i, sup[i]);
	}
	printf("finite: ");
	for (int i = 0; i < CHAR_LENGTH; i++) {
		if (trie->finite[i] == '1') {
			printf("%d ", i);
		}
	}
	printf("\n");
	printf("taille du texte : %lu\n", n);
	// for j= 0; < n - 1
	for (size_t j = 0; j < n - 1; j++) {
		printf("trie->transition[%d][%d=%c] = %d\n", e, (int) texte[j], texte[j], trie->transition[e][(int) texte[j]]);
		while (trie->transition[e][(int) texte[j]] == EMPTY_TRANSITION) {
			printf("e = %d\n", e);
			e = sup[e];
			printf("e = %d (sup[e])\n", e);
		}
		e = trie->transition[e][(int) texte[j]];
		if (trie->finite[e] == '1') {
			printf("Une occurence pour le mot lu(regarder les dernières lettres)\n");
			nbOcc++;
		}
	}
	printf("nbOcc : %d\n", nbOcc);
	return nbOcc;
}

void find_substrings(int node, char *result, int result_len) {
  if (node != root) { // si le noeud courant n'est pas la racine, ajouter le caractère courant au résultat
    result[result_len] = child[node][c];
    result[result_len + 1] = '\0';
    printf("Found substring: %s\n", result);
	  if (isInTrie(trie, result) {
	    trie->finite[node] = '1';	  
	  }
  }
  // parcourir récursivement tous les fils du noeud courant
  for (int c = 0; c < MAX_CHARS; c++) {
    int child = child[node][c];
    if (child) {
      find_substrings(child, result, result_len + 1);
    }
  }
}

int pre_ac(Trie trie, const char **mots, size_t k, int *sup, int tailleSup) {
	int q0 = 0;
	// Initialise la matrice de transtion
	for (int j = 0; j < CHAR_LENGTH; j++) {
		if (trie->transition[q0][j] != EMPTY_TRANSITION) {
			trie->transition[q0][j] = EMPTY_TRANSITION;
		}
	}
	// La fonction entrer(entrer un état) est représenter par insertInTrie
	// Entrer(X[i], q0)
	for (size_t i = 0; i < k; i++) {
		insertInTrie(trie, (unsigned char *) mots[i]);
	}
	
	for (size_t i = 0; i < CHAR_LENGTH; i++) {
		if (trie->transition[0][i] == EMPTY_TRANSITION) {
			// &(s,a) = q0
			trie->transition[0][i] = 0;
		}
	}
	complete(trie, q0, sup, tailleSup);
	return q0;
}

// cbbabc

void complete(Trie trie, int e, int *sup, int tailleSup) {
	Queue f;
	int p, r, s;
	unsigned char a;
	List first;
	// l = first car first=1er élement de la liste : 1er->2eme->3eme->NULL
	List l = liste_transitions(trie, e, 1);
	f = initQueue();
	// tant que l est non vide faire
	while (l != NULL) {
		// printf("l : start:%d, letter:%c, end:%d, nextnull?:%d\n", l->startNode, l->letter, l->targetNode, l->next == NULL);
		// (r,a,p) = premier(l)
		first = l;
		r = first->startNode;
		a = first->letter;
		p = first->targetNode;
		// l = suivant(l)
		l = l->next;
		// enfile(f, p)
		queuePush(f, p);
		// sup(p) = e
		sup[p] = e;
		free(first);
	}
	// tant que f est non vide faire
	while (!queueIsEmpty(f)) {
		r = queueFirst(f);
		queuePop(f);
		// l = liste des transitions (r,a,p)
		// récupère les transitions ayant pour noeud de départ r
		l = liste_transitions(trie, r, 0);
		// tant que l est non vide faire
		while (l != NULL) {
			// (r,a,p) = premier(l)
			first = l;
			r = first->startNode;
			a = first->letter;
			p = first->targetNode;
			// l = suivant(l)
			l = l->next;
			// enfile(f, p)
			queuePush(f, p);
			// s = sup(r)
			s = sup[r];
			// tant que &(s,a) est non définie
			while (trie->transition[s][(int) a] == EMPTY_TRANSITION) {
				// printf("trie->transition[%d][%d] = %d\n", s, (int) a, trie->transition[s][(int) a]);
				// s = sup(s)
				s = sup[s] == SUPPLEANT_NON_DEFINIE ? 0 : sup[s];
			}
			// sup(p) = &(s,a)
			sup[p] = trie->transition[s][(int) a];
			free(first);
		}
	}
}

// l = liste des transitions (e, a, p) telles que p != e (e & p = numéro de noeud, a = lettre)
List liste_transitions(Trie trie, int e, int verification) {
	int p, test;
	unsigned char a;
	List transition = NULL, first = NULL, precedent = NULL;
	for (int j = 0; j < CHAR_LENGTH; j++) {
		p = trie->transition[e][j];
		test = !verification ? 1 : e != p;
		if (trie->transition[e][j] != EMPTY_TRANSITION && test) {
			transition = (List) malloc(sizeof(struct _list));
			if (transition == NULL) {
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			transition->startNode = e;
			transition->targetNode = p;
			a = (unsigned char) j;
			transition->letter = a;
			if (precedent == NULL) {
				first = transition;
				transition->next = NULL;
				precedent = transition;
			} else {
				precedent->next = transition;
				precedent = transition;
			}
		}
	}
	return first;
}

char ** lire_mots(const char *fichier_mots, size_t *nbMots) {
	FILE *fp;	
	fp = fopen(fichier_mots, "rb");
	if (!fp) {
		fprintf(stderr, "Impossible d'ouvrir %s pour lire\n", fichier_mots);
		exit(EXIT_FAILURE);
	}
	char **buffer;
	size_t len_buf;
	size_t len_strbuf;
	len_buf = 2048;
	int bytes;
	int i = 0;
	buffer = (char **) malloc(len_buf);
	if (buffer == NULL) { perror("malloc"); exit(EXIT_FAILURE); }

	int size_line = 256;
	char line[size_line];

	while (!feof(fp)) {
		if (fgets(line, ARRAY_SIZE(line), fp) == NULL) {
			if (ferror(fp)) {
				fprintf(stderr, "fgets failed : %d\n", errno);
				exit(EXIT_FAILURE);
			}
		}
		line[strcspn(line, "\n")] = '\0';
		len_strbuf = (strlen(line) + 1) * sizeof(char);
		buffer[i] = malloc(len_strbuf);
		if (buffer[i] == NULL) { perror("malloc"); exit(EXIT_FAILURE); }
		bytes = snprintf(buffer[i], len_strbuf, "%s", line);
		if (bytes < 0 ||  bytes >= (int) len_strbuf) { perror("snprintf"); exit(EXIT_FAILURE); }
		memset(line, '\0', sizeof(line));
		i++;
		(*nbMots)++;
	}

	if (fclose(fp) != 0) {
		fprintf(stderr, "Impossible de fermer %s\n", fichier_mots);
		exit(EXIT_FAILURE);
	}
	/*
	printf("Nombre de mot(s) : %d\n", *nbMots);
	for (int j = 0; j < i; j++) {
		printf("mot : %s\n", buffer[j]);
	}
	*/

	return buffer;
}

char * lire_texte(const char *fichier_texte) {
	FILE *fp;	
	fp = fopen(fichier_texte, "rb");
	if (!fp) {
		fprintf(stderr, "Impossible d'ouvrir %s pour lire\n", fichier_texte);
		exit(EXIT_FAILURE);
	}

	int size_line = 256;
	char line[size_line];
	if (fgets(line, ARRAY_SIZE(line), fp) == NULL) {
		if (ferror(fp)) {
			fprintf(stderr, "fgets failed : %d\n", errno);
			exit(EXIT_FAILURE);
		}
	}
	line[strcspn(line, "\n")] = '\0';

	char *buffer;
	size_t len_buf = 2048;
	int bytes;
	buffer = (char *) malloc(len_buf);
	if (buffer == NULL) { perror("malloc"); exit(EXIT_FAILURE); }
	bytes = snprintf(buffer, len_buf, "%s", line);
	if (bytes < 0 ||  bytes >= (int) len_buf) { perror("snprintf"); exit(EXIT_FAILURE); }

	if (fclose(fp) != 0) {
		fprintf(stderr, "Impossible de fermer %s\n", fichier_texte);
		exit(EXIT_FAILURE);
	}

	// printf("texte : %s\n", buffer);

	return buffer;
}
