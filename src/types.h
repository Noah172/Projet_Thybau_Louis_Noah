/// \file types.h
/// \brief Définir les différents types utilisés dans le projet

#ifndef TYPES_H
#define TYPES_H

/// \enum DataType
/// \brief Enumération définissant le type de données pour un élément de la
/// liste.
typedef enum {
  INT_TYPE, ///< Entier
  CHAR_TYPE, ///< Chaine de caractères
  SOMMET_TYPE ///< Sommet
} DataType;

/// \struct Node
/// \brief Structure d'un élément de la liste.
typedef struct Node {
  int data_int;      ///< Donnée de type entier.
  char *data_str;    ///< Donnée de type chaîne de caractères.
  DataType type;     ///< Type de la donnée.
  struct Node *next; ///< Pointeur vers l'élément suivant.
} Node;

/// \struct CircularList
/// \brief Structure d'une liste circulaire.
typedef struct {
  Node *head;  ///< Pointeur vers le premier élément de la liste.
  Node *tail;  ///< Pointeur vers le dernier élément de la liste.
  int nb_elem; ///< Nombre d'éléments dans la liste.
} CircularList;

/// \struct DynamicList
/// \brief Structure d'une liste dynamique.
typedef struct {
  Node *head; ///< Pointeur vers le premier élément de la liste.
  int size;   ///< Nombre d'éléments dans la liste.
} DynamicList;

/// \struct t_mat_int_dyn
/// \brief Structure pour représenter une matrice d'entiers dynamique.
typedef struct {
  int **data; ///< Tableau de données (matrice).
  int rows;   ///< Nombre de lignes dans la matrice.
  int cols;   ///< Nombre de colonnes dans la matrice.
} t_mat_int_dyn;

/// \struct t_mat_char_star_dyn
/// \brief Structure pour représenter une matrice de chaînes de caractères
/// dynamique.
typedef struct {
  char ***data; ///< Tableau de données (matrice).
  int rows;     ///< Nombre de lignes dans la matrice.
  int cols;     ///< Nombre de colonnes dans la matrice.
} t_mat_char_star_dyn;

/// \struct t_resultat_uninominale
/// \brief Structure pour représenter les résultats d'une élection uninominale.
typedef struct {
  char **candidats; ///< Tableau des noms des candidats.
  int nb_candidats; ///< Nombre de candidats.
  char *vainqueur;  ///< Nom du vainqueur.
  int nb_votants;   ///< Nombre de votants.
  float score;        ///< Score du vainqueur.
} t_resultat_uninominale;

/// \struct t_votants
/// \brief Structure pour représenter les votes d'un votant.
typedef struct {
  int id;    ///< Identifiant du votant.
  int *vote; ///< Tableau des votes du votant.
} t_votants;

/// \struct t_votes
/// \brief Structure pour représenter l'ensemble des votes.
typedef struct {
  t_votants **votants; ///< Tableau des votants.
  int nb_candidats;    ///< Nombre de candidats.
  int nb_votants;      ///< Nombre de votants.
  char **candidats;    ///< Tableau des noms des candidats.
} t_votes;

typedef struct {
    char **candidats;
    int *notes;
    int *medianes;
    int nb_candidats;
    int nb_votants;
} t_resultat_majoritaire;

// GRAPHE


// Structure représentant un nœud du graphe
typedef struct Sommet {
  char* data;
  struct Sommet **next;
  int *next_value;
  int nb_next;
} Sommet;

// Structure représentant le graphe
typedef struct Graph {
  int numNodes;
  Sommet **sommets;
} Graph;

#endif // TYPES_H
