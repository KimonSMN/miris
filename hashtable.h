#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>

typedef struct hash_table *HashTable;
typedef struct hash_node *HashNode;

struct hash_node {
    char *key;
    int value;
    HashNode next; // separate chaining
};

struct hash_table {
    HashNode *array;
    int size;
};

// Function declarations
HashTable create_hash_table(int size);

void destroy_hash_table(HashTable htable);

bool insert_hash_table(HashTable htable, char *key, int value);

void print_hash_table(HashTable htable);

HashNode search_hash_table(HashTable htable, char *key);

unsigned long hash(char *str);

#endif
