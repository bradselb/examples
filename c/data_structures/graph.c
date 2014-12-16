#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

struct node 
{
    int nr;
    int weight;
    struct node* next;
};

// -------------------------------------------------------------------------
static struct node* create_node(int nr, int weight)
{
    struct node* node;
    node = malloc(sizeof(struct node));
    if (node) {
        node->nr = nr;
        node->weight = weight;
        node->next = 0;
    }
    return node;
}

// -------------------------------------------------------------------------
static void delete_node(struct node* node)
{
    if (node) {
        node->next = 0;
        free(node);
    }
}


// -------------------------------------------------------------------------
static int insert_node(struct node* head, struct node* node)
{
    int rc;
    struct node* p;

    rc = -1;

    if (!head || !node) {
        goto OUT;
    }

    p = head;
    while (p != 0) {
        // duplicate edges are not allowed
        if (p->next && p->next->nr == node->nr) {
            break;
        }
        // edges that start and end on same vertex are not allowed. 
        if (p->nr == node->nr) {
            break;
        }
        
        // The head node represents the vertex from which this edge
        // originates so,  never insert a node in front of the head node. 
        if (p->next && p->next->nr < node->nr) {
            p = p->next;
        } else {
            node->next = p->next;
            p->next = node;
            rc = 0; // success.
            break;
        }
    }

OUT:
    return rc;
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
// An adjacency list representation of a graph.
// The adjacency list is an array of nodes.
// Each node in the array represents a vertex. 
// Each node in the arrary is also the head of a linked list of nodes.
// Each of the nodes in the list after the head represents an edge from 
// the vertex represented by the head node to the vertex represented by 
// that node. 
struct graph
{
    int order; // the cardinality of the vertex set.
    struct node* vertex; 
};



// -------------------------------------------------------------------------
struct graph* graph_create(int order)
{
    struct graph* graph = 0;
    if (order < 0) {
        goto EXIT;
    }

    graph = malloc(sizeof(struct graph)); 
    if (!graph) {
        goto EXIT;
    }

    graph->order = 0;


    // allocate an array of nodes - this is the adjacency list.
    graph->vertex = malloc(order * sizeof(struct node));
    if (!graph->vertex) {
        free(graph);
        graph = 0;
        goto EXIT;
    }

    // initialize each node in the array
    graph->order = order;
    for (int i=0; i<order; ++i) {
        graph->vertex[i].nr = i;
        graph->vertex[i].weight = 0;
        graph->vertex[i].next = 0;
    }

EXIT:
    return graph;
}

// -------------------------------------------------------------------------
void graph_delete(struct graph* graph)
{
    if (graph) {
        struct node* neighbor;
        struct node* next;
        // for each vertex in the graph
        // walk the list of neighbors and delete each node
        for (int i=0; i<graph->order; ++i) {
            neighbor = graph->vertex[i].next;
            while (neighbor) {
                next = neighbor->next;
                delete_node(neighbor);
                neighbor = next;
            }
        }
    } // if graph
}

// -------------------------------------------------------------------------
int graph_add_edge(struct graph* graph, int from, int to, int weight)
{
    int rc;

    rc = -1;
    if (graph) {
        struct node* head = &graph->vertex[from];
        struct node* node = create_node(to, weight);
        rc = insert_node(head, node);
        if (rc != 0) {
            delete_node(node);
        }
    }

    return rc;
}


// -------------------------------------------------------------------------
int graph_print_edges(struct graph* graph)
{
    int rc = 0;

    if (graph) {
        struct node* neighbor;
        // for each vertex in the graph
        // walk the list of neighbors and print each one.
        for (int i=0; i<graph->order; ++i) {
            printf("\n%d: ", i); 
            neighbor = graph->vertex[i].next;
            while (neighbor) {
                printf("%d->%d(%d) ", i, neighbor->nr, neighbor->weight);
                neighbor = neighbor->next;
            }
        }
        printf("\n");
    }

    return rc;
}
