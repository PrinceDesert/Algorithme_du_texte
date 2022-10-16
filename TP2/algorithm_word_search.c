#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
	
/**
 * Algorithmes de recherche exacte d’un mot dans un texte
*/

// measure time : https://www.geeksforgeeks.org/how-to-measure-time-taken-by-a-program-in-c/

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
int algorithme_naif_avec_strncmp_avec_boucle_rapide_sans_sentinelle(const char *word, int m, const char *text, int n);
// algorithme naif, avec strncmp, avec boucle rapide, avec sentinelle pour compter le nb d'occurence de word dans text
int algorithme_naif_avec_strncmp_avec_boucle_rapide_avec_sentinelle(const char *word, int m, const char *text, int n);
	
// algorithme de Morris-Pratt
/**
 * Phase de pré-traitement :
 * Soit la table bon-préf à m +1 élements définies comme suit, pour 0 <= i <= m
 * bon-préf[i] = -1 si i = 0
 * bon-préf[i] = |Bord(x[0..i-1]| sinon
 * 
 * Algorithme :
 * i = 0
 * pour j=0 à n-1 faire
 *   tantque i>=0 et x[i] != y[i] faire
 *     i=bon-préf[i]
 *   i=i+1
 *   si i = m alors
 *      signaler une occurence de x
 *      i=bon-préf[i]
*/
void pre_processsing_algorithme_Morris_Pratt(const char *word, int m, int goodPrefix[]);
int algorithme_Morris_Pratt(const char *word, int m, const char *text, int n);

// algorithme de Knuth-Morris-Pratt
int algorithme_Knuth_Morris_Pratt(const char *word, int m, const char *text, int n);
// algorithme de Boyer-Moore
int algorithme_Boyer_Moore(const char *word, int m, const char *text, int n);
// algorithme de Horspool
int algorithme_Horspool(const char *word, int m, const char *text, int n);
// algorithme Quick Search
int algorithme_Quick_Search(const char *word, int m, const char *text, int n);
	
// utils
int findNextIndex(const char *word, size_t word_len, size_t start, char c);
char *substr(const char *src, size_t pos, size_t len);
	
// un generateur de texte, un generateur de mot en bash
// generer les courbes avec un autre outil
	
	
void print_result_and_measured_time(
	int (*function)(const char *word, int m, const char *text, int n),
	const char *function_name,
	const char *word, int m, const char *text, int n);

void print_result_and_measured_time(
	int (*function)(const char *word, int m, const char *text, int n),
	const char *function_name,
	const char *word, int m, const char *text, int n) {
	clock_t start_t = clock();
	int nbOcc = (*function)(word, m, text, n);
	clock_t end_t = clock();
	double time = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;
	printf("== %s : %d == (%f sec)\n", function_name, nbOcc, time);
}
	
