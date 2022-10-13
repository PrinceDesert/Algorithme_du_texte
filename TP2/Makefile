SHELL = /bin/sh
CC = gcc
CFLAGS = -std=c99 -Wpedantic -Wall -Wextra -Wconversion -Wwrite-strings -Werror -fstack-protector-all -fpie -D_FORTIFY_SOURCE=2 -O2 -D_XOPEN_SOURCE -g
LDFLAGS= -Wl,-z,relro,-z,now -pie

IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)
ODIR=obj
_DEPS = exercice.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
_OBJ = exercice.o text_generator.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

exercice: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f $(ODIR)/*.o $(INCDIR)/*~
