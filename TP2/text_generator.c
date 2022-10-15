#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define FILENAME "./text.txt"

/**
 * Écrire un premier générateur pseudo-aléatoire de texte permettant de stocker
 * dans des fichiers des textes d’une longueur donnée sur un alphabet de taille donnée.
 * Utiliser ce générateur pour produire des textes de longueur 500 000 sur des alphabets de taille 2, 4, 20 et 70.
*/
void generator1(const char *filename, size_t length_text, size_t length_alphabet);

/**
 * Écrire un second générateur pseudo-aléatoire de mots permettant de stocker dans des fichiers un nombre de mots donné, d’une longueur donnée sur un alphabet de taille donnée.
 * Utiliser ce générateur pour produire des ensembles de 100 mots de longueur 4, 5, 6, 7, 8, 9, 10, 15, 20, 30, 40 et 50 sur des alphabets de taille 2, 4, 20 et 70.
*/
void generator2(const char *filename, size_t nb_wordn size_t length_word, size_t length_alphabet, const *char separator);

void generator1(const char *filename, size_t length_text, size_t length_alphabet) {
	assert(filename != NULL);
	assert(length_text > 0);
	assert(length_alphabet >= 2 && length_alphabet <= 70);
	FILE *fout = fopen(filename, "wb");
	if (fout == NULL) {
		fprintf(stderr, "Cannot open %s to write\n", filename);
		return;
	}
	size_t min = (size_t) '!';
	size_t max = min + length_alphabet;
	char c = '\0';
	size_t i = 0;
	while (i++ < length_text) {
		c = (char) ((size_t) rand() % ((max + 1) - min) + min);
		fprintf(fout, "%c", c);
	}
	if (fclose(fout) != 0) {
		fprintf(stderr, "Cannot close %s\n", filename);
		return;
	}
	fprintf(stdout, "Text generated in %s\n", filename);
}


void generator2(const char *filename, size_t nb_word, size_t length_word, size_t length_alphabet, const *char separator) {
	assert(filename != NULL);
	assert(length_word >= 4 && length_word <= 40);
	assert(length_alphabet >= 2 && length_alphabet <= 70);
	assert(separator != NULL);
	FILE *fout = fopen(filename, "wb");
	if (fout == NULL) {
		fprintf(stderr, "Cannot open %s to write\n", filename);
		return;
	}
	size_t min = (size_t) '!';
	size_t max = min + length_alphabet;
	char c = '\0';
	size_t i = 0;
	size_t j = 0;
	while (i++ < nb_word) {
		char word[length_word];
		while (j++ < length_word) {
			c = (char) ((size_t) rand() % ((max + 1) - min) + min);
			fprintf(fout, "%c", c);
		}
		fprintf(fout, "%s", separator);
		j = 0;
	}
	if (fclose(fout) != 0) {
		fprintf(stderr, "Cannot close %s\n", filename);
		return;
	}
}

int main(void) {
	size_t length_text = 500000;
	size_t length_alphabet = 70;
	generator1(FILENAME, length_text, length_alphabet);
	return EXIT_SUCCESS;
}
