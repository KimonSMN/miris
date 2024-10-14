#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <unistd.h> 

int main(int argc, char *argv[])
{

    Graph graph = create_graph(12);

    int option;
    while((option = getopt(argc , argv, ":i:o")) != -1){
        switch (option)
        {
        case 'i':
            char accountNameFrom[50];
            char accountNameTo[50];
            int amount;
            char date[11];

            FILE *pF = fopen(optarg, "r");
            if (pF == NULL) {
                perror("Error opening input file");
                exit(EXIT_FAILURE);
            }
            // Read transactions from the file and add edges
            while (fscanf(pF, "%49s %49s %d %10s", accountNameFrom, accountNameTo, &amount, date) == 4) {
                add_edge(graph, accountNameFrom, accountNameTo, amount, date);
            }
            fclose(pF);
            break;
        case 'o':
            break;
        case '?':
            exit(-1);
        }
    }

    
    print_graph(graph);

    destroy_graph(graph);
}