int main(void) {
	
	const char *text = "atcgcgatgctag";
	const char *word = "gc";
	int text_length = (int) strlen(text);
	int word_length = (int) strlen(word);
	
	printf("== text : %s\n", text);
	printf("== word : %s\n", word);
	
	print_result_and_measured_time(
				algorithme_naif_avec_boucle_interne_sans_boucle_rapide_sans_sentinelle,
				"algorithme_naif_avec_boucle_interne_sans_boucle_rapide_sans_sentinelle",
				word, word_length, text, text_length);
				
	print_result_and_measured_time(
			algorithme_naif_avec_boucle_interne_avec_boucle_rapide_sans_sentinelle,
			"algorithme_naif_avec_boucle_interne_avec_boucle_rapide_sans_sentinelle",
			word, word_length, text, text_length);
	
	print_result_and_measured_time(
			algorithme_naif_avec_boucle_interne_avec_boucle_rapide_avec_sentinelle,
			"algorithme_naif_avec_boucle_interne_avec_boucle_rapide_avec_sentinelle CEST NORMAL QUE 1 A DEMANDER AU PROF CE QUI A ECRIT DANS LE COMMENTAIRE DU CODE POUR LE TEST DARRET",
			word, word_length, text, text_length);
	
	print_result_and_measured_time(
			algorithme_naif_avec_strncmp_sans_boucle_rapide_sans_sentinelle,
			"algorithme_naif_avec_strncmp_sans_boucle_rapide_sans_sentinelle",
			word, word_length, text, text_length);
	
	print_result_and_measured_time(
			algorithme_naif_avec_strncmp_avec_boucle_rapide_sans_sentinelle,
			"algorithme_naif_avec_strncmp_avec_boucle_rapide_sans_sentinelle",
			word, word_length, text, text_length);
	
	print_result_and_measured_time(
			algorithme_naif_avec_strncmp_avec_boucle_rapide_avec_sentinelle,
			"algorithme_naif_avec_strncmp_avec_boucle_rapide_avec_sentinelle CEST NORMAL QUE 1 A DEMANDER AU PROF CE QUI A ECRIT DANS LE COMMENTAIRE DU CODE POUR LE TEST DARRET",
			word, word_length, text, text_length);
	
	text = "GCATCGCAGAGAGTATACAGTACG";
	word = "GCAGAGAG";
	print_result_and_measured_time(
			algorithme_Morris_Pratt,
			"algorithme_Morris_Pratt",
			word, (int) strlen(word), text, (int) strlen(text));
	
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
	
// utilise findNextIndex pour passer à la prochaine occurence pour décaler la fenetre jusqu'a la prochaine occurence trouve ( = boucle rapide)
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
	
int algorithme_naif_avec_strncmp_avec_boucle_rapide_sans_sentinelle(const char *word, int m, const char *text, int n) {
	if (word == NULL || text == NULL || m == 0 || n == 0) return 0;
	int i, j = 0;
	int nbOcc = 0;
	int nextOcc = -1;
	while (j <= n - m) {
		const char *text_substr = substr(text, (size_t) j, strlen(word) + (size_t) j);
		if (text_substr == NULL) {
			fprintf(stderr, "Error substr(%s,%d,%d) = NULL", word, i, j);
			exit(EXIT_FAILURE);
		}
		if (strncmp(text_substr, word, strlen(word)) == 0) {
			nbOcc++;
		}
		j++;
		if ((nextOcc = findNextIndex(text, strlen(text), (size_t) j, word[0])) != -1) {
			j = nextOcc;
		}
	}
	return nbOcc;
}
	
int algorithme_naif_avec_strncmp_avec_boucle_rapide_avec_sentinelle(const char *word, int m, const char *text, int n) {
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
		const char *text_substr = substr(text, (size_t) j, strlen(word) + (size_t) j);
		if (text_substr == NULL) {
			fprintf(stderr, "Error substr(%s,%d,%d) = NULL", word, i, j);
			exit(EXIT_FAILURE);
		}
		if (strncmp(text_substr, word, strlen(word)) == 0) {
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
	
	
void pre_processsing_algorithme_Morris_Pratt(const char *word, int m, int goodPrefix[]) {
	int i, j;
	goodPrefix[0] = -1;
	i = 0;
	for (j = 1; j < m; j++) {
		goodPrefix[j] = i;
		while (i >= 0 && word[i] != word[j]) {
			i = goodPrefix[i];
		}
		i++;
	}
	goodPrefix[m] = i;
	/*
	for (int k = 0; k < (int) strlen(word)+1; k++) {
		printf("%d ", goodPrefix[k]);
	}
	printf("\n");
	*/
}
int algorithme_Morris_Pratt(const char *word, int m, const char *text, int n) {
	// pre-processing
	int goodPrefix[strlen(word) + 1];
	pre_processsing_algorithme_Morris_Pratt(word, m, goodPrefix);
	int i = 0, j = 0;
	int nbOcc = 0;
	for (j = 0; j < n; j++) {
		while (i >= 0 && word[i] != text[j]) {
			i = goodPrefix[i];
		}
		i++;
		if (i >= m) {
			nbOcc++;
			i = goodPrefix[i];
		}
	}
	return nbOcc;
}
	
	
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
	
