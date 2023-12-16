#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_graph creer_graphe(t_mat_int_dyn matrice, char **liste_candidat) {
  t_graph graphe;
  graphe.arcs = malloc(matrice.rows * sizeof(t_arc));
  graphe.count = 0;

  // Parcours de la matrice des duels pour créer les arcs du graphe
  for (int i = 0; i < matrice.rows; ++i) {
    for (int j = 0; j < matrice.rows; ++j) {

      int destination = matrice.data[j][i];
      int source = matrice.data[i][j];

      if (source != 0 && destination != 0 && source != destination &&
          source - destination > 0) {
        t_arc arc;
        arc.source = liste_candidat[i];
        arc.destination = liste_candidat[j];
        arc.weight = source - destination;
        graphe.arcs[i] = arc;
      }
    }
    graphe.count++;
  }

  return graphe;
}

void afficherGraphe(t_graph graphe) {
  for (int i = 0; i < graphe.count; i++) {
    printf("Arc (%s, %s, %d)\n", graphe.arcs[i].source,
           graphe.arcs[i].destination, graphe.arcs[i].weight);
  }
}
