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

typedef struct{
    int id;
    int *vote;
}t_votants;

typedef struct {
  t_votants **votants;
  int nb_candidats;
  int nb_votants;
  char **candidats;
} t_votes;


/*typedef struct t_sommet {
  char *valeur;
  struct t_sommet *suivant; // Sommet suivant dans le graphe
  struct t_sommet *origine; // Sommet d'origine dans le graphe
} t_sommet;*/

typedef struct {
  char *source;
  char *destination;
  int poids;
} t_arc;

typedef struct {
  t_arc *arcs;
  t_sommet **sommets;
  int count;
} t_graph;

#endif // TYPES_H
