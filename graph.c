#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "graph.h"

extern size_t bytes;

static void *my_malloc(size_t size){
    void *pointer = malloc(size);
    if (pointer != NULL){
        bytes += size;
    }
    return pointer;
}


Graph create_graph(int capacity) {
    
    // Memory allocation for graph.
    Graph graph = my_malloc(sizeof(struct graph));
    if (graph == NULL) {
        return NULL;        // Something went wrong, return NULL.
    }
    graph->nodes = NULL;
    graph->htable = create_hash_table(capacity);
    return graph;
}

void destroy_graph(Graph graph) {
    if (graph == NULL) {
        return;     // Something went wrong, return.
    }
    struct node *current_node = graph->nodes;   
    while (current_node != NULL) {              
        struct node *temp_node = current_node;  
        current_node = current_node->next;      

        struct edge *current_edge = temp_node->edges; 
        while (current_edge != NULL) {              // Για οσο υπαρχουν συναλλαγες.
            struct edge *temp_edge = current_edge;  // Δημιουργει ενα temporary edge ισο με το current_edge.
            current_edge = current_edge->next;      // Το current_edge γινετε το επομενο του (για να συνεχισει το iteration).
            free(temp_edge->date);          // Ελευθερωση της ημερομηνιας που ειναι δεσμευμενη δυναμικα. 
            free(temp_edge);                // Ελευθερωση του edge (συναλλαγη).
        }

        free(temp_node->accountName);       // Ελευθερωση του accountName που ειναι δεσμευμενο δυναμικα.
        free(temp_node);                    // Ελευθερωση του κομβου.
    }
    free(graph);        // Ελευθερωση του γραφου.
}

struct node *create_node(char *accountName) {
    struct node *new_node = my_malloc(sizeof(struct node)); // Δεσμευση μνημης για τον κομβο node.
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

    struct edge *new_edge = my_malloc(sizeof(struct edge));    // Δεσμευει χωρο για το καινουριο edge.
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
    struct hash_table *htable = my_malloc(sizeof(struct hash_table));
    htable->capacity = capacity;
    htable->array = my_malloc(htable->capacity * sizeof(struct hash_node *));
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

    struct hash_node *new_node = my_malloc(sizeof(struct hash_node));
    if (new_node == NULL) {
        return false;
    }
    new_node->key = strdup(key);
    new_node->value = transaction;
    new_node->next = htable->array[index];
    htable->array[index] = new_node;

    return true;
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
    for (int i = 0; i < htable->capacity; i++) {    // Απο την αρχη του ht εως το μεγεθος του. 
        struct hash_node *node = htable->array[i];  
        if (node == NULL) {         // Εαν το node ειναι κενο (NULL), επεστρεψε.
            continue;
        }
        printf("Bucket %d:\n", i);
        while (node != NULL) {      // Για οσο το node δεν ειναι κενο. 
            printf("Account: %s\n", node->key);
            while (node->value != NULL) {
                printf("  -> To account: %s, Amount: %d, Date: %s\n", node->value->to_node->accountName, node->value->amount, node->value->date);
                node->value = node->value->next;
            }
            node = node->next;
        }
    }
}


void destroy_hash_table(struct hash_table *htable){
    if(htable == NULL){ // Αμα το hash-table ειναι NULL (κενο)
        return;         // επεστρεψε.
    }
    
    for (int i = 0; i < htable->capacity; i++) {    // Απο την αρχη του hash-table εως το μεγεθος του.
    struct hash_node *current_node = htable->array[i];

        while (current_node != NULL) {              // Για οσο υπαρχει node στο bucket.
            struct hash_node *temp_node = current_node; // Δημιουργει εναν temporary node ισο με τον current_node.
            current_node = current_node->next;      // Ο current_node γινετε ο επομενος του (για να συνεχισει το iteration).

            free(temp_node->key);           // Ελευθερωση του key (ονομα λογαριασμου) που ειναι δεσμευμενο δυναμικα.
            free(temp_node);                // Ελευθερωση του κομβου.
        }
    }
    free(htable->array);        // Ελευθερωση του array του hash-table.
    free(htable);               // Ελευθρεωση του hash-table.
}

void insert_node(Graph graph, char *args){
    char *token = strtok(args, " ");
    while (token != NULL){
        add_node(graph, token);
        printf("Succ: %s\n", token);
        token = strtok(NULL, " ");
    }

    // ADD ERROR INDICATION

}

void insert_edge(Graph graph, char *args){
    char Ni[50];
    char Nj[50];
    char date[11];
    int amount;
    sscanf(args, "%s %s %d %s", Ni, Nj, &amount, date); 
    add_edge(graph, Ni, Nj, amount, date);
    printf("Inserted edge from %s to %s, amount: %d, date: %s\n", Ni, Nj, amount, date);
    // ADD ERROR INDICATION

}


void find(Graph graph, char *args){
    char Ni[50];
    sscanf(args, "%s", Ni);

    struct hash_node *node = search_hash_table(graph->htable, Ni);
    if (node == NULL) {
        printf("Non-existing node: %s", Ni);
        return;
    }

    struct edge *current_edge = node->value;
    if (current_edge == NULL) {
        printf("(none)\n");
        return;
    }
    while(current_edge != NULL){
        printf("%s %s %d %s\n", node->key, current_edge->to_node->accountName, current_edge->amount, current_edge->date);
        current_edge = current_edge->next;
    }
}
