#ifndef CREATION_GRAPHE_H
#define CREATION_GRAPHE_H
#include "types.h"

Graph* createGraph();

void addNode(Graph* graph, int data);

void addEdge(Graph* graph, int src, int dest);

void printGraph(Graph* graph);

#endif
