SHELL = /bin/sh
CC = gcc
CFLAGS = -std=c99 -Wpedantic -Wall -Wextra -Wconversion -Wwrite-strings -Werror -fstack-protector-all -fpie -D_FORTIFY_SOURCE=2 -O2 -D_XOPEN_SOURCE -g
EXE = algorithm_word_search

all : $(EXE)

% : %.c
	$(CC) $(CFLAGS) -I ./include $< -o $@

clean :
	rm -f $(EXE) *.txt
