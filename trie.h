#ifndef TRIE_H
#define TRIE_H

#include "table_hashage.h"

/* Vérification que l'une des macros MATRICE ou HACHAGE est définie */
#if !defined(MATRICE) && !defined(HACHAGE)
#error "Vous devez définir soit MATRICE soit HACHAGE pour compiler ce programme."
#endif

#ifdef MATRICE
struct _trie {
    int maxNode;    /* Nombre maximal de noeuds du trie */
    int nextNode;   /* Indice du prochain noeud disponible */
    int **transition; /* matrice de transition */
    char *finite;   /* états terminaux */
};

#elif defined(HACHAGE)
struct _trie {
    int maxNode;    /* Nombre maximal de noeuds du trie */
    int nextNode;   /* Indice du prochain noeud disponible */
    List *transition; /* listes d’adjacence */
    char *finite;   /* états terminaux */
};
#endif

typedef struct _trie *Trie;

/* Création d'un trie vide */
Trie createTrie(int maxNode);

/* Insertion d'un mot dans le trie */
void insertInTrie(Trie trie, unsigned char *w);

/* Vérification de la présence d'un mot dans le trie */
int isInTrie(Trie trie, unsigned char *w);

/* Insertion des préfixes d'un mot */
void insertPrefixInTrie(Trie trie, unsigned char *w);

/* Insertion des suffixes d'un mot */
void insertSuffixInTrie(Trie trie, unsigned char *w);

/* Insertion des facteurs d'un mot */
void insertFactInTrie(Trie trie, unsigned char *w);

#endif // TRIE_H
