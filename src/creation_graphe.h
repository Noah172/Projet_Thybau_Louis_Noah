#ifndef CREATION_GRAPHE_H
#define CREATION_GRAPHE_H
#include "types.h"

Sommet* createNode(char* data);
Graph* createGraph();
void addNode(Graph* graph, char* data);
void addEdge(Sommet* src, Sommet* dest, int poids);
void printGraph(Graph* graph);
#endif
