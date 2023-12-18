#ifndef TYPES_H
#define TYPES_H

// STRUCTURE DE DONNEE

// Structure d'un élément de la liste
typedef enum {
    INT_TYPE,
    CHAR_TYPE
} DataType;

typedef struct Node {
  int data_int;
  char* data_str;
  DataType type;
  struct Node *next;
} Node;

// Structure de la liste
typedef struct {
  Node *head;
  Node *tail;
  int nb_elem;
} CircularList;

typedef struct {
  Node *head;
  int size;
} DynamicList;

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
  int nb_candidats;
  int nb_votants;
  char *vainqueur;
  int score;
} t_resultat_uninominale;

typedef struct {
  int id;
  int *vote;
} t_votants;

typedef struct {
  t_votants **votants;
  int nb_candidats;
  int nb_votants;
  char **candidats;
} t_votes;

// GRAPHE

typedef struct t_sommet {
  char *valeur;
  struct t_sommet *suivant; // Sommet suivant dans le graphe
  struct t_sommet *origine; // Sommet d'origine dans le graphe
} t_sommet;

/*typedef struct {
  t_sommet *source;
  t_sommet *destination;
  int poids;
} t_arc;*/

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

// Structure pour représenter un cycle
typedef struct {
  t_arc *arcs;
  int count;
} t_cycle;

#endif // TYPES_H
