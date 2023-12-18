/* \file creation_graphe.c
 * \brief Création et manipulation d'un graphe à partir d'une matrice de duels
 */
#include "list.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/** \fn Sommet* createNode(char* data)
 *  \brief Crée un nouveau sommet avec la donnée spécifiée.
 *  \param data Donnée associée au sommet.
 *  \return Pointeur vers le nouveau sommet.
 */
Sommet* createNode(char* data) {
  Sommet* newSommet= (Sommet*)malloc(sizeof(Sommet));
    newSommet->data = data;
    newSommet->next = NULL;
    newSommet->next_value = NULL;
    newSommet->nb_next = 0;
    return newSommet;
}

/** \fn Graph* createGraph()
 *  \brief Crée un nouveau graphe vide.
 *  \return Pointeur vers le nouveau graphe.
 */
Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numNodes = 0;
    graph->sommets = NULL;
    return graph;
}

/** \fn void addNode(Graph* graph, char* data)
 *  \brief Ajoute un nouveau sommet au graphe avec la donnée spécifiée.
 *  \param graph Pointeur vers le graphe.
 *  \param data Donnée associée au sommet.
 */
void addNode(Graph* graph, char* data) {
  Sommet* newSommet= createNode(data);

    graph->sommets = (Sommet**)realloc(graph->sommets, (graph->numNodes + 1) * sizeof(Sommet*));

    graph->sommets[graph->numNodes] = newSommet;
    graph->numNodes++;
}

/** \fn void addEdge(Sommet* src, Sommet* dest, int poids)
 *  \brief Ajoute une arête pondérée entre deux sommets.
 *  \param src Pointeur vers le sommet source.
 *  \param dest Pointeur vers le sommet de destination.
 *  \param poids Poids de l'arête.
 */
void addEdge( Sommet* src, Sommet* dest,int poids) {
    src->next = (Sommet**)realloc(src->next, (src->nb_next + 1) * sizeof(Sommet*));
    src->next_value = (int*)realloc(src->next_value, (src->nb_next + 1) * sizeof(int));


    src->next[src->nb_next] = dest;
    src->next_value[src->nb_next] = poids;
    src->nb_next++;
}

/** \fn void printGraph(Graph* graph)
 *  \brief Affiche le graphe avec les données des sommets et les poids des arêtes.
 *  \param graph Pointeur vers le graphe à afficher.
 */
void printGraph(Graph* graph) {
    for (int i = 0; i < graph->numNodes; ++i) {
        Sommet* currentSommet = graph->sommets[i];
        printf("Nœud %d :", i);

        for (int j = 0; j < currentSommet->nb_next; ++j) {
            printf(" -> %s (%d)", currentSommet->next[j]->data, currentSommet->next_value[j]);
        }

        printf("\n");
    }
}
