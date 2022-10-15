#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Algorithmes de recherche exacte d’un mot dans un texte
*/

// avec sentinelle : concatene le mot à la fin

// trop à droite : si le mot a comparé dépasse la fin du texte
// test si trop à droite : que si occurence
// boucle rapide : décale la fenetre à la premier occurence de la lettre en gros c'est l'index qui se décale à une potentiel occurence

// algorithme naif, avec boucle interne, sans boucle rapide, sans sentinelle (word = mot à trouver) pour compter le nb d'occurence de word dans text
int algorithme_naif_avec_boucle_interne_sans_boucle_rapide_sans_sentinelle(const char *text, int m, const char *word, int n);
// algorithme naif, avec boucle interne, avec boucle rapide, sans sentinelle pour compter le nb d'occurence de word dans text
int algorithme_naif_avec_boucle_interne_avec_boucle_rapide_sans_sentinelle(const char *text, int m, const char *word, int n);
// algorithme naif, avec boucle interne, avec boucle rapide, avec sentinelle pour compter le nb d'occurence de word dans text
int algorithme_naif_avec_boucle_interne_avec_boucle_rapide_avec_sentinelle(const char *text, int m, const char *word, int n);

// algorithme naif, avec strncmp, sans boucle rapide, sans sentinelle pour compter le nb d'occurence de word dans text 
int algorithme_naif_avec_strncmp_sans_boucle_rapide_sans_sentinelle(const char *text, int m, const char *word, int n);
// algorithme naif, avec strncmp, avec boucle rapide, sans sentinelle pour compter le nb d'occurence de word dans text 
//int algorithme_naif_avec_strncmp_avec_boucle_rapide_sans_sentinelle(const char *text, int m, const char *word, int n);
// algorithme naif, avec strncmp, avec boucle rapide, avec sentinelle pour compter le nb d'occurence de word dans text
//int algorithme_naif_avec_strncmp_avec_boucle_rapide_avec_sentinelle(char *text, int m, const char *word, int n);

// algorithme de Morris-Pratt
int algorithme_Morris_Pratt();
// algorithme de Knuth-Morris-Pratt
int algorithme_Knuth_Morris_Pratt();
// algorithme de Boyer-Moore
int algorithme_Boyer_Moore();
// algorithme de Horspool
int algorithme_Horspool();
// algorithme Quick Search
int algorithme_Quick_Search();

// utils
int findNextIndex(const char *word, size_t word_len, char c);
char *substr(const char *src, size_t pos, size_t len);

// un generateur de texte, un generateur de mot en bash
// generer les courbes avec un autre outil

int main(void) {
	const char *word = "ataataatataatataa";
	const char *text = "ataataatataatataa";
	
	printf("== algorithme_naif_avec_boucle_interne_sans_boucle_rapide_sans_sentinelle : %d ==\n",
		algorithme_naif_avec_boucle_interne_sans_boucle_rapide_sans_sentinelle(text, (int) strlen(text), word, (int) strlen(word)));
	
	printf("== algorithme_naif_avec_boucle_interne_avec_boucle_rapide_sans_sentinelle : %d ==\n",
		algorithme_naif_avec_boucle_interne_avec_boucle_rapide_sans_sentinelle(text, (int) strlen(text), word, (int) strlen(word)));
	
	printf("== algorithme_naif_avec_boucle_interne_avec_boucle_rapide_avec_sentinelle : %d ==\n",
		algorithme_naif_avec_boucle_interne_avec_boucle_rapide_avec_sentinelle(text, (int) strlen(text), word, (int) strlen(word)));
	
	
	return EXIT_SUCCESS;
}

int algorithme_naif_avec_boucle_interne_sans_boucle_rapide_sans_sentinelle(const char *text, int m, const char *word, int n) {
	if (text == NULL || word == NULL || n == 0 || m == 0) return 0;
	int i, j;
	int nbOcc = 0;
	for (j = 0; j <= n - m; j++) {
		for (i = 0; i < m && text[i] == word[i + j]; i++);
		if (i >= m) {
			/*
			printf("shift : %d\n", j);
			printf("%s\n", word);
			printf("%*s%s\n", j, " ", text);
			*/
			nbOcc++;
		}
	}
	return nbOcc;
}

