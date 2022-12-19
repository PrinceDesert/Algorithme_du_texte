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
int pre_ac(Trie trie, const char **mots, size_t k);
void complete(Trie trie, int e);

#define SUPPLEANT_NON_DEFINIE -1

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Usage : %s <fichier mot> <fichier texte>\n", argv[0]);
		return EXIT_FAILURE;
	}
	const char *fichier_mots = "./mots.txt"; // argv[1];
	const char *fichier_texte = "./texte.txt"; // argv[2];
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
	int e = pre_ac(trie, mots, nbMots);
	printf("ok\n");
	return -1;
	// for j= 0; < n - 1
	for (size_t j = 0; j < n - 1; j++) {
		while (trie->transition[e][j] == EMPTY_TRANSITION) {
			// e = sup[e];
		}
		e = trie->transition[e][(int) texte[j]];
		if (e != EMPTY_TRANSITION) {
			nbOcc++;
		}
	}
	return nbOcc;
}

int pre_ac(Trie trie, const char **mots, size_t k) {
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
	complete(trie, q0);
	return q0;
}

// cbbabc

void complete(Trie trie, int e) {
	Queue f;
	int p, r, s;
	unsigned char a;
	int tailleSup = trie->nextNode - 1;
	int sup[tailleSup];
	f = initQueue();
	for (int i = 0; i < tailleSup; i++) {
		sup[i] = SUPPLEANT_NON_DEFINIE;
	}
	// l = liste des transitions (e, a, p) telles que p != e (e & p = numéro de noeud, a = lettre)
	List precedent = NULL;
	List transition = NULL;
	List first = NULL;
	for (int j = 0; j < CHAR_LENGTH; j++) {
		p = trie->transition[e][j];
		if (trie->transition[e][j] != EMPTY_TRANSITION && e != p) {
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
	// l = first car first=1er élement de la liste : 1er->2eme->3eme->NULL
	List l = first;
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
		precedent = NULL;
		for (int j = 0; j < CHAR_LENGTH; j++) {
			if (trie->transition[r][j] != EMPTY_TRANSITION) {
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
		l = precedent;
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
				printf("s=%d ", s);
				printf("sup[s]=%d\n", sup[s]);
				// s = sup(s)
				s = sup[s];
			}
			// sup(p) = &(s,a)
			sup[p] = trie->transition[s][(int) a];
			free(first);
		}
	}
	printf("ok4\n");
	exit(EXIT_FAILURE);

	// Affecte les suppléants à la matrice de transitions
	for (int i = 0; i < tailleSup; i++) {
		// trie->transition
		if (sup[i] != SUPPLEANT_NON_DEFINIE) {
			// trie->transition[i][j] = sup[i];
		}
	}

}

/*
int sup(Trie t, int q) {
	int current = q;
	// Tant que pas revenu à la racine
	while (current != 0) {
		unsigned char parentLetter;
		int parentNode;
		// Récupère la lettre
		for (int i = 0; i < t->maxNode; i++) {	 
			for (int j = 0; j < CHAR_LENGTH; j++) {
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
*/

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
