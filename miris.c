#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <bits/getopt_core.h>

int main(int argc, char *argv[])
{
    // if (argc != 3){
    //     printf("Two args required");
    //     exit(-1);
    // }

    int option;
    while((option = getopt(argc , argv, ":i:o")) != -1){
        switch (option)
        {
        case 'i':
            printf("Input File: %s\n", optarg);
            break;
        case 'o':
            printf("Output File: %s\n", optarg);
            break;
        case '?':
            printf("ERROR");
            exit(-1);
        }
    }

    Graph graph = create_graph(5);
    
    add_edge(graph,0,1,5);
    add_edge(graph,0,2,3);
    add_edge(graph,1,2,2);
    add_edge(graph,2,3,7);

    print_graph(graph);

    destroy_graph(graph);
}