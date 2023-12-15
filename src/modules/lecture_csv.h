#ifndef LECTURE_CSV_H
#define LECTURE_CSV_H
#include "../types.h"

t_mat_char_star_dyn lire_fichier_csv(const char *nom_fichier);
void afficherMatrice(t_mat_char_star_dyn *matrice);
void afficherMatriceInt(t_mat_int_dyn *matrice);

#endif /* LECTURE_CSV_H */
