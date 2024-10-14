#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

Graph create_graph() {
    Graph graph = malloc(sizeof(struct graph));
    if (graph == NULL) {
        return NULL;
    }
    graph->nodes = NULL;
    return graph;
}

void destroy_graph(Graph graph) {
    if (graph == NULL) {
        return;
    }
    Node current_node = graph->nodes;
    while (current_node != NULL) {
        Node temp_node = current_node;
        current_node = current_node->next;

        Edge current_edge = temp_node->edges;
        while (current_edge != NULL) {
            Edge temp_edge = current_edge;
            current_edge = current_edge->next;
            free(temp_edge->date);
            free(temp_edge);
        }

        free(temp_node->accountName);
        free(temp_node);
    }
    free(graph);
}

Node create_node(char *accountName) {
    Node new_node = malloc(sizeof(struct node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->accountName = strdup(accountName);
    new_node->edges = NULL;
    new_node->next = NULL;
    return new_node;
}

Node find_node(Graph graph, char *accountName) {
    Node current_node = graph->nodes;
    while (current_node != NULL) {
        if (strcmp(current_node->accountName, accountName) == 0) {
            return current_node;
        }
        current_node = current_node->next;
    }
    return NULL;
}

void add_node(Graph graph, char *accountName) {
    if (find_node(graph, accountName) != NULL) {
        return;
    }
    Node new_node = create_node(accountName);
    new_node->next = graph->nodes;
    graph->nodes = new_node;
}

void add_edge(Graph graph, char *from_account, char *to_account, int amount, char *date) {
    Node from_node = find_node(graph, from_account);
    if (from_node == NULL) {
        // maybe can use add_node instead but i have to change function from void type
        from_node = create_node(from_account);
        from_node->next = graph->nodes;
        graph->nodes = from_node;
    }
    Node to_node = find_node(graph, to_account);
    if (to_node == NULL) {
        to_node = create_node(to_account);
        to_node->next = graph->nodes;
        graph->nodes = to_node;
    }

    Edge new_edge = malloc(sizeof(struct edge));
    if (new_edge == NULL) {
        return;
    }
    new_edge->to_node = to_node;
    new_edge->amount = amount;
    new_edge->date = strdup(date);
    new_edge->next = from_node->edges;
    from_node->edges = new_edge;
}

void print_graph(Graph graph) {
    Node current_node = graph->nodes;
    while (current_node != NULL) {
        printf("\nAccount %s:", current_node->accountName);
        Edge current_edge = current_node->edges;
        while (current_edge != NULL) {
            printf("  -> %s (Amount: %d, Date: %s)",
                   current_edge->to_node->accountName,
                   current_edge->amount,
                   current_edge->date);
            current_edge = current_edge->next;
        }
        current_node = current_node->next;
    }
}
