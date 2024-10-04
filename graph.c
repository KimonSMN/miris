#include <stdio.h>
#include "graph.h"
#include <stdbool.h>
#include <stdlib.h>

struct graph{
    int numNodes;
    bool **edges;
};


Graph create_graph(int numNodes){
    Graph graph = malloc(sizeof(graph)); 
    if (graph == NULL){
        return NULL;
    }
    graph->numNodes = numNodes;

    //allocate our matrix

    graph->edges = calloc(sizeof(bool*), graph->numNodes);
    if (graph->edges == NULL){
        free(graph);
        return NULL;
    }

    for(int i=0; i < graph->numNodes; i++){
        graph->edges[i] = calloc(sizeof(bool), graph->numNodes);
        if(graph->edges[i] == NULL){
            destroy_graph(graph);
            return NULL;
        }
    }
    return graph;
}

void destroy_graph(Graph graph){
    if(graph->edges == NULL){
        return;
    }

    for(int i =0; i < graph->numNodes; i++){
        if(graph->edges[i] != NULL){
            free(graph->edges[i]);
        }
    }
    free(graph->edges);
}

void print_graph(Graph graph){
    printf("digraph{\n}");
    for(int from=0; from < graph->numNodes; from++){
        for(int to=0; to < graph->numNodes; to++){
            if(graph->edges[from][to]){
                printf("%d -> %d", from, to);
            }
        }
    }
    printf("}\n");
}

bool add_edge(Graph graph, int from_node, int to_node){
    
}

bool remove_edge(Graph graph, int from_node, int to_node){

}