#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <algorithm_word_search.h>
	
/**
 * Algorithmes de recherche exacte d’un mot dans un texte
*/
#define ALPHABET_SIZE UCHAR_MAX

// avec sentinelle : concaténation du mot à la fin, sert à ne pas tester à chaque fois si on est en fin de mot (optimisation)
// trop à droite : si le mot a comparé dépasse la fin du texte
// test si trop à droite : que si occurence
// boucle rapide : décale la fenetre à la premier occurence de la lettre en gros c'est l'index qui se décale à une potentiel occurence
// measure time : https://www.geeksforgeeks.org/how-to-measure-time-taken-by-a-program-in-c/

int main(void) {
	
	/*---------------------------------------------------------------------*/
	/* Initilisation du texte et de l'ensembles des mots dans leur fichier */
	/*---------------------------------------------------------------------*/
	
	const char *text_filename = "./text.txt"; 
	size_t text_length_file = 5000;
	size_t text_alphabet_length_file = 70;
	char *text_buffer = text_generator(text_filename, text_length_file, text_alphabet_length_file);
	// printf("text generator : %s\n", text_buffer);
	
	const char *word_filename = "./word.txt";
	size_t nb_word = 20;
	size_t word_length_file = 4;
	size_t word_alphabet_length_file = 70;
	const char *word_separator = " ";
	char **word_buffer = word_generator(word_filename, nb_word, word_length_file, word_alphabet_length_file, word_separator);
	printf("word generator : \n");
	/*
	for (size_t i = 0; i < nb_word; i++) {
		printf("word[%lu] = %s\n", i, word_buffer[i]);
	}
	*/
	
	/*---------------------------*/
	/* Lancement des algorithmes */
	/*---------------------------*/
	
	const char *text = text_buffer; // "atcgagactactgacta";
	const char *word = NULL;
	int text_length = (int) strlen(text);
	int word_length = 0;
	
	printf("== text : %s (length : %d)\n", text, text_length);
	for (size_t i = 0; i < nb_word; i++) {
		
		word = word_buffer[i]; // "gac"
		word_length = (int) strlen(word);
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
				"naive_algorithm_inner_loop_quick_loop_sentinel",
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
				"naive_algorithm_strncmp_quick_loop_sentinel",
				word, word_length, text, text_length);
		
		print_result_and_measured_time(
				Morris_Pratt_algorithm,
				"Morris_Pratt_algorithm",
				word, word_length, text, text_length);

		print_result_and_measured_time(
				Knuth_Morris_Pratt_algorithm,
				"Knuth_Morris_Pratt_algorithm",
				word, word_length, text, text_length);
		
		print_result_and_measured_time(
				Boyer_Moore_algorithm,
				"Boyer_Moore_algorithm",
				word, word_length, text, text_length);
		print_result_and_measured_time(
				Horspool_algorithm,
				"Horspool_algorithm",
				word, word_length, text, text_length);
		print_result_and_measured_time(
				Quick_Search_algorithm,
				"Quick_Search_algorithm",
				word, word_length, text, text_length);
	}
	
	/*---------------------------*/
	/* Libération des ressources */
	/*---------------------------*/
	free(text_buffer);
	for (size_t i = 0; i < nb_word; i++) {
		free(word_buffer[i]);
	}
	free(word_buffer);

	return EXIT_SUCCESS;
}
	
/*--------------------------------------------------------------------------------------------------*/
/*                                      LES ALGORITHMES NAIVES                                      */
/*--------------------------------------------------------------------------------------------------*/
	
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
	
/**
 * Utilisation de la fonction util findNextIndex pour passer à la prochaine occurence pour 
 * décaler la fenêtre de cible jusqu'a la prochaine occurence trouvée (=boucle rapide)
*/
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
	
