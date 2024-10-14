#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

unsigned long hash(char *str) {

        unsigned long hash = 5381;
        int c;
        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        return hash % 100; // 100 == num buckets, change it afterwards

}
HashTable create_hash_table(int size){
    HashTable htable = malloc(sizeof(struct hash_table));
    htable->size = size;
    htable->array = calloc(htable->size, sizeof(struct hash_node*));
    return htable;
}

void destroy_hash_table(HashTable htable) {
    for (int i = 0; i < htable->size; i++) {
        HashNode current = htable->array[i];
        while (current != NULL) {
            HashNode temp = current;
            current = current->next;
            free(temp->key);
            free(temp->value); // Free the value if necessary
            free(temp);
        }
    }
    free(htable->array);
    free(htable);
}


bool insert_hash_table(HashTable htable, char *key, void *value) {
    unsigned long i = hash(key) % htable->size;

    HashNode current = htable->array[i];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value; // Update the value
            return true;
        }
        current = current->next;
    }

    // If not found, insert new node
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
                // For accounts_table, value is an int*
                int *amount_ptr = (int *)current->value;
                printf("[AccountName: %s, Amount: %d] -> ", current->key, *amount_ptr);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
}


