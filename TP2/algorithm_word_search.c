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
size_t algorithme_naif_avec_boucle_interne_sans_boucle_rapide_sans_sentinelle(const char *text, size_t n, const char *word, size_t m);
// algorithme naif, avec boucle interne, avec boucle rapide, sans sentinelle pour compter le nb d'occurence de word dans text
size_t algorithme_naif_avec_boucle_interne_avec_boucle_rapide_sans_sentinelle(const char *text, size_t n, const char *word, size_t m);
// algorithme naif, avec boucle interne, avec boucle rapide, avec sentinelle pour compter le nb d'occurence de word dans text
size_t algorithme_naif_avec_boucle_interne_avec_boucle_rapide_avec_sentinelle(char *text, size_t n, const char *word, size_t m);

// algorithme naif, avec strncmp, sans boucle rapide, sans sentinelle pour compter le nb d'occurence de word dans text 
size_t algorithme_naif_avec_strncmp_sans_boucle_rapide_sans_sentinelle(const char *text, size_t n, const char *word, size_t m);
// algorithme naif, avec strncmp, avec boucle rapide, sans sentinelle pour compter le nb d'occurence de word dans text 
//size_t algorithme_naif_avec_strncmp_avec_boucle_rapide_sans_sentinelle(const char *text, size_t n, const char *word, size_t m);
// algorithme naif, avec strncmp, avec boucle rapide, avec sentinelle pour compter le nb d'occurence de word dans text
//size_t algorithme_naif_avec_strncmp_avec_boucle_rapide_avec_sentinelle(char *text, size_t n, const char *word, size_t m);

// algorithme de Morris-Pratt
size_t algorithme_Morris_Pratt();
// algorithme de Knuth-Morris-Pratt
size_t algorithme_Knuth_Morris_Pratt();
// algorithme de Boyer-Moore
size_t algorithme_Boyer_Moore();
// algorithme de Horspool
size_t algorithme_Horspool();
// algorithme Quick Search
size_t algorithme_Quick_Search();

// utils
int findNextIndex(const char *word, size_t word_len, char c);
char *substr(const char *src, size_t pos, size_t len);
size_t brute_force_search(const char *x, size_t m, const char *y, size_t n);

// un generateur de texte, un generateur de mot en bash
// generer les courbes avec un autre outil

int main(void) {
	const char *x = "ataatata";
	const char *y = "ataataatataatataa";
	
	printf("== brute_force_search : %lu ==\n",
		brute_force_search(x, strlen(x), y, strlen(y)));
	
	printf("== algorithme_naif_avec_boucle_interne_sans_boucle_rapide_sans_sentinelle : %lu ==\n",
		algorithme_naif_avec_boucle_interne_sans_boucle_rapide_sans_sentinelle(x, strlen(x), y, strlen(y)));
	
	
	return EXIT_SUCCESS;
}

size_t algorithme_naif_avec_boucle_interne_sans_boucle_rapide_sans_sentinelle(const char *text, size_t n, const char *word, size_t m) {
	if (text == NULL || word == NULL || n == 0 || m == 0) return 0;
	size_t i, j;
	size_t nbOcc = 0;
	for (j = 0; j <= n - m; ++j) {
		for (i = 0; i < m && text[i] == word[i + j]; ++i);
		if (i >= m) {
			printf("shift : %lu\n", j);
			printf("%s\n", word);
			printf("%*s%s\n", (int) j, " ", text);
			nbOcc++;
		}
	}
	return nbOcc;
}

// utilise findNextInd pour passer à la prochaine occurence pour décaler la fenetre jusqu'a la prochaine occurence trouve ( = boucle rapide)
size_t algorithme_naif_avec_boucle_interne_avec_boucle_rapide_sans_sentinelle(const char *text, size_t n, const char *word, size_t m) {
	if (text == NULL || word == NULL || n == 0 || m == 0) return 0;
	size_t i, j;
	size_t nbOcc = 0;
	int nextOcc = -1;
	for (j = 0; j <= n - m; ++j) {
		for (i = 0; i < m && text[i] == word[i + j]; ++i);
		if (i >= m) {
			printf("shift : %lu\n", j);
			printf("%s\n", word);
			printf("%*s%s\n", (int) j, " ", text);
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
size_t algorithme_naif_avec_boucle_interne_avec_boucle_rapide_avec_sentinelle(char *text, size_t n, const char *word, size_t m) {
	size_t i, j = 0;
	size_t nbOcc = 0;
	int nextOcc = -1;
	
	// on ajoute le mot à la fin pour être sur d'avoir une occurence = sentinelle
	size_t newTextLength = n + strlen(word);
	text = (char *) realloc(text, newTextLength * sizeof(char));
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
			printf("shift : %lu\n", j);
			printf("%s\n", word);
			printf("%*s%s\n", (int) j, " ", text);
			nbOcc++;
		} else {
			if ((nextOcc = findNextIndex(text, strlen(text), word[i])) != -1) {
				j = (size_t) nextOcc;
			}
		}
	}
	return nbOcc;
}

// avec strncmp au lieu de comparer 1 par 1, on utilise strncmp mais on garde la boucle principale
size_t algorithme_naif_avec_strncmp_sans_boucle_rapide_sans_sentinelle(const char *text, size_t n, const char *word, size_t m) {
	if (text == NULL || word == NULL || n == 0 || m == 0) return 0;
	size_t i, j;
	size_t nbOcc = 0;
	for (j = 0; j <= n - m; ++j) {
		// Extraction de la fenêtre contenant le mot du texte
		const char *text_substr = substr(text, j, strlen(word)+j);
		if (text_substr == NULL) {
			fprintf(stderr, "Error substr(%s,%lu,%lu) = NULL", word, i, j);
			exit(EXIT_FAILURE);
		}
		if (strncmp(text_substr, word, strlen(word)) == 0) {
			nbOcc++;
		}
	}
	return nbOcc;
}
/*
size_t algorithme_naif_avec_strncmp_avec_boucle_rapide_sans_sentinelle(const char *text, size_t n, const char *word, size_t m) {
	return 0;
}

size_t algorithme_naif_avec_strncmp_avec_boucle_rapide_avec_sentinelle(char *text, size_t n, const char *word, size_t m) {
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

size_t brute_force_search(const char *x, size_t m, const char *y, size_t n) {
	size_t i, j;
	size_t nbOcc = 0;
	for (j = 0; j <= n - m; ++j) {
		for (i = 0; i < m && x[i] == y[i + j]; ++i);
		if (i >= m) {
			nbOcc++;
			printf("shift : %lu\n", j);
			printf("%s\n", y);
			printf("%*s%s\n", (int) j, " ", x);
		}
	}
	return nbOcc;
}
