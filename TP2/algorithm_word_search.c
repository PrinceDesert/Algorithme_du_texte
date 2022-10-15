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
int algorithme_naif_avec_boucle_interne_sans_boucle_rapide_sans_sentinelle(const char *word, int m, const char *text, int n);
// algorithme naif, avec boucle interne, avec boucle rapide, sans sentinelle pour compter le nb d'occurence de word dans text
int algorithme_naif_avec_boucle_interne_avec_boucle_rapide_sans_sentinelle(const char *word, int m, const char *text, int n);
// algorithme naif, avec boucle interne, avec boucle rapide, avec sentinelle pour compter le nb d'occurence de word dans text
int algorithme_naif_avec_boucle_interne_avec_boucle_rapide_avec_sentinelle(const char *word, int m, const char *text, int n);

// algorithme naif, avec strncmp, sans boucle rapide, sans sentinelle pour compter le nb d'occurence de word dans text 
int algorithme_naif_avec_strncmp_sans_boucle_rapide_sans_sentinelle(const char *word, int m, const char *text, int n);
// algorithme naif, avec strncmp, avec boucle rapide, sans sentinelle pour compter le nb d'occurence de word dans text 
//int algorithme_naif_avec_strncmp_avec_boucle_rapide_sans_sentinelle(const char *word, int m, const char *text, int n);
// algorithme naif, avec strncmp, avec boucle rapide, avec sentinelle pour compter le nb d'occurence de word dans text
//int algorithme_naif_avec_strncmp_avec_boucle_rapide_avec_sentinelle(char *word, int m, const char *text, int n);

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
int findNextIndex(const char *word, size_t word_len, size_t start, char c);
char *substr(const char *src, size_t pos, size_t len);

// un generateur de texte, un generateur de mot en bash
// generer les courbes avec un autre outil

int main(void) {
	const char *text = "abbaaaaab";
	const char *word = "a";
	
	printf("== %s : %s ==\n", text, word);
	
	printf("== algorithme_naif_avec_boucle_interne_sans_boucle_rapide_sans_sentinelle : %d ==\n",
		algorithme_naif_avec_boucle_interne_sans_boucle_rapide_sans_sentinelle(word, (int) strlen(word), text, (int) strlen(text)));
	
	// BUG
	printf("== algorithme_naif_avec_boucle_interne_avec_boucle_rapide_sans_sentinelle : %d ==\n",
		algorithme_naif_avec_boucle_interne_avec_boucle_rapide_sans_sentinelle(word, (int) strlen(word), text, (int) strlen(text)));
	
	// BUG
	printf("== algorithme_naif_avec_boucle_interne_avec_boucle_rapide_avec_sentinelle : %d ==\n",
		algorithme_naif_avec_boucle_interne_avec_boucle_rapide_avec_sentinelle(word, (int) strlen(word), text, (int) strlen(text)));
	
	printf("== algorithme_naif_avec_strncmp_sans_boucle_rapide_sans_sentinelle : %d ==\n", 
		algorithme_naif_avec_strncmp_sans_boucle_rapide_sans_sentinelle(word, (int) strlen(word), text, (int) strlen(text)));
	
	
	return EXIT_SUCCESS;
}

int algorithme_naif_avec_boucle_interne_sans_boucle_rapide_sans_sentinelle(const char *word, int m, const char *text, int n) {
	if (word == NULL || text == NULL || m == 0 || n == 0) return 0;
	int i, j;
	int nbOcc = 0;
	for (j = 0; j <= n - m; j++) {
		for (i = 0; i < m && word[i] == text[i + j]; i++);
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
int algorithme_naif_avec_boucle_interne_avec_boucle_rapide_sans_sentinelle(const char *word, int m, const char *text, int n) {
	if (word == NULL || text == NULL || m == 0 || n == 0) return 0;
	int i, j = 0;
	int nbOcc = 0;
	int nextOcc = -1;
	
	while (j <= n - m) {
		for (i = 0; i < m && word[i] == text[i + j]; i++);
		if (i >= m) {
			nbOcc++;
		}
		j++;
		if ((nextOcc = findNextIndex(text, strlen(text), (size_t) j, word[0])) != -1) {
			j = nextOcc;
		}
	}
	return nbOcc;
}

// la sentinelle sert à ne pas tester à chaque fois si on est en fin de mot
int algorithme_naif_avec_boucle_interne_avec_boucle_rapide_avec_sentinelle(const char *word, int m, const char *text, int n) {
	if (word == NULL || text == NULL || m == 0 || n == 0) return 0;
	int i, j = 0;
	int nbOcc = 0;
	int nextOcc = -1;
	
	// création d'un copie du texte et ajout du mot à la fin du texte pour être sur d'avoir une occurence = sentinelle
	size_t newTextLength = (size_t) n+1 + strlen(word);
	char *newText = (char *) malloc(newTextLength * sizeof(char));
	if (newText == NULL) {
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	if (snprintf(newText, newTextLength, "%s%s", text, word) == 0) {
		perror("snprintf");
		exit(EXIT_FAILURE);
	}
	// s'arrête dès que la première occurence a été trouvé
	// int find = nbOcc != 1;
	while (nbOcc != 1) {
		for (i = 0; i < m && word[i] == newText[i + j]; i++);
		if (i >= m) {
			/*
			printf("shift : %d\n", j);
			printf("%s\n", word);
			printf("%*s%s\n", j, " ", newText);
			*/
			nbOcc++;
			/**
			 * METTRE un test si j est arrivée en fin de texte
			 * Demander au prof si la sentinelle, si y'a une occurence trouvé alors il faut vérifier si on est en fin de texte pour les occurences suivantes
			*/
		}
		j++;
		if ((nextOcc = findNextIndex(newText, strlen(newText), (size_t) j, word[0])) != -1) {
			j = nextOcc;
		}
	}
	return nbOcc;
}

// avec strncmp au lieu de comparer 1 par 1, on utilise strncmp mais on garde la boucle principale
int algorithme_naif_avec_strncmp_sans_boucle_rapide_sans_sentinelle(const char *word, int m, const char *text, int n) {
	if (word == NULL || text == NULL || m == 0 || n == 0) return 0;
	int i, j;
	int nbOcc = 0;
	for (j = 0; j <= n - m; ++j) {
		// Extraction de la fenêtre contenant le mot du texte
		const char *text_substr = substr(text, (size_t) j, strlen(word) + (size_t) j);
		// printf("Extrait : %s\n", text_substr);
		if (text_substr == NULL) {
			fprintf(stderr, "Error substr(%s,%d,%d) = NULL", word, i, j);
			exit(EXIT_FAILURE);
		}
		if (strncmp(text_substr, word, strlen(word)) == 0) {
			// printf("Strncmp : (%s, %s, %lu)\n", text_substr, word, strlen(word));
			nbOcc++;
		}
	}
	return nbOcc;
}

/*
int algorithme_naif_avec_strncmp_avec_boucle_rapide_sans_sentinelle(const char *word, size_t m, const char *text, size_t n) {
	if (word == NULL || text == NULL || m == 0 || n == 0) return 0;
	return 0;
}

int algorithme_naif_avec_strncmp_avec_boucle_rapide_avec_sentinelle(char *word, size_t m, const char *text, size_t n) {
	if (word == NULL || text == NULL || m == 0 || n == 0) return 0;
	return 0;
}*/

int findNextIndex(const char *word, size_t word_len, size_t start, char c) {
	if (word == NULL || word_len == 0) return -1;
	// printf("findNextIndex : word %s(%lu) - %lu - %c\n", word, word_len, start, c);
	for (size_t i = start; i < word_len; i++) {
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
