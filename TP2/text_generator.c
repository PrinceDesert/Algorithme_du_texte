#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "./text.txt"

void generator1(size_t length);

/**
 * générateur pseudo-aléatoire de texte permettant de stocker
 * dans des fichiers des textes d’une longueur donnée sur un alphabet de taille donnée.
 * Utiliser ce générateur pour produire des textes de longueur 500 000 sur des alphabets de taille 2, 4, 20 et 70.
*/
void generator1(size_t length) {
	FILE *fout = fopen(FILENAME, "wb");
	if (fout == NULL) {
		fprintf(stderr, "Impossible to open %s to write\n", FILENAME);
		return;
	}
	// A-Z : 65-90
	// a-z : 97-122
	// rand() % (max + 1 - min) + min
	// rand to choose upper or lower letters
	short rL = rand() % 2;
	char a = 'A';
	char z = 'Z';
	if (rL) {
		a = 'A';
		z = 'Z';
	}
	int i = 0;
	char c = '\0';
	while (i++ < length) {
		c = (rand() % ((((int) z) + 1) - ((int) a)) + ((int) a));
		fprintf(fout, "%c", c);
	}
	if (fclose(fout) != 0) {
		fprintf(stderr, "Cannot close %s\n", FILENAME);
		return;
	}
}

int main() {
	size_t length = length;
	generator1(500000);
	return EXIT_SUCCESS;
}
