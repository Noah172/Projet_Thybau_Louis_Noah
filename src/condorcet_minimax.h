#ifndef CONDORCETM_H
#define CONDORCETM_H
#include <stdio.h>
#include "types.h"

extern int taille_matrice;

char *methodeCondorcetMinimax(t_mat_int_dyn matrice,
                              DynamicList liste_candidat, FILE* fichier);

#endif /* CONDORCET_H */
