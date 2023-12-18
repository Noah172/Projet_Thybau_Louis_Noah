/// \file creation_graphe.c
/// \brief Créer le graphe à partir de la matrice de duet et le confirmer
/// \brief ATTENTION : PAS TERMINÉ

#include "list.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// \fn compare_arcs(const void *a, const void *b)
/// \brief Fonction de comparaison pour le tri rapide des arcs du graphe.
/// \param a Pointeur vers le premier arc.
/// \param b Pointeur vers le deuxième arc.
/// \return Valeur négative si le poids du premier arc est inférieur à celui du
/// deuxième, 0 en cas d'égalité, et positive sinon.
/*int compare_arcs(const void *a, const void *b) {
  return ((t_arc *)b)->poids - ((t_arc *)a)->poids;
}*/

/// \fn void trier_graphe(t_graph *graphe)
/// \brief Fonction pour trier les arcs du graphe dans l'ordre décroissant par
/// poids. \param graphe Pointeur vers la structure du graphe.
/*void trier_graphe(t_graph *graphe) {
  qsort(graphe->arcs, graphe->count, sizeof(t_arc), compare_arcs);
}*/

/// \fn void confirmerGraphe(t_graph *graphe)
/// \brief Fonction pour confirmer le graphe en vérifiant la présence de cycles.
/// \param graphe Pointeur vers la structure du graphe.
/*void confirmerGraphe(t_graph *graphe) {
  for (int i = 0; i < graphe->count; i++) {
    int *visited = malloc(graphe->count * sizeof(int));
    int *recStack = malloc(graphe->count * sizeof(int));
    memset(visited, 0, graphe->count * sizeof(int));
    memset(recStack, 0, graphe->count * sizeof(int));

    /// \brief A FINIR
  }
}*/

// Fonction pour créer un nouveau nœud
Sommet* createNode(char* data) {
  Sommet* newSommet= (Sommet*)malloc(sizeof(Sommet));
    newSommet->data = data;
    newSommet->next = NULL;
    return newSommet;
}

// Fonction pour créer un graphe vide
Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numNodes = 0;
    graph->sommets = NULL;
    return graph;
}

// Fonction pour ajouter un nœud au graphe
void addNode(Graph* graph, char* data) {
  Sommet* newSommet= createNode(data);

    graph->sommets = (Sommet**)realloc(graph->sommets, (graph->numNodes + 1) * sizeof(Sommet*));

    graph->sommets[graph->numNodes] = newSommet;
    graph->numNodes++;
}

// Fonction pour ajouter une arête dirigée entre deux nœuds
void addEdge(Graph* graph, Sommet* src, Sommet* dest) {
  
        newSommet->next = graph->sommets[src];
        graph->sommets[src] = newSommet;
}

// Fonction pour afficher le graphe
void printGraph(Graph* graph) {
    for (int i = 0; i < graph->numNodes; ++i) {
      Sommet* currentSommet= graph->sommets[i];
        printf("Nœud %d :", i);

        while (currentSommet!= NULL) {
            printf(" -> %d", currentSommet->data);
            currentSommet= currentSommet->next;
        }

        printf("\n");
    }
}
