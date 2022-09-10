# Variables du Makefile
SHELL = /bin/sh
CC = gcc
# Option de compilation
CFLAGS = -std=c99 -Wpedantic -Wall -Wextra -Wconversion -Wwrite-strings -Werror -fstack-protector-all -fpie -D_FORTIFY_SOURCE=2 -O2 -D_XOPEN_SOURCE -g
# Option d'édition de lien
LDFLAGS= -Wl,-z,relro,-z,now -pie -pthread
INCDIR=inc
OBJDIR=obj
BINDIR=bin
# Nom des fichiers sans l'extension c et o
TR_MATRIX = transition_matrix_trie
H_TABLE = hash_table_trie

#---------------------------------------------------------#
# Construction des dossiers bin et obj : make start_build #
#---------------------------------------------------------#
start_build :
	mkdir -p ./$(OBJDIR) ./$(BINDIR)

#-----------------------------------------------------#
# Lancement d'un client : make TR_MATRIX #
#-----------------------------------------------------#
# Éxécution du fichier éxécutable client
start_$(TR_MATRIX) : ./$(BINDIR)/$(TR_MATRIX)
	./$(BINDIR)/$(TR_MATRIX)
# Génération de l'éxécutable client et édition des liens
./$(BINDIR)/$(TR_MATRIX) : ./$(OBJDIR)/$(TR_MATRIX).o
	$(CC) -o ./$(BINDIR)/$(TR_MATRIX) ./$(OBJDIR)/$(TR_MATRIX).o $(LDFLAGS)
# Compilation TR_MATRIX.c pour générer le fichier objet dans le dossier ./$(OBJDIR)
./$(OBJDIR)/$(TR_MATRIX).o : ./$(SRCDIR)/$(TR_MATRIX).c
	$(CC) -c ./$(SRCDIR)/$(TR_MATRIX).c $(CFLAGS) -I ./$(INCDIR) -o ./$(OBJDIR)/$(TR_MATRIX).o

#-------------------------------------------#
# Lancement du démon : make hash_table_trie # 
#-------------------------------------------#
# Éxécution du fichier éxécutable hash_table_trie
start_$(H_TABLE) : ./$(BINDIR)/$(H_TABLE)
	./$(BINDIR)/$(H_TABLE)
# Génération de l'éxécutable hash_table_trie et édition des liens
./$(BINDIR)/$(H_TABLE) : ./$(OBJDIR)/$(H_TABLE).o
	$(CC) -o ./$(BINDIR)/$(H_TABLE) ./$(OBJDIR)/$(H_TABLE).o $(LDFLAGS)
# Compilation hash_table_trie.c pour générer le fichier objet dans le dossier ./$(OBJDIR)
./$(OBJDIR)/$(H_TABLE).o : ./$(SRCDIR)/$(H_TABLE).c
	$(CC) -c ./$(SRCDIR)/$(H_TABLE).c $(CFLAGS) -I ./$(INCDIR) -o ./$(OBJDIR)/$(H_TABLE).o

#-----------#
# Nettoyage #
#-----------#

# clean : supprime les fichiers objets et éxécutables
clean :
	rm -rf ./$(OBJDIR)/*.o ./$(BINDIR)/*

# mrproper : supprime les fichiers objets, éxécutables et créer durant l'éxécution de l'application
mrproper : clean
	rm -rf ./$(BINDIR)/$(H_TABLE) ./$(BINDIR)/$(TR_MATRIX) ./$(OBJDIR) ./$(BINDIR)
	

# =========================================================================
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~ Tutoriel Makefile ~~~~~~~~~~~~~~~~~~~~~~~~~~~
# =========================================================================

# Variables pour les règles générales (mais inutile pour ce projet) \
EXEC = main \
SRC = $(wildcard *.c) \
OBJ = $(SRC:.c=.o) \

#------------------#
# Règles générales #
#------------------#
#Règles pour compiler, édition des liens et éxécuter \
all : $(EXEC) \
	./$(EXEC) \
 Création du fichier éxécutable \
$(EXEC) : $(OBJ) \
	$(CC) -o $(EXEC) $(OBJDIR)/$(OBJ) $(LDFLAGS) \
 Génération des fichiers objets \
$(OBJDIR)/%.o : %.c \
	$(CC) -c $(SRC) $(CFLAGS) \
Les règles générales sont inutiles car pour ce projet.

# Tutoriel : https://www.youtube.com/watch?v=-riHEHGP2DU&ab_channel=FormationVid%C3%A9o

# ========================= 
# ~~ Variables spéciales ~~
# =========================

# $@ : nom de la cible se trouvant le $@
# $< : nom de la première dépendance
# $^ : la liste des dépendances
# $? : la liste des dépendances plus récentes que la cible
# $* : le nom du fichier sans son extension

# %.c : Tous les fichiers .c
# %.o : Tous les fichiers .o
