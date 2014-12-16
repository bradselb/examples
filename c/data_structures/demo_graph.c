#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

int main(int argc, char* argv[])
{
    struct graph* graph;
    const int count = 5;

    graph = graph_create(count);
    graph_add_edge(graph, 0, 1, 2);
    graph_add_edge(graph, 0, 2, 1);
    graph_add_edge(graph, 1, 3, 3);
    graph_add_edge(graph, 2, 1, 5);
    graph_add_edge(graph, 2, 4, 6);
    graph_add_edge(graph, 4, 3, 1);

    graph_add_edge(graph, 0, 1, 2);
    graph_add_edge(graph, 0, 1, 2);
    graph_add_edge(graph, 3, 3, 0);

    graph_print_edges(graph);
    graph_delete(graph);

    return 0;
}
