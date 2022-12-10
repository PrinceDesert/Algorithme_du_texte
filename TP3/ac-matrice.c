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
	
char** lire_mots(const char *fichier_mots, int *nbMots);
char* lire_texte(const char *fichier_texte);

int ac_matrice(const char **mots, int *nbMots, const char *texte);
void pre_ac(Trie trie, const char **mots, int k);

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Usage : %s <fichier mot> <fichier texte>\n", argv[0]);
		return EXIT_FAILURE;
	}
	const char *fichier_mots = "./mots.txt"; // argv[1];
	const char *fichier_texte = "./texte.txt"; // argv[2];
	int nbMots = 0;
	__attribute_maybe_unused__ const char **mots = (const char **) lire_mots(fichier_mots, &nbMots);
	__attribute_maybe_unused__ const char *texte = (const char *) lire_texte(fichier_texte);
	ac_matrice(mots, &nbMots, texte);
	return EXIT_SUCCESS;
}

int ac_matrice(const char **mots, int *nbMots, __attribute_maybe_unused__ const char *texte) {
	
	int nbOcc = 0;
	Trie trie = createTrie(100);
	if (trie == NULL) {
		exit(EXIT_FAILURE);
	}

	pre_ac(trie, mots, *nbMots);

	return nbOcc;
}

void pre_ac(Trie trie, const char **mots, int k) {
	// La fonction entrer(entrer un état) est représenter par insertInTrie
	for (int i = 0; i < k; i++) {
		insertInTrie(trie, (unsigned char *) mots[i]);
	}
	// printTransition(trie);
	complete(trie);
}

// cbbabc


/*
// e = num état
int complete(Trie trie) {
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
*/

char ** lire_mots(const char *fichier_mots, int *nbMots) {
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
