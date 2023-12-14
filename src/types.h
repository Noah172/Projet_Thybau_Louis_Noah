#ifndef TYPES_H
#define TYPES_H
typedef struct {
  int **data;
  int rows;
  int cols;
} t_mat_int_dyn;

typedef struct {
  char ***data;
  int rows;
  int cols;
} t_mat_char_star_dyn;

typedef struct {
  char **candidats;
  int nb_candidats;
  char *vainqueur;
  int nb_votants;
  int score;
} t_resultat_uninominale;

#endif // TYPES_H
