// #include "types.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>



// // Fonction de comparaison pour le tri rapide
// int compare_arcs(const void *a, const void *b) {
//   return ((t_arc *)b)->poids - ((t_arc *)a)->poids;
// }

// // Fonction pour trier le graphe dans l'ordre décroissant par poids
// void trier_graphe(t_graph *graphe) {
//   qsort(graphe->arcs, graphe->count, sizeof(t_arc), compare_arcs);
// }

// void confirmer_arcs_sans_cycle(t_graph *graphe, int *visited, int *recStack,
//                                int v) {
//   visited[v] = 1;
//   recStack[v] = 1;

//   for (int i = 0; i < graphe->count; i++) {
//     if (graphe->arcs[i].confirme) {
//       if (!visited[i]) {
//         confirmer_arcs_sans_cycle(graphe, visited, recStack, i);
//       } else if (recStack[i]) {
//         // Si un arc crée un cycle, le marquer comme non confirmé
//         graphe->arcs[v].confirme = 0;
//       }
//     }
//   }

//   recStack[v] = 0;
// }

// void confirmerGraphe(t_graph *graphe) {
//   for (int i = 0; i < graphe->count; i++) {
//     // Vérifier si l'ajout de cet arc crée un cycle
//     int *visited = malloc(graphe->count * sizeof(int));
//     int *recStack = malloc(graphe->count * sizeof(int));
//     memset(visited, 0, graphe->count * sizeof(int));
//     memset(recStack, 0, graphe->count * sizeof(int));
    
//     confirmer_arcs_sans_cycle(graphe, visited, recStack, i);

//     if (graphe->arcs[i].confirme == 0) {
//       printf("L'arc %s %s n'est pas confirmé\n", graphe->arcs[i].source,
//              graphe->arcs[i].destination);
//     }
//   }
// }

// t_graph creer_graphe(t_mat_int_dyn matrice, char **liste_candidat) {
//   t_graph graphe;
//   graphe.arcs = malloc((matrice.rows * matrice.rows) * sizeof(t_arc));
//   graphe.count = 0;

//   // Parcours de la matrice des duels pour créer les arcs du graphe
//   for (int i = 0; i < matrice.rows; ++i) {
//     for (int j = 0; j < matrice.rows; ++j) {

//       int destination = matrice.data[j][i];
//       int source = matrice.data[i][j];

//       if (source != 0 && destination != 0 && source != destination &&
//           source - destination > 0/) {
//         t_arc arc;
//         arc.source = liste_candidat[i];
//         arc.destination = liste_candidat[j];
//         arc.poids = source - destination;
        
//         graphe.arcs[graphe.count] = arc;
//         graphe.count++;
//       }
//     }
//   }

//   trier_graphe(&graphe);

//   return graphe;
// }

// void afficherGraphe(t_graph graphe) {
//   for (int i = 0; i < graphe.count; i++) {
//     printf("Arc (%s, %s, %d)\n", graphe.arcs[i].source,
//            graphe.arcs[i].destination, graphe.arcs[i].poids);
//   }
// }
