#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "graph.h"

extern size_t bytes;

void *my_malloc(size_t size){
    void *pointer = malloc(size);
    if (pointer != NULL){
        bytes += size;
    }
    return pointer;
}

Graph create_graph(int capacity) {
    // Δέσμευση μνήμης του γράφου.
    Graph graph = my_malloc(sizeof(struct graph));
    if (graph == NULL) 
        return NULL;

    graph->nodes = NULL;
    graph->htable = create_hash_table(capacity); // Δημιουργία του hash-table με μεγεθος capacity.
    return graph;
}


void destroy_graph(Graph graph) {
    if (graph == NULL) {    // Έλεχγει αν ο γράφος ειναι κενός.
        return;
    }
    struct node *current_node = graph->nodes;       // Αρχικοποιεί το current_node ως τον πρωτο κόμβο του γράφου. 
    while (current_node != NULL) {                  // Μεχρι το τέλος του γράφου.
        struct node *temp_node = current_node;      // Temporary αποθήκευση του current_node στον temp_node. 

        struct edge *current_edge = temp_node->edges; 
        while (current_edge != NULL) {              // Μέχρι το τέλος των συναλλαγών.
            struct edge *temp_edge = current_edge;  // Temporary αποθήκευση του current_edge στον temp_edge. 
            current_edge = current_edge->next;      // Επόμενη ακμή στην λίστα.
            free(temp_edge->date);          // Ελευθερωση της ημερομηνιας που ειναι δεσμευμενη δυναμικα. 
            free(temp_edge);                // Ελευθερωση του edge (συναλλαγη).
        }

        free(temp_node->accountName);       // Ελευθέρωση του accountName που ειναι δεσμευμενο δυναμικα.
        free(temp_node);                    // Ελευθέρωση του κομβου.
        current_node = current_node->next;  // Επόμενος κόμβος στην λίστα.

    }
    free(graph);        // Ελευθέρωση μνήμης του γραφου.
}

struct node *create_node(char *accountName) {
    struct node *new_node = my_malloc(sizeof(struct node)); // Δέσμευση μνήμης για τον κόμβο node.
    if (new_node == NULL) {         // Ελέγχει αν ο κόμβος είναι κενός.
        return NULL;
    }
    new_node->accountName = strdup(accountName);    // Δεσμευει μνημη και αντιγραφει το accountName.
    new_node->edges = NULL;
    new_node->next = NULL;
    return new_node;
}

struct node *find_node(Graph graph, char *accountName) {
    struct node *current_node = graph->nodes;
    while (current_node != NULL) {
        if (strcmp(current_node->accountName, accountName) == 0) {      // strcmp επιστρεφει 0 οταν και τα δυο string ειναι ιδια.
            return current_node;    // Βρέθηκε ο κόμβος και τον επιστρέφει.
        }
        current_node = current_node->next;  // Επόμενος κόμβος στην λίστα.
    }
    return NULL;    // Δεν βρέθηκε ο κόμβος, επιστρέφει NULL
}

void add_node(Graph graph, char *accountName) {
    if (find_node(graph, accountName) != NULL) {      // Ελέγχει αν υπάρχει ήδη ο κόμβος μεσα στον γράφο.
        return;                                       
    }
    struct node *new_node = create_node(accountName); // Δημιουργεί κόμβο με όνομα accountName.
    new_node->next = graph->nodes;                    // Ο next pointer του καινουριου κομβου δειχνει στην αρχη της λιστας nodes του γραφου.
    graph->nodes = new_node;                          // Ο καινουριος κομβος γινετε ο πρωτος κομβος του graph->nodes.

    insert_hash_table(graph->htable, accountName, new_node->edges); // Προσθετει στο hashtable τον καινουριο κομβο.
}

void delete_node(Graph graph, char* accountName){

    struct node *node_to_delete = find_node(graph, accountName);
    if (node_to_delete == NULL){
        return;
    }

    // εξερχόμενες ακμες
    struct edge *current_edge = node_to_delete->edges;  // Αρχικοποιεί την current_edge ως την πρώτη ακμή της λίστας.
    while(current_edge != NULL){
        struct edge *temp = current_edge;       // Temporary αποθήκευση του current_edge στον temp_edge. 
        free(temp->date);
        free(temp);
        current_edge = current_edge->next;      // Επόμενη ακμή στην λίστα.
    }
    
    // εισερχόμενες ακμές
    struct node *current_node = graph->nodes;   // Αρχικοποιεί το current_node ως τον πρωτο κόμβο του γράφου.
    while(current_node != NULL){
        struct edge *prev_edge = NULL;                      // Δεν υπάρχει προηγούμενη ακμή ακομα, 
        struct edge *current_edge = current_node->edges;    // εφόσον ξεκινάει απο την αρχή της λίστας.
        
        while(current_edge != NULL){
            if(current_edge->to_node == node_to_delete){
                if (prev_edge != NULL) {                    // Αν δεν είναι η πρώτη ακμή στη λίστα,
                    prev_edge->next = current_edge->next;   // συνδέεται η προηγούμενη ακμή με την επόμενη ακμή.
                } else {
                    current_node->edges = current_edge->next;
                }

                free(current_edge->date);
                struct edge *temp = current_edge;
                free(temp);
                current_edge = current_edge->next;

            } else{
                prev_edge = current_edge;
                current_edge = current_edge->next;
            }
        }
        current_node = current_node->next;
    }

    struct node *prev_node = NULL;
    current_node = graph->nodes;
    while (current_node != NULL) {
        if (current_node == node_to_delete) {
            if (prev_node != NULL) {
                prev_node->next = current_node->next;
            } else {
                graph->nodes = current_node->next;
            }
            break;
        }
        prev_node = current_node;
        current_node = current_node->next;
    }

    remove_from_hash_table(graph->htable, accountName);

    free(node_to_delete->accountName);
    free(node_to_delete);
}

