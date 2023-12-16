#ifndef CREATION_GRAPHE_H
#define CREATION_GRAPHE_H
#include "types.h"

t_graph creer_graphe(t_mat_int_dyn matrice, char **liste_candidat);

void afficherGraphe(t_graph graphe);

void confirmerGraphe(t_graph *graphe);

#endif
