#ifndef LECTURE_CSV_H
#define LECTURE_CSV_H

typedef struct {
    int **data;
    int rows;
    int cols;
} t_mat_int_dyn;


t_mat_int_dyn lire_fichier_csv(const char *nom_fichier);
void afficherMatrice(t_mat_int_dyn *matrice);


#endif /* LECTURE_CSV_H */
