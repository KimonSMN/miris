// graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct graph *Graph;

struct graph {
    struct node *nodes; // Linked list of nodes
    struct hash_table *htable;
};

struct node {
    char *accountName;
    struct edge *edges;
    struct node *next;
};

struct edge {
    struct node *to_node;
    int amount;
    char *date;
    struct edge *next;
};

struct hash_node {
    char *key;
    struct edge *value; // pointer to the list of edges (transactions) for the key (accountName)
    struct hash_node *next; // to handle collisions with chaining

};
struct hash_table {
    struct hash_node **array; // array of pointers to hash_nodes
    int capacity;
};

//// Graph functions ////////////////

// Δημιουργει εναν γραφο graph.
Graph create_graph(int capacity);

// Ελευθερώνει όλη τη μνήμη που δεσμεύει ο graph.
void destroy_graph(Graph graph);

// Δημιουργει ενα καινουριο κομβο node με ονομα accountName.
// Επιστρεφει αυτον τον κομβο.
struct node *create_node(char *accountName);

// Βρισκει και επιστρεφει τον κομβο node με ονομα == accountName.
// Αν δεν βρεθει επιστρεφει NULL.
struct node *find_node(Graph graph, char *accountName);

// Προσθετει στον γραφο, τον κομβο με ονομα accountName.
void add_node(Graph graph, char *accountName);

void delete_node(Graph graph, char* accountName);

// function to add an edge to the graph
void add_edge(Graph graph, char *from_account, char *to_account, int amount, char *date);

// function to print the graph
void print_graph(Graph graph);

//// Hash functions ////////////////

// Δημιουργει ενα hashtable με μεγεθος capacity
struct hash_table *create_hash_table(int capacity);

bool insert_hash_table(struct hash_table *htable, char *key, struct edge *transaction);

struct hash_node *search_hash_table(struct hash_table *htable, char *key);

void remove_from_hash_table(struct hash_table *htable, char *accountName);

void print_hash_table(struct hash_table *htable);

void destroy_hash_table(struct hash_table *htable);

unsigned long hash(struct hash_table *htable, char *str);

//// Command line functions ////////////////

void insert_node(Graph graph, char *args);

void insert_edge(Graph graph, char *args);

void find(Graph graph, char *args);

void delete(Graph graph, char *args); // works but then i get seg fault when i exit

void modify(Graph graph, char *args);

#endif // GRAPH_H


