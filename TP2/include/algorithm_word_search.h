#ifndef __ALGORITHM_WORD_SEARCH__
#define __ALGORITHM_WORD_SEARCH__
	#include <stdlib.h>
	
/**
 * Algorithmes de recherche exacte d’un mot dans un texte
 * Générateur de texte et d'un ensemble de mot(s)
 * Fonctions utilitaires
*/

/*----------------------------------------------------------*/
/*					LES ALGORITHMES NAIVES					*/
/*----------------------------------------------------------*/

/**
 * algorithme naif, avec boucle interne, sans boucle rapide, sans sentinelle (word = mot à trouver) pour compter le nombre d'occurence(s) de word dans text
 * @return Le nombre d'occurence du mot dans le text
 * @param word : le mot
 * @param m : la taille du mot
 * @param text : le texte
 * @param n : la taille du texte
*/
int naive_algorithm_inner_loop(const char *word, int m, const char *text, int n);

/**
 * algorithme naif, avec boucle interne, avec boucle rapide, sans sentinelle pour compter le nombre d'occurence(s) de word dans text
 * @return Le nombre d'occurence du mot dans le text
 * @param word : le mot
 * @param m : la taille du mot
 * @param text : le texte
 * @param n : la taille du texte
*/
int naive_algorithm_inner_loop_quick_loop(const char *word, int m, const char *text, int n);

/**
 * algorithme naif, avec boucle interne, avec boucle rapide, avec sentinelle pour compter le nombre d'occurence(s) de word dans text
 * @return Le nombre d'occurence du mot dans le text
 * @param word : le mot
 * @param m : la taille du mot
 * @param text : le texte
 * @param n : la taille du texte
*/
int naive_algorithm_inner_loop_quick_loop_sentinel(const char *word, int m, const char *text, int n);

/**
 * algorithme naif, avec strncmp, sans boucle rapide, sans sentinelle pour compter le nombre d'occurence(s) de word dans text 
 * @return Le nombre d'occurence du mot dans le text
 * @param word : le mot
 * @param m : la taille du mot
 * @param text : le texte
 * @param n : la taille du texte
*/
int naive_algorithm_strncmp(const char *word, int m, const char *text, int n);

/**
 * algorithme naif, avec strncmp, avec boucle rapide, sans sentinelle pour compter le nombre d'occurence(s) de word dans text
 * @return Le nombre d'occurence du mot dans le text
 * @param word : le mot
 * @param m : la taille du mot
 * @param text : le texte
 * @param n : la taille du texte
*/
int naive_algorithm_strncmp_quick_loop(const char *word, int m, const char *text, int n);

/**
 * algorithme naif, avec strncmp, avec boucle rapide, avec sentinelle pour compter le nombre d'occurence(s) de word dans text
 * @return Le nombre d'occurence du mot dans le text
 * @param word : le mot
 * @param m : la taille du mot
 * @param text : le texte
 * @param n : la taille du texte
*/
int naive_algorithm_strncmp_quick_loop_sentinel(const char *word, int m, const char *text, int n);

/*----------------------------------------------------------*/
/*					LES ALGORITHMES COMPLEXES				*/
/*----------------------------------------------------------*/

/**
 * Phase de pré-traitement de l'algorithme Morris-Pratt
 * @param word : le mot
 * @param m : la taille du mot
 * @param goodPrefix : la table de bon-préfixe
*/
void preProcesssing_Morris_Pratt_algorithm(const char *word, int m, int goodPrefix[]);
/**
 * Algorithme de Morris-Pratt
 * @param word : le mot
 * @param m : la taille du mot
 * @param text : le texte
 * @param n : la taille du texte
*/
int Morris_Pratt_algorithm(const char *word, int m, const char *text, int n);

/**
 * Phase de pré-traitement de l'algorithme Knuth-Morris-Pratt
 * @param word : le mot
 * @param m : la taille du mot
 * @param goodPrefix : la table de meilleur-préfixe
*/
void preProcesssing_Knuth_Morris_Pratt_algorithm(const char *word, int m, int bestPrefix[]);
/**
 * Algorithme de Knuth-Morris-Pratt
 * @param word : le mot
 * @param m : la taille du mot
 * @param text : le texte
 * @param n : la taille du texte
*/
int Knuth_Morris_Pratt_algorithm(const char *word, int m, const char *text, int n);

