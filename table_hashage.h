#ifndef TABLE_HASHAGE_H
#define TABLE_HASHAGE_H

typedef struct _list {
    int startNode;
    int targetNode;
    unsigned char letter;
    struct _list *next;
} *List; // Définir List comme un pointeur vers struct _list

// Déclaration anticipée de Trie
typedef struct _trie *Trie;

int fonctionDeHashage(unsigned char c, int maxNode);
void updateState(Trie trie, int currentState, unsigned char letter);

#endif // TABLE_HASHAGE_H
