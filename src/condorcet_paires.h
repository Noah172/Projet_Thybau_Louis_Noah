#ifndef CONDORCETPAIRS_H
#define CONDORCETPAIRS_H

#include "creation_graphe.h"
void findMaxDuel(Graph *graph, int *max, FILE *fichier);
void eliminateCandidates(Graph *graph, int *max, FILE *fichier);
int CondorcetouPaires(t_mat_int_dyn matrice, DynamicList liste_candidat, FILE *fichier, int nb_votants);
int condorcet_pairs(t_mat_int_dyn matrice, DynamicList liste_candidat, FILE *fichier, int nb_votants);
#endif

