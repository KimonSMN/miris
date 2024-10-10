#include <stdio.h>
#include "graph.h"
#include <stdbool.h>
#include <stdlib.h>

struct node {
    int accountName;
    int weight;
    Node next;
};

struct graph{
    int numNodes;
    Node *adj_list;
};


Graph create_graph(int numNodes){
    Graph graph = malloc(sizeof(struct graph)); 
    if (graph == NULL){
        return NULL;
    }

    graph->numNodes = numNodes;


    // Allocate memory for the adjacency list (array of Node pointers)

    graph->adj_list = malloc(numNodes * sizeof(struct node));

    if (graph->adj_list == NULL){
        free(graph);
        return NULL;
    }

    for (int i = 0; i < numNodes; i++){
        graph->adj_list[i] = NULL;
    }
    return graph;

}

void destroy_graph(Graph graph){
    if(graph->numNodes == NULL){
        return;
    }

    for(int i = 0; i < graph->numNodes; i++){
        Node current_node = graph->adj_list[i];
        while (current_node != NULL){
            Node temp = current_node;
            current_node = current_node->next;
            free(temp);
        }
    }
    free(graph->adj_list);
    free(graph);
}

Node create_node(int accountName, int weight){
    Node new_node = malloc(sizeof(new_node));
    new_node->accountName = accountName;
    new_node->weight = weight;
    new_node->next = NULL;
    return new_node;
}


void add_edge(Graph graph, int from_node, int to_node, int weight){
    Node new_node = create_node(to_node, weight);
    new_node->next = graph->adj_list[from_node];
    graph->adj_list[from_node] = new_node;
}

void print_graph(Graph graph){
    for(int i = 0; i< graph->numNodes; i++){
        Node current_node = graph->adj_list[i];
        if(current_node == NULL) continue;
        printf("Adjacency list of vertex %d: ", i);
        while(current_node != NULL){
            printf("(%d, %d) -> ", current_node->accountName, current_node->weight);
            current_node = current_node->next;
        }
        printf("NULL\n");
    }
}


// bool remove_edge(Graph graph, int from_node, int to_node){

// }