# Makefile
CC = gcc
CFLAGS = -Wall -g -std=c99
COMMON_OBJ = main.o trie.o table_hashage.o

all: matrice hachage

matrice: CFLAGS += -DMATRICE
matrice: $(COMMON_OBJ)
	$(CC) $(CFLAGS) $(COMMON_OBJ) -o trie_matrice

hachage: CFLAGS += -DHACHAGE
hachage: $(COMMON_OBJ)
	$(CC) $(CFLAGS) $(COMMON_OBJ) -o trie_hachage

main.o: main.c trie.h
	$(CC) $(CFLAGS) -c main.c

trie.o: trie.c trie.h table_hashage.h
	$(CC) $(CFLAGS) -c trie.c

table_hashage.o: table_hashage.c table_hashage.h
	$(CC) $(CFLAGS) -c table_hashage.c

clean:
	rm -f *.o trie_matrice trie_hachage
