#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <assert.h>
#include <transition_list.h>
#include <hash_table_trie.h>
#include <queue.h>
	
char ** lire_mots(const char *fichier_mots, size_t *nbMots, size_t *maxNoeuds);
char* lire_texte(const char *fichier_texte);
	
int ac_hachage(const char **mots, size_t nbMots, size_t maxNoeuds, const char *texte, size_t n);
int pre_ac(Trie trie, const char **mots, size_t k, int *sup);
void complete(Trie trie, int e, int *sup);
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
	size_t maxNoeuds = 0;
	int alphabet[CHAR_LENGTH];
	memset(alphabet, 0, sizeof(alphabet));
	const char **mots = (const char **) lire_mots(fichier_mots, &nbMots, &maxNoeuds);
	const char *texte = (const char *) lire_texte(fichier_texte);
	ac_hachage(mots, nbMots, maxNoeuds, texte, strlen(texte));
	return EXIT_SUCCESS;
}

int ac_hachage(const char **mots, size_t nbMots, size_t maxNoeuds, const char *texte, size_t n) {
	assert(mots != NULL);
	assert(nbMots >= 1);
	assert(texte != NULL);
	assert(n == strlen(texte));
	// printf("Nombre de noeuds max : %lu\n", maxNode);
	Trie trie = createTrie((int) maxNoeuds);
	if (trie == NULL) {
		exit(EXIT_FAILURE);
	}
	int nbOcc = 0;
	int tailleSup = trie->maxNode + 1;
	int sup[tailleSup];
	for (int i = 0; i < tailleSup; i++) {
		sup[i] = SUPPLEANT_NON_DEFINIE;
	}
	int e = pre_ac(trie, mots, nbMots, sup);
	/*
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
	*/
	List noeud = NULL;
	int cleHash = -1;
	for (size_t j = 0; j <= n - 1; j++) {
		cleHash = hash(e, (unsigned char) texte[j], trie->maxNode);
		noeud = searchLink(trie->transition[cleHash], e, (unsigned char) texte[j]);
		while (noeud == NULL) {
			// printf("e = %d\n", e);
			e = sup[e];
			// printf("e = %d (sup[e])\n", e);
			cleHash = hash(e, (unsigned char) texte[j], trie->maxNode);
			noeud = searchLink(trie->transition[cleHash], e, (unsigned char) texte[j]);
		}
		e = noeud->targetNode;
		if (trie->finite[e] == '1') {
			nbOcc++;
			// printf("occurence %d\n", nbOcc);
		}
	}
	printf("%d\n", nbOcc);
	return nbOcc;
}
	
int pre_ac(Trie trie, const char **mots, size_t k, int *sup) {
	int q0 = 0;
	// La fonction entrer(entrer un état) est représenter par insertInTrie
	// Entrer(X[i], q0)
	for (size_t i = 0; i < k; i++) {
		insertInTrie(trie, (unsigned char *) mots[i]);
		// printf("insertion de %s, isInTrie(%s) = %d\n", mots[i], mots[i], isInTrie(trie, (unsigned char *) mots[i]));
	}
	List noeud = NULL;
	List nvNoeud = NULL;
	for (size_t i = 0; i < CHAR_LENGTH; i++) {
		int q0Hash = hash(q0, (unsigned char) i, trie->maxNode);
		noeud = trie->transition[q0Hash];
		nvNoeud = (List) malloc(sizeof(struct _list));
		if (nvNoeud == NULL) {perror("malloc"); free(trie->transition); exit(EXIT_FAILURE);}
		nvNoeud->startNode = q0;
		nvNoeud->letter = (unsigned char) i;
		nvNoeud->targetNode = q0;
		nvNoeud->next = NULL;
		if (noeud == NULL) {
			trie->transition[q0Hash] = nvNoeud;
		} else if (searchLink(noeud, 0, (unsigned char) i) == NULL) {
			appendLink(noeud, nvNoeud);
		} else {
			free(nvNoeud);
		}
	}
	complete(trie, q0, sup);
	return q0;
}
	
void complete(Trie trie, int e, int *sup) {
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
			int sHash = hash(s, (unsigned char) a, trie->maxNode);
			List noeud = searchLink(trie->transition[sHash], s, (unsigned char) a);
			while (noeud == NULL) {
				// printf("trie->transition[%d][%d] = %d\n", s, (int) a, trie->transition[s][(int) a]);
				// s = sup(s)
				s = sup[s] == SUPPLEANT_NON_DEFINIE ? 0 : sup[s];
				sHash = hash(s, (unsigned char) a, trie->maxNode);
				noeud = searchLink(trie->transition[sHash], s, (unsigned char) a);
			}
			// sup(p) = &(s,a)
			sup[p] = noeud->targetNode;
			free(first);
		}
	}
}

// l = liste des transitions (e, a, p) telles que p != e (e & p = numéro de noeud, a = lettre)
List liste_transitions(Trie trie, int e, int verification) {
	int p, test, cleHash;
	unsigned char a;
	List transition = NULL, first = NULL, precedent = NULL, noeud = NULL;
	for (int j = 0; j < CHAR_LENGTH; j++) {
		cleHash = hash(e, (unsigned char) j, trie->maxNode);
		// Recherche pour le noeud e, la transition du noeud de départ e avec la lettre j
		noeud = searchLink(trie->transition[cleHash], e, (unsigned char) j);
		if (noeud != NULL) {
			// printf("|%d| => [%d,%c,%d]\n", cleHash, node->startNode, node->letter, node->targetNode);
			p = noeud->targetNode;
			test = !verification ? 1 : e != p;
			if (test) {
				transition = (List) malloc(sizeof(struct _list));
				if (transition == NULL) { perror("malloc"); exit(EXIT_FAILURE); }
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
	}
	return first;
}
	
char ** lire_mots(const char *fichier_mots, size_t *nbMots, size_t *maxNoeuds) {
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
	size_t nbLettres = 0;
	while (!feof(fp)) {
		if (fgets(line, ARRAY_SIZE(line), fp) == NULL) {
			if (ferror(fp)) {
				fprintf(stderr, "fgets failed : %d\n", errno);
				exit(EXIT_FAILURE);
			}
		}
		line[strcspn(line, "\n")] = '\0';
		len_strbuf = (strlen(line) + 1) * sizeof(char);
		if (strlen(line) > 0) {
			buffer[i] = malloc(len_strbuf);
			if (buffer[i] == NULL) { perror("malloc"); exit(EXIT_FAILURE); }
			bytes = snprintf(buffer[i], len_strbuf, "%s", line);
			if (bytes < 0 ||  bytes >= (int) len_strbuf) { perror("snprintf"); exit(EXIT_FAILURE); }
			nbLettres += strlen(buffer[i]);
			memset(line, '\0', sizeof(line));
			i++;
			(*nbMots)++;
		}
	}
	*maxNoeuds = ((*nbMots) * nbLettres) + 1;
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
	return buffer;
}
