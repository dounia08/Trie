// main.c
#include <stdio.h>
#include "trie.h"

int main() {
    // Création d'un trie avec un maximum de 100 noeuds
    Trie trie = createTrie(100);
    unsigned char word1[] = "abcd";
    unsigned char word2[] = "aebc";
    unsigned char word3[] = "cdae";

    // Insertion de mots dans le trie
    insertInTrie(trie, word1);
    insertInTrie(trie, word2);
    insertInTrie(trie, word3);

    // Vérification de la présence des mots dans le trie
    printf("le mot'abcd' est dans le trie ? %s\n", isInTrie(trie, word1) ? "oui" : "Non");
    printf("le mot'aedc' iest dans le trie ? %s\n", isInTrie(trie, word2) ? "oui" : "Non");
    printf("le mot'cdae' est dans le trie ? %s\n", isInTrie(trie, word3) ? "oui" : "Non");
    printf("le mot 'cda' est dans le trie ? %s\n", isInTrie(trie, (unsigned char *)"cda") ? "Yes" : "No");

    // Insertion d'un préfixe dans le trie
    insertPrefixInTrie(trie, (unsigned char *)"cdae");
    printf("Le préfixe 'cda' est-il présent dans le trie après l'insertion des préfixes ? %s\n", isInTrie(trie, (unsigned char *)"cda") ? "oui" : "Non");

    // Libération de la mémoire (si une fonction de destruction est implémentée)
    // freeTrie(trie); // Assurez-vous de définir cette fonction si nécessaire

    return 0;
}