// utilise findNextInd pour passer à la prochaine occurence pour décaler la fenetre jusqu'a la prochaine occurence trouve ( = boucle rapide)
int algorithme_naif_avec_boucle_interne_avec_boucle_rapide_sans_sentinelle(const char *text, int m, const char *word, int n) {
	if (text == NULL || word == NULL || n == 0 || m == 0) return 0;
	int i, j;
	int nbOcc = 0;
	int nextOcc = -1;
	for (j = 0; j <= n - m; j++) {
		for (i = 0; i < m && text[i] == word[i + j]; i++);
		if (i >= m) {
			/*
			printf("shift : %d\n", j);
			printf("%s\n", word);
			printf("%*s%s\n", j, " ", text);
			*/
			nbOcc++;
		} else {
			if ((nextOcc = findNextIndex(text, strlen(text), word[i])) != -1) {
				j = (size_t) nextOcc;
			}
		}
	}
	return nbOcc;
}

// la sentinelle sert à ne pas tester à chaque fois si on est en fin de mot
int algorithme_naif_avec_boucle_interne_avec_boucle_rapide_avec_sentinelle(const char *text, int m, const char *word, int n) {
	int i, j = 0;
	int nbOcc = 0;
	int nextOcc = -1;
	
	// création d'un copie du texte et ajout du mot à la fin du texte pour être sur d'avoir une occurence = sentinelle
	size_t newTextLength = (size_t) n + strlen(word);
	char *newText = (char *) malloc(newTextLength * sizeof(char));
	if (newText == NULL) {
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	if (snprintf(newText, newTextLength, "%s%s", text, word) == 0) {
		perror("snprintf");
		exit(EXIT_FAILURE);
	}
	
	while (nbOcc != 1) {
		for (i = 0; i < m && newText[i] == word[i + j]; i++);
		if (i >= m) {
			/*
			printf("shift : %d\n", j);
			printf("%s\n", word);
			printf("%*s%s\n", j, " ", newText);
			*/
			nbOcc++;
		} else {
			if ((nextOcc = findNextIndex((const char *) newText, strlen(newText), word[i])) != -1) {
				j = nextOcc;
			}
		}
	}
	return nbOcc;
}

// avec strncmp au lieu de comparer 1 par 1, on utilise strncmp mais on garde la boucle principale
int algorithme_naif_avec_strncmp_sans_boucle_rapide_sans_sentinelle(const char *text, int m, const char *word, int n) {
	if (text == NULL || word == NULL || n == 0 || m == 0) return 0;
	int i, j;
	int nbOcc = 0;
	for (j = 0; j <= n - m; ++j) {
		// Extraction de la fenêtre contenant le mot du texte
		const char *text_substr = substr(text, (size_t) j, strlen(word) + (size_t) j);
		if (text_substr == NULL) {
			fprintf(stderr, "Error substr(%s,%d,%d) = NULL", word, i, j);
			exit(EXIT_FAILURE);
		}
		if (strncmp(text_substr, word, strlen(word)) == 0) {
			nbOcc++;
		}
	}
	return nbOcc;
}
/*
int algorithme_naif_avec_strncmp_avec_boucle_rapide_sans_sentinelle(const char *text, size_t m, const char *word, size_t n) {
	return 0;
}

int algorithme_naif_avec_strncmp_avec_boucle_rapide_avec_sentinelle(char *text, size_t m, const char *word, size_t n) {
	return 0;
}*/

int findNextIndex(const char *word, size_t word_len, char c) {
	if (word == NULL || word_len == 0) return -1;
	for (size_t i = 0; i < word_len; i++) {
		if (word[i] == c) {
			return (int) i;
		}
	}
	return -1;
}

/**
 * Substring with index
 * url : https://www.developpez.net/forums/d115796/c-cpp/c/equivalent-substring-c/
*/
char *substr(const char *src, size_t pos, size_t len) {
	char *dest=NULL;
	if (len>0) {
		dest = (char *) calloc(len+1, 1);
		if (NULL != dest) {
			strncat(dest, src+pos,len);
		} else {
			perror("calloc");
			exit(EXIT_FAILURE);
		}
	}
	return dest;
}
