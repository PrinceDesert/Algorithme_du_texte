#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
	
/**
 * Écrire un premier générateur pseudo-aléatoire de texte permettant de stocker
 * dans des fichiers des textes d’une longueur donnée sur un alphabet de taille donnée.
 * Utiliser ce générateur pour produire des textes de longueur 500 000 sur des alphabets de taille 2, 4, 20 et 70.
*/
char * text_generator(const char *filename, size_t length_text, size_t length_alphabet);
	
/**
 * Écrire un second générateur pseudo-aléatoire de mots permettant de stocker dans des fichiers un nombre de mots donné, d’une longueur donnée sur un alphabet de taille donnée.
 * Utiliser ce générateur pour produire des ensembles de 100 mots de longueur 4, 5, 6, 7, 8, 9, 10, 15, 20, 30, 40 et 50 sur des alphabets de taille 2, 4, 20 et 70.
 * Chaque mot écrit dans un fichier est séparé un par separator
*/
char ** word_generator(const char *filename, size_t nb_word, size_t length_word, size_t length_alphabet, const char *separator);
	
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
	assert(length_word >= 4 && length_word <= 40);
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
		for (size_t k = 0; k < strlen(separator); k++) {
			word[j++] = separator[k];
		}
		fprintf(fout, "%s", word);
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
	
int main(void) {
	
	size_t length_text = 100;
	size_t length_alphabet = 70;
	char *text_buffer = text_generator("./test1.txt", length_text, length_alphabet);
	printf("text generator : %s\n", text_buffer);
	free(text_buffer);
	
	size_t nb_word = 10;
	size_t length_word = 4;
	length_alphabet = 4;
	const char *separator = " ";
	char **word_buffer = word_generator("./test2.txt", nb_word, length_word, length_alphabet, separator);
	printf("word generator : \n");
	for (size_t i = 0; i < nb_word; i++) {
		printf("word[%lu] = %s\n", i, word_buffer[i]);
	}
	for (size_t i = 0; i < nb_word; i++) {
		free(word_buffer[i]);
	}
	free(word_buffer);
	return EXIT_SUCCESS;
}
