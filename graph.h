#define GRAPH_H
#include <stdbool.h>

typedef struct graph *Graph;

Graph create_graph(int numNodes);

void destroy_graph(Graph graph);

void print_graph(Graph graph);

bool add_edge(Graph graph, int from_node, int to_node);

bool remove_edge(Graph graph, int from_node, int to_node);