#include "graph.h"
#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct graph{
    int numNodes;
    Node *adj_list;
    Hashtable accounts_table;
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

    // graph->accounts_table = create_hashtable(100);
    // if (graph->accounts_table == NULL){
    //     free(graph);
    //     return NULL;
    // }

    return graph;
}

void destroy_graph(Graph graph){
    if(graph->numNodes == -1){ // == -1 and not NULL  
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

Node create_node(int accountName, int amount, char *date){
    Node new_node = malloc(sizeof(new_node));
    new_node->accountName = accountName;
    new_node->amount = amount;
    new_node->next = NULL;
    new_node->date = strdup(date);
    return new_node;
}


void add_edge(Graph graph, int from_node, int to_node, int amount, char *date){
    Node new_node = create_node(to_node, amount, date);
    new_node->next = graph->adj_list[from_node];
    graph->adj_list[from_node] = new_node;

    // insert_hashtable(graph->accounts_table, new_node);
}

void print_graph(Graph graph){
    for(int i = 0; i< graph->numNodes; i++){
        Node current_node = graph->adj_list[i];
        if(current_node == NULL) continue;
        printf("Adjacency list of vertex %d: ", i);
        while(current_node != NULL){
            printf("(%d, %d, %s) -> ", current_node->accountName, current_node->amount, current_node->date);
            current_node = current_node->next;
        }
        printf("NULL\n");
    }
}

