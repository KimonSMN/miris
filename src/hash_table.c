#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

extern size_t bytes;

// Hash function
unsigned long hash(struct hash_table *htable, char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash % htable->capacity;
}

struct hash_table *create_hash_table(int capacity) {
    struct hash_table *htable = my_malloc(sizeof(struct hash_table));
    htable->capacity = capacity;
    htable->array = my_malloc(htable->capacity * sizeof(struct hash_node *));
    for (int i = 0; i < htable->capacity; i++) {
        htable->array[i] = NULL;
    }
    return htable;
}

bool insert_hash_table(struct hash_table *htable, char *key, struct edge *transaction) {
    if (key == NULL) {
        return false;
    }

    unsigned long index = hash(htable, key);

    struct hash_node *node = htable->array[index];
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            transaction->next = node->value;
            node->value = transaction;
            return true;
        }
        node = node->next;
    }

    struct hash_node *new_node = my_malloc(sizeof(struct hash_node));
    if (new_node == NULL) {
        return false;
    }
    new_node->key = strdup(key);
    new_node->value = transaction;
    new_node->next = htable->array[index];
    htable->array[index] = new_node;

    return true;
}


struct hash_node *search_hash_table(struct hash_table *htable, char *key){
    unsigned long index = hash(htable, key);

    struct hash_node *node_to_search = htable->array[index];
    while (node_to_search != NULL){
        if(strcmp(node_to_search->key, key) == 0){
            return node_to_search;
        }
        node_to_search = node_to_search->next;
    }
    return NULL;
}

void print_hash_table(struct hash_table *htable) {
    for (int i = 0; i < htable->capacity; i++) {    // Απο την αρχη του ht εως το μεγεθος του. 
        struct hash_node *node = htable->array[i];  
        if (node == NULL) {         // Εαν το node ειναι κενο (NULL), επεστρεψε.
            continue;
        }
        printf("Bucket %d:\n", i);
        while (node != NULL) {      // Για οσο το node δεν ειναι κενο. 
            printf("Account: %s\n", node->key);
            while (node->value != NULL) {
                printf("  -> To account: %s, Amount: %d, Date: %s\n", node->value->to_node->accountName, node->value->amount, node->value->date);
                node->value = node->value->next;
            }
            node = node->next;
        }
    }
}


void destroy_hash_table(struct hash_table *htable){
    if(htable == NULL){ // Αμα το hash-table ειναι NULL (κενο)
        return;         // επεστρεψε.
    }
    
    for (int i = 0; i < htable->capacity; i++) {    // Απο την αρχη του hash-table εως το μεγεθος του.
    struct hash_node *current_node = htable->array[i];

        while (current_node != NULL) {              // Για οσο υπαρχει node στο bucket.
            struct hash_node *temp_node = current_node; // Δημιουργει εναν temporary node ισο με τον current_node.
            current_node = current_node->next;      // Ο current_node γινετε ο επομενος του (για να συνεχισει το iteration).

            free(temp_node->key);           // Ελευθερωση του key (ονομα λογαριασμου) που ειναι δεσμευμενο δυναμικα.
            free(temp_node);                // Ελευθερωση του κομβου.
        }
    }
    free(htable->array);        // Ελευθερωση του array του hash-table.
    free(htable);               // Ελευθρεωση του hash-table.
}


void remove_from_hash_table(struct hash_table *htable, char *accountName){
    if (accountName == NULL){
        return;
    }

    unsigned long index = hash(htable, accountName);

    struct hash_node *current_node = htable->array[index];
    struct hash_node *prev_node = NULL;

    while (current_node != NULL) {
        if (strcmp(current_node->key, accountName) == 0) {
            if (prev_node == NULL) {

                htable->array[index] = current_node->next;
            } else {

                prev_node->next = current_node->next;
            }

            free(current_node->key);
            free(current_node);

            return;
        }

        prev_node = current_node;
        current_node = current_node->next;
    }

}
