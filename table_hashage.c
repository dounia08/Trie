#include <stdlib.h>
#include "table_hashage.h"
#include "trie.h"   
#include <stdio.h>

int fonctionDeHashage(unsigned char c, int maxNode) {
    return c % maxNode;
}

void updateState(Trie trie, int currentState, unsigned char letter) {
#ifdef HACHAGE
    int index = fonctionDeHashage(letter, trie->maxNode);
    List newTransition = (List)malloc(sizeof(struct _list));
    if (newTransition == NULL) {
        fprintf(stderr, "Erreur : échec de l'allocation mémoire pour une nouvelle transition.\n");
        exit(EXIT_FAILURE);
    }

    newTransition->startNode = currentState;
    newTransition->letter = letter;
    newTransition->targetNode = trie->nextNode++;
    newTransition->next = trie->transition[index]; // Type correct pour l'implémentation par liste
    trie->transition[index] = newTransition;       // Type correct pour l'implémentation par liste
#else
    // Rien à faire, ou ajouter un message approprié si MATRICE est défini
    fprintf(stderr, "Erreur : updateState ne doit être utilisé qu'avec l'option HACHAGE.\n");
#endif
}
