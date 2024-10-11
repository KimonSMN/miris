#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

#define TABLE_SIZE 100

struct hashtable{
    Node *table; // a table with accounts 
    int size;
};

Hashtable create_hashtable(int size){

    // Allocate memory for the hashtable structure
    Hashtable accounts_table = malloc(sizeof(struct hashtable)); 

    // Allocate memory for the node table (accounts table)
    accounts_table->table = malloc(size * sizeof(Node));

    // set every element of the table to null 
    for (int i = 0; i < size; i++){
        accounts_table->table[i] == NULL;
    }

    accounts_table->size = size;

    return accounts_table;
}

void print_hashtable(Hashtable table) {
    if (table = NULL) {
        printf("Hashtable is NULL.\n");
        return;
    }

    printf("Hashtable contents:\n");

    // Iterate through each index of the hash table
    for (int i = 0; i < table->size; i++) {
        printf("Index %d: ", i);

        Node curr = table->table[i];
        while (curr != NULL){
            printf("(%d, %d, %s) -> ", curr->accountName, curr->amount, curr->date);
            curr = curr->next;
        }
    }
}

int hash(int accountName, int size) {
    return accountName % size;  // Simple modulo-based hash function
}

void insert_hashtable(Hashtable table, Node new_node){
    int index = hash(new_node->accountName, table->size);
    new_node->next = table->table[index];
    table->table[index] = new_node;
}


