#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "graph.h"

Graph create_graph(int size) {
    
    // Δεσμευση μνημης για τον γραφο 
    Graph graph = malloc(sizeof(struct graph));
    if (graph == NULL) {
        return NULL;        // Κατι πηγε στραβα επεστρεψε NULL.
    }
    graph->nodes = NULL;
    graph->htable = create_hash_table(size);
    return graph;
}

void destroy_graph(Graph graph) {
    if (graph == NULL) {
        return;     // Κατι πηγε στραβα επεστρεψε NULL.
    }
    struct node *current_node = graph->nodes;   // Ξεκιναμε απο τον 1ο κομβο του γραφου.
    while (current_node != NULL) {              // Μεχρι να ειναι ο current_node NULL.
        struct node *temp_node = current_node;  // Προσωρινη αποθηκευση του current_node στον temp
        current_node = current_node->next;      // ωστε να εχουμε προσβαση στο ->next 

        struct edge *current_edge = temp_node->edges; // Ιδια λογικη και εδω.
        while (current_edge != NULL) {
            struct edge *temp_edge = current_edge;
            current_edge = current_edge->next;
            free(temp_edge->date);
            free(temp_edge);
        }

        free(temp_node->accountName);
        free(temp_node);
    }
    free(graph->htable->array);
    free(graph->htable);
    free(graph);
}

struct node *create_node(char *accountName) {
    struct node *new_node = malloc(sizeof(struct node)); // Δεσμευση μνημης για τον κομβο node.
    if (new_node == NULL) {
        return NULL;        // Κατι πηγε στραβα επεστρεψε NULL
    }
    new_node->accountName = strdup(accountName); // Δεσμευει μνημη και αντιγραφει το accountName.
    new_node->edges = NULL;
    new_node->next = NULL;
    return new_node;
}

struct node *find_node(Graph graph, char *accountName) {
    struct node *current_node = graph->nodes; // Ξεκιναμε απο τον 1ο κομβο του γραφου.
    while (current_node != NULL) {            // Μεχρι να ειναι ο current_node NULL (τελος).
        if (strcmp(current_node->accountName, accountName) == 0) { // strcmp επιστρεφει 0 οταν και τα δυο string ειναι ιδια.
            return current_node;    // Βρηκε τον κομβο και τον επιστρεφει.
        }
        current_node = current_node->next;  // Points τον επομενο κομβο
    }
    return NULL;    // Στην περιπτωση που δεν βρηκε τον κομβο μεσα στον γραφο επιστρεφει NULL
}

void add_node(Graph graph, char *accountName) {
    if (find_node(graph, accountName) != NULL) {    // Εαν υπαρχει ηδη το κομβος 
        return;                                     // επιστρεφει.
    }
    struct node *new_node = create_node(accountName); // Δημιουργει κομβο με ονομα accountName
    new_node->next = graph->nodes;                    // Ο next του καινουριου κομβου δειχνει στην αρχη της λιστας nodes του γραφου
    graph->nodes = new_node;                          // Ο καινουριος κομβος γινετε ο πρωτος κομβος του graph->nodes

    insert_hash_table(graph->htable, accountName, new_node->edges); // Προσθετει στο hashtable τον καινουριο κομβο.
}

void add_edge(Graph graph, char *from_account, char *to_account, int amount, char *date) {
    struct node *from_node = find_node(graph, from_account);    // Ψαχνει να βρει τον εισερχομενο κομβο.
    // Δεν βρηκε τον from_node στον γραφο.
    // Τον δημιουργει και τον προσθετει στο hash table.
    if (from_node == NULL) { 
        from_node = create_node(from_account);
        from_node->next = graph->nodes;
        graph->nodes = from_node;
        insert_hash_table(graph->htable, from_account, from_node->edges);
    }

    struct node *to_node = find_node(graph, to_account);    // Ψαχνει να βρει τον εξερχομενο κομβο.
    // Δεν βρηκε τον to_node στον γραφο.
    // Τον δημιουργει και τον προσθετει στο hash table.
    if (to_node == NULL) { 
        to_node = create_node(to_account);
        to_node->next = graph->nodes;
        graph->nodes = to_node;
        insert_hash_table(graph->htable, to_account, to_node->edges);
    }

    struct edge *new_edge = malloc(sizeof(struct edge));    // Δεσμευει χωρο για το καινουριο edge.
    if (new_edge == NULL) {
        return;     // Κατι πηγε στραβα επεστρεψε.
    }
    new_edge->to_node = to_node;
    new_edge->amount = amount;
    new_edge->date = strdup(date);  // Δεσμευει μνημη και αντιγραφει το date
    new_edge->next = from_node->edges;
    from_node->edges = new_edge;

    insert_hash_table(graph->htable, from_account, from_node->edges); // Προσθετει τον εισερχομενο λογαριασμο μαζι και την συναλλαγη του στο hash table.
}

void print_graph(Graph graph) {
    struct node *current_node = graph->nodes;
    while (current_node != NULL) {
        printf("\nAccount %s:\n", current_node->accountName);
        struct edge *current_edge = current_node->edges;
        while (current_edge != NULL) {
            printf("  -> To account: %s (Amount: %d, Date: %s)\n",current_edge->to_node->accountName, current_edge->amount, current_edge->date);
            current_edge = current_edge->next;
        }
        current_node = current_node->next;
    }
    printf("\n");
}

// Hash function
unsigned long hash(struct hash_table *htable, char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash % htable->capacity;
}

struct hash_table *create_hash_table(int capacity) {
    struct hash_table *htable = malloc(sizeof(struct hash_table));
    htable->capacity = capacity;
    htable->array = malloc(htable->capacity * sizeof(struct hash_node *));
    for (int i = 0; i < htable->capacity; i++) {
        htable->array[i] = NULL;
    }
    return htable;
}

bool insert_hash_table(struct hash_table *htable, char *key, struct edge *transaction) {
    if (key == NULL) {
        return false;
    }

    unsigned long index = hash(htable, key);

    struct hash_node *node = htable->array[index];
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            transaction->next = node->value;
            node->value = transaction;
            return true;
        }
        node = node->next;
    }

    struct hash_node *new_node = malloc(sizeof(struct hash_node));
    if (new_node == NULL) {
        return false;
    }
    new_node->key = strdup(key);
    new_node->value = transaction;
    new_node->next = htable->array[index];
    htable->array[index] = new_node;

    return true;
}

void print_transactions(struct edge *transaction) {
    while (transaction != NULL) {
        printf("  -> To account: %s, Amount: %d, Date: %s\n",
               transaction->to_node->accountName, transaction->amount, transaction->date);
        transaction = transaction->next;
    }
}

struct hash_node *search_hash_table(struct hash_table *htable, char *key){
    unsigned long index = hash(htable, key);

    struct hash_node *node_to_search = htable->array[index];
    while (node_to_search != NULL){
        if(strcmp(node_to_search->key, key) == 0){
            return node_to_search;
        }
        node_to_search = node_to_search->next;
    }
    return NULL;
}

void print_hash_table(struct hash_table *htable) {
    for (int i = 0; i < htable->capacity; i++) {
        struct hash_node *node = htable->array[i];
        if (node == NULL) {
            continue;
        }
        printf("Bucket %d:\n", i);
        while (node != NULL) {
            printf("Account: %s\n", node->key);
            print_transactions(node->value);
            node = node->next;
        }
    }
}
