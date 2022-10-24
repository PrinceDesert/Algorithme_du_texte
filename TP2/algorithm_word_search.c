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
int naive_algorithm_inner_loop(const char *word, int m, const char *text, int n);
// algorithme naif, avec boucle interne, avec boucle rapide, sans sentinelle pour compter le nb d'occurence de word dans text
int naive_algorithm_inner_loop_quick_loop(const char *word, int m, const char *text, int n);
// algorithme naif, avec boucle interne, avec boucle rapide, avec sentinelle pour compter le nb d'occurence de word dans text
int naive_algorithm_inner_loop_quick_loop_sentinel(const char *word, int m, const char *text, int n);
	
// algorithme naif, avec strncmp, sans boucle rapide, sans sentinelle pour compter le nb d'occurence de word dans text 
int naive_algorithm_strncmp(const char *word, int m, const char *text, int n);
// algorithme naif, avec strncmp, avec boucle rapide, sans sentinelle pour compter le nb d'occurence de word dans text 
int naive_algorithm_strncmp_quick_loop(const char *word, int m, const char *text, int n);
// algorithme naif, avec strncmp, avec boucle rapide, avec sentinelle pour compter le nb d'occurence de word dans text
int naive_algorithm_strncmp_quick_loop_sentinel(const char *word, int m, const char *text, int n);
	
void preProcesssing_Morris_Pratt_algorithm(const char *word, int m, int goodPrefix[]);
int Morris_Pratt_algorithm(const char *word, int m, const char *text, int n);

// algorithme de Knuth-Morris-Pratt
void preProcesssing_Knuth_Morris_Pratt_algorithm(const char *word, int m, int bestPrefix[]);
int Knuth_Morris_Pratt_algorithm(const char *word, int m, const char *text, int n);
	
// algorithme de Boyer-Moore
void preProcesssing_Last_Occurence_Boyer_Moore_algorithm(const char *word, int m, int alphabetSize, int lastOcc[]);
void preProcesssing_Suffixes_Boyer_Moore_algorithm(const char *word, int m, int goodSuffixes[]);
void preProcesssing_Good_Suffixes_Boyer_Moore_algorithm(const char *word, int m, int goodSuffixes[]);
int Boyer_Moore_algorithm(const char *word, int m, const char *text, int n, int alphabetSize);

// algorithme de Horspool
int Horspool_algorithm(const char *word, int m, const char *text, int n);
// algorithme Quick Search
int Quick_Search_algorithm(const char *word, int m, const char *text, int n);
	
// utils
int findNextIndex(const char *word, size_t word_len, size_t start, char c);
char *substr(const char *src, size_t pos, size_t len);
int max(int a, int b);
int min(int a, int b);
	
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
	
	printf("== text : %s (length : %d)\n", text, text_length);
	printf("== word : %s (length : %d)\n", word, word_length);
	
	print_result_and_measured_time(
				naive_algorithm_inner_loop,
				"naive_algorithm_inner_loop",
				word, word_length, text, text_length);
				
	print_result_and_measured_time(
			naive_algorithm_inner_loop_quick_loop,
			"naive_algorithm_inner_loop_quick_loop",
			word, word_length, text, text_length);
	
	print_result_and_measured_time(
			naive_algorithm_inner_loop_quick_loop_sentinel,
			"naive_algorithm_inner_loop_quick_loop_sentinel CEST NORMAL QUE 1 A DEMANDER AU PROF CE QUI A ECRIT DANS LE COMMENTAIRE DU CODE POUR LE TEST DARRET",
			word, word_length, text, text_length);
	
	print_result_and_measured_time(
			naive_algorithm_strncmp,
			"naive_algorithm_strncmp",
			word, word_length, text, text_length);
	
	print_result_and_measured_time(
			naive_algorithm_strncmp_quick_loop,
			"naive_algorithm_strncmp_quick_loop",
			word, word_length, text, text_length);
	
	print_result_and_measured_time(
			naive_algorithm_strncmp_quick_loop_sentinel,
			"naive_algorithm_strncmp_quick_loop_sentinel CEST NORMAL QUE 1 A DEMANDER AU PROF CE QUI A ECRIT DANS LE COMMENTAIRE DU CODE POUR LE TEST DARRET",
			word, word_length, text, text_length);
	
	print_result_and_measured_time(
			naive_algorithm_strncmp_quick_loop_sentinel,
			"naive_algorithm_strncmp_quick_loop_sentinel CEST NORMAL QUE 1 A DEMANDER AU PROF CE QUI A ECRIT DANS LE COMMENTAIRE DU CODE POUR LE TEST DARRET",
			word, word_length, text, text_length);
	
	// text = "GCATCGCAGAGAGTATACAGTACG";
	// word = "GCAGAGAG";
	print_result_and_measured_time(
			Morris_Pratt_algorithm,
			"Morris_Pratt_algorithm",
			word, word_length, text, text_length);
		
	clock_t start_t = clock();
	int nbOcc = Boyer_Moore_algorithm(word, word_length, text, text_length, 13);
	clock_t end_t = clock();
	double time = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;
	printf("== %s : %d == (%f sec)\n", "Boyer_Moore_algorithm", nbOcc, time);
	
	
	return EXIT_SUCCESS;
}
	
