#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "graph.h"

typedef struct hashtable *Hashtable;

Hashtable create_hashtable(int size); // Function to create a hashtable

void destroy_hashtable(Hashtable table); // Function to free hashtable

void insert_hashtable(Hashtable table, Node new_node);

Hashtable search_hashtable(Hashtable table, Node new_node);

int hash(int accountName, int size); // hash function

void destroy_hashtable(Hashtable table);

#endif 
