#include <stdio.h>
#include <stdlib.h>
#include <string.h>
	
#define FILENAME "text_generator"
	
char ** genere_mots(size_t nb_mot, size_t min_taille_mot, size_t max_taille_mot, size_t taille_alphabet);
	
int main(void) {
	size_t nb_mot = 5, min_taille_mot = 5, max_taille_mot = 7, taille_alphabet = 2;
	genere_mots(nb_mot, min_taille_mot, max_taille_mot, taille_alphabet);
	return EXIT_SUCCESS;
}
	
char ** genere_mots(size_t nb_mot, size_t min_taille_mot, size_t max_taille_mot, size_t taille_alphabet) {
	if (nb_mot < 1 || min_taille_mot < 1 || max_taille_mot < 1 || 
		min_taille_mot > max_taille_mot ||  max_taille_mot < min_taille_mot) {
		return NULL;
	}
	size_t min_alphabet = (size_t) '!';
	size_t max_alphabet = min_alphabet + (taille_alphabet - 1);
	size_t i = 0;
	size_t j = 0;
	size_t rand_length_word = 0;
	char word[max_taille_mot];
	char **buffer;
	size_t len_buf;
	size_t len_strbuf;
	len_buf = nb_mot * sizeof(char *);
	buffer = (char **) malloc(len_buf);
	if (buffer == NULL) { perror("malloc"); exit(EXIT_FAILURE); }
	while (i < nb_mot) {
		memset(word, '\0', sizeof(word));
		rand_length_word = ((size_t) rand() % ((max_taille_mot + 1) - min_taille_mot) + min_taille_mot);
		while (j < rand_length_word) {
			word[j] = (char) ((size_t) rand() % ((max_alphabet + 1) - min_alphabet) + min_alphabet);
			j++;
		}
		fprintf(stdout, "%s\n", word);
		len_strbuf = (strlen(word) + 1) * sizeof(char);
		buffer[i] = malloc(len_buf);
		if (buffer[i] == NULL) { perror("malloc"); exit(EXIT_FAILURE); }
		int bytes = snprintf(buffer[i], len_strbuf, "%s", word);
		if (bytes < 0 ||  bytes >= (int) len_strbuf) { perror("snprintf"); exit(EXIT_FAILURE); }
		j = 0;
		i++;
	}
	return buffer;
}
	

