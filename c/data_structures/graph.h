#if !defined ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

struct graph;

struct graph* graph_create(int vertices);
void graph_delete(struct graph*);

int graph_add_edge(struct graph*, int from, int to, int weight);
int graph_print_edges(struct graph* graph);


#endif //!defined ADJACENCY_LIST_H
