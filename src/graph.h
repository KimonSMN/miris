#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct graph *Graph;

struct graph {      // Γράφος
    struct node *nodes;         // Συνδεδεμένη λίστα με κόμβους.
    struct hash_table *htable;  // Hash-table με κόβους.
};

struct node {       // Κόμβος στον γράφο.
    char *accountName;  // Όνομα τραπεζικού λογαριασμού.
    struct edge *edges; // Συνδεδεμένη λίστα ακμών.
    struct node *next;  // Pointer στον επόμενο κόμβο.
};

struct edge {       // Ακμή στον γράφο.
    struct node *to_node;   // Pointer στον κόμβο προορισμού.
    int amount;             // Ποσό συναλλαγής.
    char *date;             // Ημερομηνία συναλλαγής.
    struct edge *next;      // Pointer στην επόμενη ακμή.
};

struct hash_node {  // Κόμβος του hash-table
    char *key;              // Κλειδί (accountName) του hash-table.
    struct edge *value;     // Pointer στην λίστα ακμών του key (accountName).
    struct hash_node *next; // Pointer στον επόμενο hash_node στο ίδιο bucket. 

};
struct hash_table { // Hash-table
    struct hash_node **array; // Πίνακας απο pointers σε hash_nodes.
    int capacity;             // Αριθμός των buckets (μέγεθος του hash-table).
};

// Βοηθητική malloc για την παρακολούθηση των byte που δεσμεύονται από το πρόγραμμα.
void *my_malloc(size_t size);


//////////////// Λειτουργίες του Γράφου ////////////////


// Δημιουργεί έναν γράφο με μεγεθος capacity.
Graph create_graph(int capacity);

// Ελευθερώνει όλη τη μνήμη που δεσμεύει ο γράφος καθως και οι κόμβοι του.
void destroy_graph(Graph graph);

// Δημιουργεί ενα καινούριο κόμβο node με όνομα accountName.
struct node *create_node(char *accountName);

// Βρίσκει και επιστρέφει τον κόμβο node με όνομα accountName.
// Αν δεν βρεθεί επιστρέφει NULL.
struct node *find_node(Graph graph, char *accountName);

// Προσθέτει εναν νέο κόμβο στον γράφο, με όνομα accountName.
void add_node(Graph graph, char *accountName);

// Διαγράφει έναν κόμβο και όλες τις ακμές του από τον γράφο.
void delete_node(Graph graph, char* accountName);

// Προσθέτει μια ακμή από τον κόμβο from_account στον κόμβο to_account,
// με το ποσό amount και την ημερομηνία date.
void add_edge(Graph graph, char *from_account, char *to_account, int amount, char *date);

// Εκτυπώνει τον γράφο στην παρούσα κατάσταση του. 
void print_graph(Graph graph);


//////////////// Λειτουργίες του Hash-table ////////////////


// Δημιουργεί ενα hash-table με μέγεθος capacity.
struct hash_table *create_hash_table(int capacity);

// Εισάγει μια νέα ακμή transaction στο hash-table για το συγκεκριμένο account (key).
// Αν το account υπάρχει ήδη, η συναλλαγή προστίθεται στην αρχή της λίστας συναλλαγών.
// Σε περίπτωση collision, το νέο account προστίθεται με separate chaining.
bool insert_hash_table(struct hash_table *htable, char *key, struct edge *transaction);

// Ψάχνει το accountName στο hash-table και επιστρέφει το αντίστοιχο hash node.
// Αν δεν βρεθεί, επιστρέφει NULL.
struct hash_node *search_hash_table(struct hash_table *htable, char *key);

// Αφαιρεί απο το hash-table το hash_node με accountName.
// Ελευθερώνει την μηνήμη του.
void remove_from_hash_table(struct hash_table *htable, char *accountName);

// Εκτυπώνει το hash-table στην παρούσα κατάσταση του. 
void print_hash_table(struct hash_table *htable);

// Ελευθερώνει όλη τη μνήμη που δεσμεύει το hash-table.
void destroy_hash_table(struct hash_table *htable);

// Γνωστή hash function (djb2)
unsigned long hash(struct hash_table *htable, char *str);


//////////////// Command line functions ////////////////


void insert_node(Graph graph, char *args);

void insert_edge(Graph graph, char *args);

void find(Graph graph, char *args);

void delete(Graph graph, char *args); // works but then Ι get seg fault when Ι exit

void modify(Graph graph, char *args);

#endif


