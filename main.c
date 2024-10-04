#include <stdio.h>
#include "graph.h"

int main()
{
    Graph graph1 = create_graph(5);
    print_graph(graph1);

    destroy_graph(graph1);
}