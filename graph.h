#ifndef GRAPH_H
#define GRAPH_H

#include "hashtable.h"

typedef struct node *Node;
typedef struct graph *Graph;

struct node {
    char *accountName;
    int amount;
    char *date;
    Node next;
};

struct graph {
    int numNodes;
    Node *adj_list;
    HashTable accounts_table;
};

// Function declarations
Graph create_graph(int numNodes);

void destroy_graph(Graph graph);

Node create_node(char *accountName, int amount, char *date);

void add_edge(Graph graph, char *from_account, char *to_account, int amount, char *date);

void print_graph(Graph graph);

#endif
