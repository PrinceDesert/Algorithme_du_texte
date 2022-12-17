SHELL = /bin/sh
CC = gcc
CFLAGS = -std=c99 -Wpedantic -Wall -Werror -Wextra -Wconversion -Wwrite-strings  -fstack-protector-all -fpie -D_FORTIFY_SOURCE=2 -O2 -D_XOPEN_SOURCE -g
EXE = ac-matrice transition ac-hachage

%.o : %.c
	$(CC) -c $(wildcard *.c) $(CFLAGS) -I inc

transition : transition_matrix_trie.o
	$(CC) -o $@ $^

ac-matrice : ac-matrice.o transition_matrix_trie.o queue.o
	$(CC) -o $@ $^

clean :
	rm -f $(wildcard *.o) $(EXE)
