#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

unsigned long hash(char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

HashTable create_hash_table(int size){
    HashTable htable = malloc(sizeof(struct hash_table));
    htable->size = size;
    htable->array = calloc(htable->size, sizeof(struct hash_node*));
    return htable;
}

void destroy_hash_table(HashTable htable){
    for (int i = 0; i < htable->size; i++) {
        HashNode current = htable->array[i];
        while (current != NULL) {
            HashNode temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(htable->array);
    free(htable);
}

bool insert_hash_table(HashTable htable, char *key, int value){
    unsigned long i = hash(key) % htable->size;

    HashNode new_hash_node = malloc(sizeof(struct hash_node));
    new_hash_node->key = strdup(key);
    new_hash_node->value = value;
    new_hash_node->next = htable->array[i];
    htable->array[i] = new_hash_node;

    return true;
}

void print_hash_table(HashTable htable) {
    printf("Hash Table Contents:\n");
    for (int i = 0; i < htable->size; i++) {
        HashNode current = htable->array[i];
        if (current == NULL) {
            printf("Bucket %d: Empty\n", i);
        } else {
            printf("Bucket %d: ", i);
            while (current != NULL) {
                printf("[AccountName: %s, Amount: %d] -> ", current->key, current->value);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
}

HashNode search_hash_table(HashTable htable, char *key){
    unsigned long i = hash(key) % htable->size;

    HashNode current = htable->array[i];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