/**
 * Phase de pré-traitement de l'algorithme Boyer-Moore
 * @param word : le mot
 * @param m : la taille du mot
 * @param lastOcc : la table des dernières occurences
*/
void preProcesssing_Last_Occurence_Boyer_Moore_algorithm(const char *word, int m, int lastOcc[]);
/**
 * Phase de pré-traitement de l'algorithme Boyer-Moore
 * @param word : le mot
 * @param m : la taille du mot
 * @param suff : la table de suffixe
*/
void preProcesssing_Suffixes_Boyer_Moore_algorithm(const char *word, int m, int suff[]);
/**
 * Phase de pré-traitement de l'algorithme Boyer-Moore
 * @param word : le mot
 * @param m : la taille du mot
 * @param goodSuffixes : la table de bon-suffixe
*/
void preProcesssing_Good_Suffixes_Boyer_Moore_algorithm(const char *word, int m, int goodSuffixes[]);
/**
 * Algorithme de Boyer-Moore
 * @param word : le mot
 * @param m : la taille du mot
 * @param text : le texte
 * @param n : la taille du texte
*/
int Boyer_Moore_algorithm(const char *word, int m, const char *text, int n);

/**
 * Algorithme de Horspool
 * @param word : le mot
 * @param m : la taille du mot
 * @param text : le texte
 * @param n : la taille du texte
*/
int Horspool_algorithm(const char *word, int m, const char *text, int n);

/**
 * Phase de pré-traitement de l'algorithme Quick Search
 * @param word : le mot
 * @param m : la taille du mot
 * @param badChars : la table des mauvais caractères (décalage)
*/
void preProcesssing_Bad_Chars_Shift_Quick_Search_algorithm(const char *word, int m, int badChars[]);
/**
 * Algorithme de Quick Search
 * @param word : le mot
 * @param m : la taille du mot
 * @param text : le texte
 * @param n : la taille du texte
*/
int Quick_Search_algorithm(const char *word, int m, const char *text, int n);

/*----------------------------------------------------------*/
/*					FONCTIONS UTILITAIRES					*/
/*----------------------------------------------------------*/
/**
 * @return l'index de la position du caractère c dans le mot word
 * @param : le mot
 * @param word_len : la taille du mot
 * @param start : le début de la position de la phase de recherche
 * @param c : le caractère à rechercher
*/
int findNextIndex(const char *word, size_t word_len, size_t start, char c);
/**
 * substring 
*/
char *substr(const char *src, size_t pos, size_t len);
/**
 * @return le maximum entre a et b
 * @param a : la valeur entière de a
 * @param b : la valeur entière de b
*/ 
int max(int a, int b);
/**
 * @return le min entre a et b
 * @param a : la valeur entière de a
 * @param b : la valeur entière de b
*/
int min(int a, int b);

/**
 * Écrire un premier générateur pseudo-aléatoire de texte permettant de stocker
 * dans des fichiers des textes d’une longueur donnée sur un alphabet de taille donnée.
 * Utiliser ce générateur pour produire des textes de longueur 500 000 sur des alphabets de taille 2, 4, 20 et 70.
 * @return le texte dans une chaîne de caractères
 * @param filename : le fichier dans lequel il faut écrire le texte à générer
 * @param length_text : la taille du texte
 * @param length_alphabet : la taille de l'alphabet
*/
char * text_generator(const char *filename, size_t length_text, size_t length_alphabet);

/**
 * Écrire un second générateur pseudo-aléatoire de mots permettant de stocker dans des fichiers un nombre de mots donné, d’une longueur donnée sur un alphabet de taille donnée.
 * Utiliser ce générateur pour produire des ensembles de 100 mots de longueur 4, 5, 6, 7, 8, 9, 10, 15, 20, 30, 40 et 50 sur des alphabets de taille 2, 4, 20 et 70.
 * Chaque mot écrit dans un fichier est séparé un par separator
 * @return Retourne un tableau de chaîne de caractères
 * @param filename : le fichier dans lequel il faut écrire l'ensemble de mots
 * @param nb_word : le nombre de mots
 * @param length_word : la taille des mots
 * @param length_alphabet : la taille de l'alphabet
 * @param separator : le séparateur entre les mots
*/
char ** word_generator(const char *filename, size_t nb_word, size_t length_word, size_t length_alphabet, const char *separator);

/**
 * Affichage des résultats d'une fonction de recherche de mots et affiche le temps d'éxécution de cette fonction
 * Ne fonctionne que pour les algorithmes naives, l'algorithme de Morris-Prath et l'algorithme de Knuth-Morris-Prath
 * @param function(word, m, text, n) : la fonction de recherche de mots
 * @param function_name : le nom de la fonction
*/
void print_result_and_measured_time(
	int (*function)(const char *word, int m, const char *text, int n),
	const char *function_name,
	const char *word, int m, const char *text, int n);

#endif