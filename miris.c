#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <unistd.h> 

int main(int argc, char *argv[])
{

    Graph graph = create_graph(12); // have to change it to me dynamic

    int option;
    while((option = getopt(argc , argv, ":i:o")) != -1){
        switch (option)
        {
        case 'i':
            int accountNameFrom;
            int accountNameTo;
            int amount;
            char date[11];
            
            FILE *pF = fopen(optarg, "r");
            if (pF == NULL) {
                printf("Error");
                exit(-1);
            }
            while (fscanf(pF, "%d %d %d %10s", &accountNameFrom, &accountNameTo, &amount, date) != EOF) {
                add_edge(graph, accountNameFrom, accountNameTo, amount, date);
            }
            fclose(pF);
            break;
        case 'o':
            printf("Output File: %s\n", optarg);
            break;
        case '?':
            printf("ERROR");
            exit(-1);
        }
    }

    
    print_graph(graph);

    destroy_graph(graph);
}