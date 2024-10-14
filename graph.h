// graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct graph *Graph;

typedef struct node *Node;

typedef struct edge *Edge;

struct graph {
    Node nodes; // Linked list of nodes
};

struct node {
    char *accountName;
    Edge edges;
    Node next;
};

struct edge {
    Node to_node;
    int amount;
    char *date;
    Edge next;
};

// function to create a new graph
Graph create_graph();

//function to destroy the graph and free up the memory
void destroy_graph(Graph graph);

// function to create a new node
Node create_node(char *accountName);

// function to find a node
Node find_node(Graph graph, char *accountName);
// function to add a node to the graph
void add_node(Graph graph, char *accountName);

// function to add an edge to the graph
void add_edge(Graph graph, char *from_account, char *to_account, int amount, char *date);

// function to print the graph
void print_graph(Graph graph);

#endif // GRAPH_H


