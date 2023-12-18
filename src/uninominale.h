#ifndef UNINOMINALE_H
#define UNINOMINALE_H
#include "types.h"
#include <stdbool.h>
#include <stdio.h>


char *trouver_vainqueur(t_mat_char_star_dyn *mat_votes);
char* uninominale_un_tour(t_mat_char_star_dyn *mat_votes,FILE *fichier);
char* uninominale_deux_tours(t_mat_char_star_dyn *mat_votes,FILE *fichier);
void afficher_resultat_uninominal(t_resultat_uninominale resultat, bool deuxTours);
char* methode_uninomale(t_mat_char_star_dyn *votes, bool deuxTours, FILE *fichier);

#endif /* UNINOMINALE_H */
