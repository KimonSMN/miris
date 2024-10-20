#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <unistd.h> 
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[])
{
    Graph graph = NULL;
    FILE *pF1, *pF2;
    int option;
    char *iFile = NULL, *oFile = NULL;

    while((option = getopt(argc , argv, ":i:o:")) != -1){
        switch (option)
        {
        case 'i':
            iFile = optarg;
            break;
        case 'o':
            oFile = optarg;
            break;
        case '?':
            exit(-1);
        }
    }
        

    ////// Read from the input file //////

    if (iFile == NULL) {
        printf("Input file not provided\n");
        return -1;
    }

    char accountNameFrom[50], accountNameTo[50], date[11];
    int amount, line = 0, ch = 0;

    pF1 = fopen(iFile, "r");
    if (pF1 == NULL) {
        printf("error opening file\n");
        exit(-1);
    }

    for (ch = getc(pF1); ch != EOF; ch = getc(pF1))
        if (ch == '\n')
            line = line + 1;

    rewind(pF1);

    graph = create_graph(line);

    // Read transactions from the file and add edges
    while (fscanf(pF1, "%49s %49s %d %10s", accountNameFrom, accountNameTo, &amount, date) == 4) {
        add_edge(graph, accountNameFrom, accountNameTo, amount, date);
    }

    fclose(pF1);    // Close the file
    
    ////// COMMAND LINE //////

    bool active = true;
    char command[64];

    while (active) {
        printf("\n/$ ");

        fgets(command, sizeof(command), stdin);
        
        command[strlen(command)-1] = '\0';

        if (strncmp(command, "i ", 2) == 0) { // Eισήγαγε ένα νέο Ni ή πολλαπλούς νέους κόμβους όπως π.χ. Ni, Nj, Nk.
            insert_node(graph, command + 2);  // Not connected nodes dont show up. Also make sure user can add multiple nodes at once. 
        } else if(strncmp(command, "n ", 2) == 0){  // Eισήγαγε μια ακμή με φορά από Ni προς Nj με ημερομηνία date και ποσό sum.
            insert_edge(graph, command + 2);        // Οι κόμβοι Ni και Nj μπορεί να εμφανίζονται για πρώτη φορά στην δομή.
        } else if(strncmp(command, "f ", 2) == 0) {
            find(graph, command + 2);
        } else if (strcmp(command, "exit") == 0) {
            active = false;
        } else { 
            printf("Command '%s' not found.\n", command);
        }
    }

    print_graph(graph);

    ////// Write to the output file //////

    if (oFile == NULL){
        printf("Output file not provided\n");
        return -1;
    }

    pF2 = fopen(oFile, "w");
    if (pF2 == NULL) {
        return -1;
    }

    struct node *current_node = graph->nodes;
    while (current_node != NULL) {
        struct edge *current_edge = current_node->edges;
        while (current_edge != NULL) {
            fprintf(pF2, "%s %s %d %s\n", current_node->accountName, current_edge->to_node->accountName, current_edge->amount, current_edge->date);
            current_edge = current_edge->next;
        }
        current_node = current_node->next;
    }

    fclose(pF2);    // Close the file

    print_hash_table(graph->htable);
    destroy_hash_table(graph->htable);
    destroy_graph(graph);

    return 0;
}