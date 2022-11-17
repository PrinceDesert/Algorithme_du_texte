SHELL = /bin/sh
CC = gcc
CFLAGS = -std=c99 -Wpedantic -Wall -Wextra -Wconversion -Wwrite-strings -Werror -fstack-protector-all -fpie -D_FORTIFY_SOURCE=2 -O2 -D_XOPEN_SOURCE -g
EXE = genere-texte genere-mots queue ac-matrice

all : $(EXE)

% : %.c
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm -f $(EXE)
