#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <unistd.h> 
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[])
{
    Graph graph = NULL;

    int option;
    while((option = getopt(argc , argv, ":i:o")) != -1){
        switch (option)
        {
        case 'i':
            char accountNameFrom[50];
            char accountNameTo[50];
            int amount;
            char date[11];
            int line;
            int ch = 0;
            FILE *pF = fopen(optarg, "r");
            if (pF == NULL) {
                perror("Error opening input file");
                exit(EXIT_FAILURE);
            }

            for (ch = getc(pF); ch != EOF; ch = getc(pF))
                if (ch == '\n')
                    line = line + 1;

            rewind(pF);

            graph = create_graph(line);
            // Read transactions from the file and add edges
            while (fscanf(pF, "%49s %49s %d %10s", accountNameFrom, accountNameTo, &amount, date) == 4) {
                add_edge(graph, accountNameFrom, accountNameTo, amount, date);
            }

            fclose(pF);
            break;
        case 'o':
            //σημαία -o είναι το αρχείο εξόδου που την στιγμή της εξόδου της εφαρμογής σας καταγράφει,
            // την κατάσταση του γράφου όπως αυτή έχει εξελιχτεί με την περάτωση της εφαρμογής.
            break;
        case '?':
            exit(-1);
        }
    }

    // bool active = true;
    // char command[64];

    // while (active) {
    //     printf("\n/$ ");

    //     fgets(command, sizeof(command), stdin);
        
    //     command[strlen(command)-1] = '\0';

    //     if (strncmp(command, "n ", 2) == 0) {
    //         insert_edge(graph, command + 2);
    //     }
    //     else if (strcmp(command, "exit") == 0) {
    //         active = false;
    //     }
    //     else { 
    //         printf("Command '%s' not found.\n", command);
    //     }
    // }
    // print_graph(graph);
    destroy_hash_table(graph->htable);
    destroy_graph(graph);
    
    return 0;
}