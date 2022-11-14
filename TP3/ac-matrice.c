#include <stdio.h>
#include <stdlib.h>

int ac_matrice(const char *filename_word, const char *filename_text);

int main(void) {
	
	return EXIT_SUCCESS;
}

int ac_matrice(const char *filename_word, const char *filename_text) {
	
	return 0;
}

void pre_ac(const char *x, int k) {
	Trie trie = createTrie(maxNode);
	if (trie == NULL) {
		exit(EXIT_FAILURE);
	}
	char *q0 = "";
	// for i 
	insertInTrie(trie, q0);
	
}

// x le mot mot, num etat
// δ(e, x[i]) = num état il y a la lettre x[i]
const char* entrer(const char *x, int e) {
	int i = 0;
	int len_x = (int) strlen(x);
	// j soit égale à l'indice de la lettre à faire
	// cherche le plus long préfixe dans le trie
	while (i < len_x && trie->transition[i][x[i]] == e) {
		e = trie->transition[i][x[i]];
		i++;
	}
	while (i < len_x) {
		// crée un état s
		trie->transition[i][x[i]] = trie->nextNode++;
		e = trie->nextNode;
		i++;
	}
	return x;
}

// e = num état
int completer(int e) {
	aho_queue q = new_aho_queue();
	// crée une liste des transitions de e
	int *transitions = 
	// while (notempty(l)) {
	
	// }
}

// La liste des transitions
// struct transition {int startNode, int endNode, char letter}
// *transition = list des transitions
// premier 
// suivant

// file d'entier p est l'état suivant de e ou a est la lettre de transition
// enfiler, defiler

// la fonction sup regarde le plus long suffixe pour trouver l'état où atterir
