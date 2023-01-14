SHELL = /bin/sh
CC = gcc
CFLAGS = -std=c99 -Wpedantic -Wall -Werror -Wextra -Wconversion -Wwrite-strings  -fstack-protector-all -fpie -D_FORTIFY_SOURCE=2 -O2 -D_XOPEN_SOURCE -g
EXE = ac-matrice ac-hachage genere-texte genere-mots

all : ac-matrice ac-hachage genere-texte genere-mots

%.o : %.c
	$(CC) -c $(wildcard *.c) $(CFLAGS) -I inc

ac-matrice : ac-matrice.o transition_matrix_trie.o queue.o
	$(CC) -o $@ $^
	
ac-hachage : ac-hachage.o hash_table_trie.o queue.o
	$(CC) -o $@ $^

genere-texte : genere-texte.o
	$(CC) -o $@ $^
	
genere-mots : genere-mots.o
	$(CC) -o $@ $^
	
clean :
	rm -f $(wildcard *.o) $(EXE)
