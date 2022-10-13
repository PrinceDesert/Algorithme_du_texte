#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// avec sentinelle : concatene le mot à la fin

// trop à droite : si le mot a comparé dépasse la fin du texte
// test si trop à droite : que si occurence
// boucle rapide : décale la fenetre à la premier occurence de la lettre en gros c'est l'index qui se décale à une potentiel occurence

// algorithme naif, avec boucle interne, sans boucle rapide, sans sentinelle (word = mot à trouver) pour compter le nb d'occurence de word dans text
int algorithme_naif_avec_boucle_interne_sans_boucle_rapide_sans_sentinelle(char *text, int n, char *word, int m);
// algorithme naif, avec boucle interne, avec boucle rapide, sans sentinelle pour compter le nb d'occurence de word dans text
int algorithme_naif_avec_boucle_interne_avec_boucle_rapide_sans_sentinelle(char *text, int n, char *word, int m);
// algorithme naif, avec boucle interne, avec boucle rapide, avec sentinelle pour compter le nb d'occurence de word dans text
int algorithme_naif_avec_boucle_interne_avec_boucle_rapide_avec_sentinelle(char *text, int n, char *word, int m);
// algorithme naif, avec strncmp, sans boucle rapide, sans sentinelle pour compter le nb d'occurence de word dans text 
int algorithme_naif_avec_boucle_interne_avec_boucle_rapide_avec_sentinelle(char *text, int n, char *word, int m);
// algorithme naif, avec strncmp, sans boucle rapide, sans sentinelle pour compter le nb d'occurence de word dans text 
int algorithme_naif_avec_strncmp_sans_boucle_rapide_sans_sentinelle(char *text, int n, char *word, int m);
// algorithme naif, avec strncmp, avec boucle rapide, sans sentinelle pour compter le nb d'occurence de word dans text 
int algorithme_naif_avec_strncmp_avec_boucle_rapide_sans_sentinelle(char *text, int n, char *word, int m);
// algorithme naif, avec strncmp, avec boucle rapide, avec sentinelle pour compter le nb d'occurence de word dans text
int algorithme_naif_avec_strncmp_avec_boucle_rapide_avec_sentinelle(char *text, int n, char *word, int m);

int findNextIndex(char *word, size_t word_len, char c);

// algorithme de Morris-Pratt
// algorithme de Knuth-Morris-Pratt
// algorithme de Boyer-Moore
// algorithme de Horspool
// algorithme Quick Search

/** 
 * premier genérateur pseudo-aléatoire de texte permettant de stocker
dans des fichiers des textes d’une longueur donn ́ee sur un alphabet de taille
donnée
*/

// un generateur de texte, un generateur de mot en bash
// generer les courbes avec un autre outil

int findNextIndex(char *word, size_t word_len, char c) {
	if (word == NULL || word_len == 0) return -1;
	for (int i = 0; i < word_len; i++) {
		if (word[i] == c) {
			return i;
		}
	}
	return -1;
}

size_t algorithme_naif_avec_boucle_interne_sans_boucle_rapide_sans_sentinelle(char *text, size_t n, char *word, size_t m) {
	if (text == NULL || word == NULL || n == 0 || m == 0) return 0;
	int i, j;
	int nbOcc = 0;
	for (j = 0; j <= n - m; ++j) {
		for (i = 0; i < m && text[i] == word[i + j]; ++i);
		if (i >= m) {
			printf("shift : %d\n", j);
			printf("%s\n", word);
			printf("%*s%s\n", j, " ", text);
			nbOcc++;
		}
	}
	return nbOcc;
}

// utilise findNextInd pour passer à la prochaine occurence pour décaler la fenetre jusqu'a la prochaine occurence trouve ( = boucle rapide)
size_t algorithme_naif_avec_boucle_interne_avec_boucle_rapide_sans_sentinelle(char *text, size_t n, char *word, size_t m) {
	if (text == NULL || word == NULL || n == 0 || m == 0) return 0;
	int i, j;
	int nbOcc = 0;
	int nextOcc = -1;
	for (j = 0; j <= n - m; ++j) {
		for (i = 0; i < m && text[i] == word[i + j]; ++i);
		if (i >= m) {
			printf("shift : %d\n", j);
			printf("%s\n", word);
			printf("%*s%s\n", j, " ", text);
			nbOcc++;
		} else {
			if ((nextOcc = findNextIndex(text, word[i])) != -1) {
				j = nextOcc;
			}
		}
	}
	return nbOcc;
}

// la sentinelle sert à ne pas tester à chaque fois si on est en fin de mot
int algorithme_naif_avec_boucle_interne_avec_boucle_rapide_avec_sentinelle(char *text, size_t n, char *word, size_t m) {
	int i, j = 0;
	int nbOcc = 0;
	int nextOcc = -1;
	
	// on ajoute le mot à la fin pour être sur d'avoir une occurence = sentinelle
	size_t newTextLength = n + strlen(word);
	text = (char *) realloc(newTextLength * sizeof(char));
	if (text == NULL) {
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	if (snprintf(text, newTextLength, "%s%s", text, word) == 0) {
		perror("snprintf");
		exit(EXIT_FAILURE);
	}
	
	while (nbOcc != 1) {
		for (i = 0; i < m && text[i] == word[i + j]; ++i);
		if (i >= m) {
			printf("shift : %d\n", j);
			printf("%s\n", word);
			printf("%*s%s\n", j, " ", text);
			nbOcc++;
		} else {
			if ((nextOcc = findNextIndex(text, word[i])) != -1) {
				j = nextOcc;
			}
		}
	}
	return nbOcc;
}

// avec strncmp au lieu de comparer 1 par 1, on utilise strncmp mais on garde la boucle principale
int algorithme_naif_avec_strncmp_sans_boucle_rapide_sans_sentinelle(char *text, int n, char *word, int m) {
	if (text == NULL || word == NULL || n == 0 || m == 0) return 0;
	int i, j;
	int nbOcc = 0;
	for (j = 0; j <= n - m; ++j) {
		// Extraction de la fenêtre contenant le mot du texte
		const char *text_substr = substr(text, j, j+strlen(word));
		if (text_substr == NULL) {
			fprintf("Erreur substring(%s,%d,%d) = NULL", word, i, j);
			exit(EXIT_FAILURE);
		}
		
		if (strncmp(text_substr, word, strlen(word)) == 0) {
			nbOcc++;
		}
	}
	return nbOcc;
}

int algorithme_naif_avec_strncmp_avec_boucle_rapide_sans_sentinelle(char *text, int n, char *word, int m) {
	
}

/**
 * Substring with index
 * url : https://www.developpez.net/forums/d115796/c-cpp/c/equivalent-substring-c/
*/
char *substr(char *src, int pos, int len) {
	char *dest=NULL;
	if (len>0) {
		dest = calloc(len+1, 1);
		if (NULL != dest) {
			strncat(dest, src+pos,len);
		} else {
			perror("calloc");
			exit(EXIT_FAILURE);
		}
	}
	return dest;
}

int main()
{
	char *x = "ataatata";
	char *y = "ataataatataatataa";
	brute_force_search(x, strlen(x), y, strlen(y));
	return EXIT_SUCCESS;
}

void brute_force_search(char *x, int m, char *y, int n) {
	int i, j;
	for (j = 0; j <= n - m; ++j) {
		for (i = 0; i < m && x[i] == y[i + j]; ++i);
		if (i >= m) {
			printf("shift : %d\n", j);
			printf("%s\n", y);
			printf("%*s%s\n", j, " ", x);
		}
	}
}