void add_edge(Graph graph, char *from_account, char *to_account, int amount, char *date) {

    // Δημιουργεί τον εισερχόμενο/εξερχόμενο κόμβο, αν δεν υπάρχουν.
    add_node(graph, from_account);  
    add_node(graph, to_account);

    struct node *from_node = find_node(graph, from_account);
    struct node *to_node = find_node(graph, to_account);

    struct edge *new_edge = my_malloc(sizeof(struct edge));    // Δέσμευση μνήμης για την καινούρια ακμή.
    if (new_edge == NULL) {         // Ελέγχει αν η ακμή είναι κενή.
        return;
    }
    new_edge->to_node = to_node;
    new_edge->amount = amount;
    new_edge->date = strdup(date);  // Δεσμευει μνημη και αντιγραφει το date
    new_edge->next = from_node->edges;
    from_node->edges = new_edge;

    insert_hash_table(graph->htable, from_account, from_node->edges); // Πρόσθεση εισερχόμενου λογαριασμού και την συναλλαγη του στο hash table.
}

void print_graph(Graph graph) {
    printf("\t//////// Graph ////////\t\n");
    struct node *current_node = graph->nodes; // Αρχικοποιεί το current_node ως τον πρωτο κόμβο του γράφου.
    while (current_node != NULL) {            // Μέχρι το τέλος του γράφου.
        printf("\nAccount %s:\n", current_node->accountName);
        struct edge *current_edge = current_node->edges; // Αρχικοποιεί την current_edge ως την πρωτη ακμή της λίστας.
        while (current_edge != NULL) {        // Μέχρι το τέλος της λίστας.
            printf("  -> To account: %s (Amount: %d, Date: %s)\n",current_edge->to_node->accountName, current_edge->amount, current_edge->date);
            current_edge = current_edge->next;
        }
        current_node = current_node->next;
    }
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
    if(strcmp(Ni, "") == 0|| strcmp(Nj,"") == 0){
        printf("IssueWith: %s %s", Ni, Nj);
        return;
    }
    add_edge(graph, Ni, Nj, amount, date);
    printf("Inserted edge from %s to %s, amount: %d, date: %s\n", Ni, Nj, amount, date);
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

void delete(Graph graph, char *args){
    char *token = strtok(args, " ");
    while (token != NULL){
        if(search_hash_table(graph->htable, token) == NULL){
            printf("Non-existing node: %s", token);
            return;
        }
        delete_node(graph, token);
        token = strtok(NULL, " ");
    }
}

// void delete2(Graph graph, char *args){
    
// }

void modify(Graph graph, char *args) {
    char Ni[50], Nj[50], date[11], date1[11];
    int sum, sum1;

    sscanf(args, "%s %s %d %d %s %s", Ni, Nj, &sum, &sum1, date, date1); 

    struct node *current_node = find_node(graph, Ni);
    if (current_node == NULL) {
        printf("Non-existing node: %s\n", Ni);
        return;
    }

    struct edge *current_edge = current_node->edges;
    while (current_edge != NULL) {
        if (strcmp(current_edge->to_node->accountName, Nj) == 0 && current_edge->amount == sum && strcmp(current_edge->date, date) == 0) {

            current_edge->amount = sum1;
            free(current_edge->date);
            current_edge->date = strdup(date1);
            return;  // if succesful return
        }
        current_edge = current_edge->next;
    }

    printf("Non-existing edge: %s %s %d %s\n", Ni, Nj, sum, date); // error indication
}


// void receiving(Graph graph, char *args){
    
// }

// void circle_find(Graph graph, char *args){

// }

// void find_circles(Graph graph, char *args){
    
// }

// void trace_flow(Graph graph, char *args){
    
// }

// void connected(Graph graph, char *args){
// 
// }