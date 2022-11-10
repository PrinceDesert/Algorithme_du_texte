#include <stdio.h>
#include <stdlib.h>
#include <string.h>
	
char * genere_texte(size_t taille_texte, size_t taille_alphabet);
	
int main(void) {
	size_t taille_texte = 4;
	size_t taille_alphabet = 2;
	genere_texte(taille_texte, taille_alphabet);
	return EXIT_SUCCESS;
}
	
char * genere_texte(size_t taille_texte, size_t taille_alphabet) {
	if (taille_texte < 1 || taille_alphabet < 1) {
		return NULL;
	}
	size_t min_alphabet = (size_t) '!';
	size_t max_alphabet = min_alphabet + (taille_alphabet - 1);
	char c = '\0';
	size_t i = 0;
	char *buffer = (char *) calloc(taille_texte + 1, sizeof(char));
	if (buffer == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (i < taille_texte) {
		c = (char) ((size_t) rand() % ((max_alphabet + 1) - min_alphabet) + min_alphabet);
		buffer[i] = c;
		// fprintf(stdout, "%c", c);
		i++;
	}
	buffer[i] = '\0';
	fprintf(stdout, "%s", buffer);
	return buffer;
}
	

