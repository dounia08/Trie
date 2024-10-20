#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "trie.h"
#include "table_hashage.h"

Trie createTrie(int maxNode) {
    if (maxNode <= 0) {
        fprintf(stderr, "Erreur: maxNode doit être supérieur à 0.\n");
        exit(EXIT_FAILURE);
    }

    Trie trie = (Trie)malloc(sizeof(struct _trie));
    if (!trie) {
        fprintf(stderr, "Erreur: échec de l'allocation mémoire pour le trie.\n");
        exit(EXIT_FAILURE);
    }

    trie->maxNode = maxNode;
    trie->nextNode = 1;

#ifdef MATRICE
    trie->transition = (int **)malloc(UCHAR_MAX * sizeof(int *));
    for (int i = 0; i < UCHAR_MAX; i++) {
        trie->transition[i] = (int *)malloc(maxNode * sizeof(int));
        for (int j = 0; j < maxNode; j++) {
            trie->transition[i][j] = -1;  // Indique aucune transition
        }
    }
#else
    trie->transition = (List *)calloc(maxNode, sizeof(List));
#endif

    trie->finite = (char *)calloc(maxNode, sizeof(char));
    return trie;
}

void freeTrie(Trie trie) {
    if (!trie) return;

#ifdef MATRICE
    for (int i = 0; i < UCHAR_MAX; i++) {
        free(trie->transition[i]);
    }
    free(trie->transition);
#else
    for (int i = 0; i < trie->maxNode; i++) {
        List current = trie->transition[i];
        while (current) {
            List temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(trie->transition);
#endif

    free(trie->finite);
    free(trie);
}

void insertInTrie(Trie trie, unsigned char *w) {
    int currentState = 0;
    while (*w) {
        unsigned char letter = *w;
#ifdef MATRICE
        if (trie->transition[letter][currentState] == -1) {
            if (trie->nextNode >= trie->maxNode) {
                fprintf(stderr, "Erreur: nombre maximal de noeuds atteint.\n");
                exit(EXIT_FAILURE);
            }
            trie->transition[letter][currentState] = trie->nextNode++;
        }
        currentState = trie->transition[letter][currentState];
#else
        int index = fonctionDeHashage(letter, trie->maxNode);
        updateState(trie, currentState, letter);
        currentState = trie->nextNode - 1;
#endif
        ++w;
    }
    trie->finite[currentState] = 1;  // Marquer l'état comme terminal
}

int isInTrie(Trie trie, unsigned char *w) {
    int currentState = 0;
    while (*w) {
        unsigned char letter = *w;
#ifdef MATRICE
        if (trie->transition[letter][currentState] == -1) {
            return 0;  // Mot non trouvé
        }
        currentState = trie->transition[letter][currentState];
#else
        int index = fonctionDeHashage(letter, trie->maxNode);
        List temp = trie->transition[index];
        while (temp && !(temp->startNode == currentState && temp->letter == letter)) {
            temp = temp->next;
        }
        if (!temp) {
            return 0;  // Mot non trouvé
        }
        currentState = temp->targetNode;
#endif
        ++w;
    }
    return trie->finite[currentState];  // Retourner si l'état final est terminal
}

void insertPrefixInTrie(Trie trie, unsigned char *w) {
    size_t len = strlen((const char *)w);
    for (size_t i = 0; i < len; ++i) {
        insertInTrie(trie, w + i);  // Insertion de chaque préfixe
    }
}

void insertSuffixInTrie(Trie trie, unsigned char *w) {
    size_t len = strlen((const char *)w);
    for (size_t i = 0; i < len; ++i) {
        insertInTrie(trie, w + i);  // Insertion de chaque suffixe
    }
}

void insertFactInTrie(Trie trie, unsigned char *w) {
    insertSuffixInTrie(trie, w);
    size_t len = strlen((const char *)w);
    for (size_t i = 0; i < len; ++i) {
        insertPrefixInTrie(trie, w + i);  // Insertion de chaque facteur
    }
}
