#ifndef UNINOMINALE_H
#define UNINOMINALE_H

#include "modules/lecture_csv.h"

typedef struct {
  char **candidats;
  int nb_candidats;
  char *vainqueur;
  int nb_votants;
  int score;
} t_resultat_uninominale;

t_mat_int_dyn init_mat_int_dyn(int rows, int cols);
void free_mat_int_dyn(t_mat_int_dyn *mat);

t_resultat_uninominale init_resultat_uninominale(int nb_candidats);
void free_resultat_uninominale(t_resultat_uninominale *resultat);

t_resultat_uninominale uninominale_un_tour(const t_mat_int_dyn *mat_votes, int nb_candidats);
t_resultat_uninominale uninominale_deux_tours(const t_mat_int_dyn *mat_votes, int nb_candidats);

void afficher_resultat_uninominale(int tour, t_resultat_uninominale resultat);

int methodeUninominales();
#endif /* UNINOMINALE_H */
