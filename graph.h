#define GRAPH_H
#include <stdbool.h>

typedef struct graph *Graph;

typedef struct node *Node;

Graph create_graph(int numNodes);

void destroy_graph(Graph graph);

Node create_node(int node, int weight, char *date);

void add_edge(Graph graph, int from_node, int to_node, int weight, char *date);

void print_graph(Graph graph);


// bool remove_edge(Graph graph, int from_node, int to_node);