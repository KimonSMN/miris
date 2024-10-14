#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

Graph create_graph(int numNodes){
    Graph graph = malloc(sizeof(struct graph)); 
    if (graph == NULL){
        return NULL;
    }

    graph->numNodes = numNodes;
    graph->adj_list = calloc(numNodes, sizeof(Node));
    if (graph->adj_list == NULL){
        free(graph);
        return NULL;
    }

    graph->accounts_table = create_hash_table(100);
    if (graph->accounts_table == NULL){
        free(graph->adj_list);
        free(graph);
        return NULL;
    }

    return graph;
}

void destroy_graph(Graph graph){
    if(graph == NULL){  
        return;
    }

    for(int i = 0; i < graph->numNodes; i++){
        Node current_node = graph->adj_list[i];
        while (current_node != NULL){
            Node temp = current_node;
            current_node = current_node->next;
            free(temp->date);
            free(temp);
        }
    }
    free(graph->adj_list);
    destroy_hash_table(graph->accounts_table);
    free(graph);
}

Node create_node(char *accountName, int amount, char *date){
    Node new_node = malloc(sizeof(struct node));
    new_node->accountName = strdup(accountName);
    new_node->amount = amount;
    new_node->next = NULL;
    new_node->date = strdup(date);
    return new_node;
}

void add_edge(Graph graph, char *from_account, char *to_account, int amount, char *date){
    Node new_node = create_node(to_account, amount, date);
    unsigned long from_index = hash(from_account) % graph->numNodes;
    new_node->next = graph->adj_list[from_index];
    graph->adj_list[from_index] = new_node;

    insert_hash_table(graph->accounts_table, to_account, amount);
}

void print_graph(Graph graph){
    for(int i = 0; i < graph->numNodes; i++){
        Node current_node = graph->adj_list[i];
        if(current_node == NULL) continue;
        printf("Adjacency list of vertex %d: ", i);
        while(current_node != NULL){
            printf("(%s, %d, %s) -> ", current_node->accountName, current_node->amount, current_node->date);
            current_node = current_node->next;
        }
        printf("NULL\n");
    }
}
