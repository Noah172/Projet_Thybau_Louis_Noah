#ifndef CONDORCETM_H
#define CONDORCETM_H
#include "types.h"

extern int taille_matrice;

int minimax(t_mat_int_dyn matrice);
int condorcet_minimax(t_mat_int_dyn matrice);
int methodeCondorcetMinimax(t_mat_int_dyn matrice, char **liste_candidat);

#endif /* CONDORCET_H */
