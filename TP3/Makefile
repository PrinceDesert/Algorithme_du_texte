SHELL = /bin/sh
CC = gcc
CFLAGS = -std=c99 -Wpedantic -Wall -Wextra -Wconversion -Wwrite-strings -Werror -fstack-protector-all -fpie -D_FORTIFY_SOURCE=2 -O2 -D_XOPEN_SOURCE -g
EXE = genere-texte genere-mots queue ac-matrice

all : $(EXE)

# enere_texte :

transition : transition_matrix_trie.o
	$(CC) -o $@ $^

ac-matrice : ac-matrice.o transition_matrix_trie.o
	$(CC) -o $@ $^

%.o : %.c
	$(CC) -c $(wildcard *.c) $(CFLAGS)

transition_matrix_trie.o : transition_matrix_trie.c
	$(CC) -c $< $(CFLAGS) -I inc
	
hash_table_trie.o : hash_table_trie.c
	$(CC) -c $< $(CFLAGS) -I inc

clean :
	rm -f $(wildcard *.o) $(EXE)