int naive_algorithm_inner_loop(const char *word, int m, const char *text, int n) {
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
int naive_algorithm_inner_loop_quick_loop(const char *word, int m, const char *text, int n) {
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
int naive_algorithm_inner_loop_quick_loop_sentinel(const char *word, int m, const char *text, int n) {
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
int naive_algorithm_strncmp(const char *word, int m, const char *text, int n) {
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
	
int naive_algorithm_strncmp_quick_loop(const char *word, int m, const char *text, int n) {
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
	
int naive_algorithm_strncmp_quick_loop_sentinel(const char *word, int m, const char *text, int n) {
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
	
	
void preProcesssing_Morris_Pratt_algorithm(const char *word, int m, int goodPrefix[]) {
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
	
int Morris_Pratt_algorithm(const char *word, int m, const char *text, int n) {
	// pre-processing
	int goodPrefix[strlen(word) + 1];
	preProcesssing_Morris_Pratt_algorithm(word, m, goodPrefix);
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
	
void preProcesssing_Knuth_Morris_Pratt_algorithm(const char *word, int m, int bestPrefix[]) {
	int i, j;
	bestPrefix[0] = -1;
	i = 0;
	for (j = 1; j < m; j++) {
		if (word[i] == word[j]) {
			bestPrefix[j] = bestPrefix[i];
		} else {
			bestPrefix[j] = i;
			do {
				i = bestPrefix[i];
			} while (i >= 0 && word[i] != word[j]);
		}
		i++;
	}
	bestPrefix[m] = i;
}
	
int Knuth_Morris_Pratt_algorithm(const char *word, int m, const char *text, int n) {
	int bestPrefix[strlen(word) + 1];
	preProcesssing_Knuth_Morris_Pratt_algorithm(word, m, bestPrefix);
	int i = 0, j = 0;
	int nbOcc = 0;
	for (j = 0; j < n; j++) {
		while (i >= 0 && word[i] != text[j]) {
			i = bestPrefix[i];
		}
		i++;
		if (i >= m) {
			nbOcc++;
			i = bestPrefix[i];
		}
	}
	return nbOcc;
}
	
void preProcesssing_Last_Occurence_Boyer_Moore_algorithm(const char *word, int m, int alphabetSize, int lastOcc[]) {
	int i;
	for (i = 0; i < alphabetSize; i++)
		lastOcc[i] = m;
	for (i = 0; i <= m - 2; i++)
		lastOcc[(int) word[i]] = m - 1 - i;
}
	
void preProcesssing_Suffixes_Boyer_Moore_algorithm(const char *word, int m, int suff[]) {
	int f, g, i;
	f = 0;
	g = m - 1;
	suff[m - 1] = m;
	for (i = m - 2; i >= 0; i--) {
		if (i > g && suff[i + m - 1 - f] != i - g) {
			suff[i] = min(suff[i + m - 1 - f], i - g);
		} else {
			g = min(i, g);
			f = i;
			while (g >= 0 && word[g] == word[g + m - 1 - f]) {
				g--;
			}
			suff[i] = f - g;
		}
	}
}
	
void preProcesssing_Good_Suffixes_Boyer_Moore_algorithm(const char *word, int m, int goodSuffixes[]) {
	int i, j, suff[m];
	preProcesssing_Suffixes_Boyer_Moore_algorithm(word, m, suff);
	i = 0;
	for (j = m - 2; j >= -1; j--) {
		if (j == -1 || suff[j] == j + 1) {
			while (i < m - 1 - j) {
				goodSuffixes[i] = m - 1 - j;
				i++;
			}
		}
	}
	for (j = 0; j <= m - 2; j++) {
		goodSuffixes[m - 1 - suff[j]] = m - 1 - j;
	}
}

int Boyer_Moore_algorithm(const char *word, int m, const char *text, int n, int alphabetSize) {
	int i, j;
	int goodSuffixes[m];
	int lastOcc[alphabetSize];
	int nbOcc = 0;
	
	preProcesssing_Good_Suffixes_Boyer_Moore_algorithm(word, m, goodSuffixes);
	preProcesssing_Last_Occurence_Boyer_Moore_algorithm(word, m, alphabetSize, lastOcc);
	
	j = m - 1;
	while (j < n) {
		i = m - 1;
		while (i >= 0 && word[i] == text[j - m + 1 + i]) {
			i--;
		}
		if (i < 0) {
			nbOcc++;
			j += goodSuffixes[0];
		} else {
			j += max(goodSuffixes[i], lastOcc[(int) text[j - m + 1 + i]] - m + 1 + i);
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
	
int max(int a, int b) {
	return a > b ? a : b;
}
	
int min(int a, int b) {
	return a < b ? a : b;
}