/**
 * la sentinelle sert à ne pas tester à chaque fois si on est en fin de mot
 * Un test droite s'effectue que si il y a une occurence de trouvée
*/
int naive_algorithm_inner_loop_quick_loop_sentinel(const char *word, int m, const char *text, int n) {
	if (word == NULL || text == NULL || m == 0 || n == 0) return 0;
	int i, j = 0;
	int nbOcc = 0;
	int nextOcc = -1;
	// création d'un copie du texte et ajout du mot à la fin du texte pour être sur d'avoir une occurence = sentinelle
	int newTextLength = ((int) strlen(word)) + (n + 1);
	char newText[newTextLength];
	if (snprintf(newText, (size_t) newTextLength, "%s%s", text, word) == 0) {
		perror("snprintf");
		exit(EXIT_FAILURE);
	}
	while (1) {
		for (i = 0; i < m && word[i] == newText[i + j]; i++);
		if (i >= m) {
			/*
			printf("shift : %d\n", j);
			printf("%s\n", word);
			printf("%*s%s\n", j, " ", newText);
			printf("i:%d, m:%d, j:%d, nbOcc : %d, j>=n -> %d>=%d ? %d\n", i, m, j, nbOcc, j, n, j >= n);
			*/
			nbOcc++;
			// Test trop à droite
			if (j >= n) {
				break;
			}
		}
		j++;
		if ((nextOcc = findNextIndex(newText, strlen(newText), (size_t) j, word[0])) != -1) {
			j = nextOcc;
		}
	}
	return nbOcc - 1;
}
	
/**
 * Utilisation de  strncmp au lieu de comparer lettre par lettre comme dans la méthode naive, 
 * mais on garde la boucle principale
*/
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
	int newTextLength = ((int) strlen(word)) + (n + 1);
	char newText[newTextLength];
	if (snprintf(newText, (size_t) newTextLength, "%s%s", text, word) == 0) {
		perror("snprintf");
		exit(EXIT_FAILURE);
	}

	while (1) {
		const char *text_substr = substr(text, (size_t) j, strlen(word) + (size_t) j);
		if (text_substr == NULL) {
			fprintf(stderr, "Error substr(%s,%d,%d) = NULL", word, i, j);
			exit(EXIT_FAILURE);
		}
		if (strncmp(text_substr, word, strlen(word)) == 0) {
			nbOcc++;
			// Test trop à droite
			if (j >= n) {
				break;
			}
		}
		j++;
		if ((nextOcc = findNextIndex(newText, strlen(newText), (size_t) j, word[0])) != -1) {
			j = nextOcc;
		}
	}
	return nbOcc - 1;
}
	
/*-----------------------------------------------------------------------------------------------------*/
/*                                      LES ALGORITHMES COMPLEXES                                      */
/*-----------------------------------------------------------------------------------------------------*/
	
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
	
void preProcesssing_Last_Occurence_Boyer_Moore_algorithm(const char *word, int m, int *lastOcc) {
	int i;
	for (i = 0; i < ALPHABET_SIZE; i++)
		lastOcc[i] = m;
	for (i = 0; i < m - 1; i++) {
		lastOcc[(int) word[i]] = m - 1 - i;
	}
	/*
	printf("Last occurence Boyer Moore : \n");
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		printf("%d ", lastOcc[i]);
	}
	printf("\n");
	*/
}
	
