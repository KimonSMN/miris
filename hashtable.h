#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>

typedef struct hash_table *HashTable;
typedef struct hash_node *HashNode;

struct hash_node {
    char *key;
    void *value;
    HashNode next; // separate chaining
};

struct hash_table {
    HashNode *array;
    int size;
};

// Function declarations
HashTable create_hash_table(int size);

bool insert_hash_table(HashTable htable, char *key, void *value);

void print_hash_table(HashTable htable);

void destroy_hash_table(HashTable htable);

unsigned long hash(char *str);


// add search function
#endif
