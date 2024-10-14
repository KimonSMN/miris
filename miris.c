// miris.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include "graph.h"
#include "hashtable.h"

int main(int argc, char *argv[])
{
    Graph graph = create_graph(9);

    int option;
    while ((option = getopt(argc, argv, ":i:o:")) != -1) {
        switch (option) {
        case 'i': {
            char accountNameFrom[50];
            char accountNameTo[50];
            int amount;
            char date[11];
            
            FILE *pF = fopen(optarg, "r");
            if (pF == NULL) {
                printf("Error opening file\n");
                exit(-1);
            }
            while (fscanf(pF, "%49s %49s %d %10s", accountNameFrom, accountNameTo, &amount, date) != EOF) {
                add_edge(graph, accountNameFrom, accountNameTo, amount, date);
            }
            fclose(pF);
            break;
        }
        case 'o':
            printf("Output File: %s\n", optarg);
            break;
        case '?':
            printf("ERROR: Unknown option\n");
            exit(-1);
        }
    }

    // Print the graph
    print_graph(graph);

    // Print the hash table to see its contents
    print_hash_table(graph->accounts_table);

    destroy_graph(graph);
    return 0;
}