void preProcesssing_Suffixes_Boyer_Moore_algorithm(const char *word, int m, int *suff) {
	int f, g, i;
	f = 0;
	g = m - 1;
	suff[m - 1] = m;
	for (i = m - 2; i >= 0; i--) {
		if (i > g && suff[i + m - 1 - f] < i - g) {
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
	/*
	printf("Suffixes Boyer Moore : \n");
	for (i = 0; i < m; i++) {
		printf("%d ", suff[i]);
	}
	printf("\n");
	*/
}
	
void preProcesssing_Good_Suffixes_Boyer_Moore_algorithm(const char *word, int m, int *goodSuffixes) {
	int i, j;
	int suff[m+1];
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
	/*
	printf("Good Suffixes Boyer Moore : \n");
	for (i = 0; i < m; i++) {
		printf("%d ", goodSuffixes[i]);
	}
	printf("\n");
	*/
}

int Boyer_Moore_algorithm(const char *word, int m, const char *text, int n) {
	int i, j;
	int goodSuffixes[m+1];
	int lastOcc[ALPHABET_SIZE];
	int nbOcc = 0;

	preProcesssing_Good_Suffixes_Boyer_Moore_algorithm(word, m, goodSuffixes);
	preProcesssing_Last_Occurence_Boyer_Moore_algorithm(word, m, lastOcc);
	
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
	
int Horspool_algorithm(const char *word, int m, const char *text, int n) {
	int j;
	int lastOcc[ALPHABET_SIZE];
	char c;
	int nbOcc = 0;
	
	preProcesssing_Last_Occurence_Boyer_Moore_algorithm(word, m, lastOcc);
	
	j = 0;
	while (j <= n - m) {
		c = text[j + m - 1];
		if (word[m - 1] == c && memcmp(text + j, word, (size_t) (m - 1)) == 0)
			nbOcc++;
		j += lastOcc[(int) c];
	}
	return nbOcc;
}
	
	
void preProcesssing_Bad_Chars_Shift_Quick_Search_algorithm(const char *word, int m, int badChars[]) {
	int i;
	for (i = 0; i < ALPHABET_SIZE; i++)
		badChars[i] = m + 1;
	for (i = 0; i < m; i++)
		badChars[(int) word[i]] = m - i;
}
	
int Quick_Search_algorithm(const char *word, int m, const char *text, int n) {
	int j;
	int badChars[ALPHABET_SIZE];
	int nbOcc = 0;
	
	preProcesssing_Bad_Chars_Shift_Quick_Search_algorithm(word, m, badChars);
	
	j = 0;
	while (j <= n - m) {
		if (memcmp(text + j, word, (size_t) m) == 0)
			nbOcc++;
		j += badChars[(int) text[j + m]];
	}
	
	return nbOcc;
}
	
/*------------------------------------------------------------------------------------------------------------*/
/*                                      GENERATEUR DE TEXTE ET DE MOT(S)                                      */
/*------------------------------------------------------------------------------------------------------------*/
	
char * text_generator(const char *filename, size_t length_text, size_t length_alphabet) {
	assert(filename != NULL);
	assert(length_text > 0);
	assert(length_alphabet >= 2 && length_alphabet <= 70);
	FILE *fout = fopen(filename, "wb");
	if (fout == NULL) {
		fprintf(stderr, "Cannot open %s to write\n", filename);
		exit(EXIT_FAILURE);
	}
	size_t min = (size_t) '!';
	size_t max = min + (length_alphabet-1);
	char c = '\0';
	size_t i = 0;
	char *buffer = (char *) calloc(length_text + 1, sizeof(char));
	if (buffer == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (i < length_text) {
		c = (char) ((size_t) rand() % ((max + 1) - min) + min);
		buffer[i] = c;
		// fprintf(fout, "%c", c);
		i++;
	}
	buffer[i] = '\0';
	fprintf(fout, "%s", buffer);
	// printf("buffer : %s(%lu) - i : %lu - zero terminal : %d\n", buffer, strlen(buffer), i, buffer[strlen(buffer)] == '\0');
	if (fclose(fout) != 0) {
		fprintf(stderr, "Cannot close %s\n", filename);
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "Text generated in %s\n", filename);
	return buffer;
}
	
char ** word_generator(const char *filename, size_t nb_word, size_t length_word, size_t length_alphabet, const char *separator) {
	assert(filename != NULL);
	assert(length_word >= 1 && length_word <= 40);
	assert(length_alphabet >= 2 && length_alphabet <= 70);
	assert(separator != NULL);
	FILE *fout = fopen(filename, "wb");
	if (fout == NULL) {
		fprintf(stderr, "Cannot open %s to write\n", filename);
		exit(EXIT_FAILURE);
	}
	size_t min = (size_t) '!';
	size_t max = min + (length_alphabet-1);
	size_t i = 0;
	size_t j = 0;
	char word[length_word+strlen(separator)+1];
	char **buffer;
	size_t len_buf;
	size_t len_strbuf;
	len_buf = nb_word * sizeof(char *);
	buffer = (char **) malloc(len_buf);
	if (buffer == NULL) { perror("malloc"); exit(EXIT_FAILURE); }
	while (i < nb_word) {
		memset(word, '\0', sizeof(word));
		while (j < length_word) {
			word[j] = (char) ((size_t) rand() % ((max + 1) - min) + min);
			j++;
		}
		fprintf(fout, "%s", word);
		fprintf(fout, "%s", separator);
		len_strbuf = (strlen(word) + 1) * sizeof(char);
		buffer[i] = malloc(len_buf);
		if (buffer[i] == NULL) { perror("malloc"); exit(EXIT_FAILURE); }
		int bytes = snprintf(buffer[i], len_strbuf, "%s", word);
		if (bytes < 0 ||  bytes >= (int) len_strbuf) { perror("snprintf"); exit(EXIT_FAILURE); }
		j = 0;
		i++;
	}
	fprintf(fout, "%s", word);
	if (fclose(fout) != 0) {
		fprintf(stderr, "Cannot close %s\n", filename);
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "Words generated in %s\n", filename);
	return buffer;
}
	
/*-------------------------------------------------------------------------------------------------*/
/*                                      FONCTIONS UTILITAIRES                                      */
/*-------------------------------------------------------------------------------------------------*/
	
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

