/// \file condorcet_minimax.c
/// \brief Implementation de la méthode Condorcet avec utilisation de Minimax en
/// cas d'égalité.

#include "condorcet_minimax.h"
#include "list.h"
#include "modules/lecture_csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// \var int taille_matrice
/// \brief Taille de la matrice (nombre de candidats).
int taille_matrice;

/// \fn minimax(t_mat_int_dyn matrice)
/// \brief Trouve le minimum de chaque duel dans la matrice.
///
/// \param matrice La matrice des duels.
/// \return Le candidat qui a le plus petit score dans chaque duel, ou
/// -1 s'il y a une égalité.
int minimax(t_mat_int_dyn matrice, DynamicList liste_candidat, FILE *fichier) {

  DynamicList resultats;
  initDynamicList(&resultats);

  /// \brief Initialisation des indices du minimum
  DynamicList min;
  initDynamicList(&min);
  int index1 = 0;
  int index2 = 0;
  add(&min, &index1, INT_TYPE);
  add(&min, &index2, INT_TYPE);

  fprintf(fichier,
          "[Minimax] Création de la listes des minimums de chaque duel\n");
  /// \brief Parcours de la matrice pour trouver le minimum de chaque duel
  for (int i = 0; i < taille_matrice; i++) {
    set_int(&min, 0, i);
    set_int(&min, 1, i + 1);
    for (int j = 0; j < taille_matrice; j++) {
      if (matrice.data[get_int(&min, 0)][get_int(&min, 1)] >
              matrice.data[i][j] &&
          matrice.data[i][j] != 0) {
        set_int(&min, 0, i);
        set_int(&min, 1, j);
      }
    }

    add(&resultats, &matrice.data[get_int(&min, 0)][get_int(&min, 1)],
        INT_TYPE);
  }
  fprintf(fichier, "[Minimax] Listes des minimums créée\n");
  fprintf(fichier, "[Minimax] Recherche du maximum parmis les minimums\n");
  /// \brief Trouve le maximum parmi les minimums
  int max = 0;
  for (int i = 0; i < taille_matrice; i++) {
    if (get_int(&resultats, i) > get_int(&resultats, max)) {
      max = i;
    }
  }

  char *vainqueur = get_char(&liste_candidat, max);
  fprintf(fichier, "[Minimax] Maximum trouvé : correspondant au candidat %s\n",
          vainqueur);
  fprintf(fichier, "[Minimax] Recherche d'égalité\n");
  /// \brief Vérifie s'il y a des égalités
  int egalite = 0;
  for (int i = 0; i < taille_matrice; i++) {
    if (get_int(&resultats, i) == get_int(&resultats, max) && i != max)
      egalite = 1;
  }

  freeDynamicList(&resultats);

  if (egalite) {
    fprintf(fichier, "[Minimax] Égalité trouvée, pas de vainqueur\n");
    return -1;
  }
  fprintf(fichier, "[Minimax] Pas d'égalité trouvée\n");
  return max;
}

/**
 * \brief Calcul du vainqueur par la méthode Condorcet, utilisation de Minimax
 * si besoin.
 *
 * \param matrice Matrice des duels.
 * \return L'indice du candidat vainqueur par la méthode Condorcet, ou par
 * Minimax s'il y a une égalité.
 */
int condorcet_minimax(t_mat_int_dyn matrice, DynamicList liste_candidat,
                      FILE *fichier) {

  /// \brief Initialisation des indices du maximum

  DynamicList max;
  initDynamicList(&max);
  int index0 = 1;
  int index1 = 0;
  add(&max, &index0, INT_TYPE);
  add(&max, &index1, INT_TYPE);
  fprintf(fichier, "[Condorcet] Recherche du maximum de chaque duel\n");
  /// \brief Parcours de la matrice pour trouver le maximum de chaque duel
  for (int i = 0; i < taille_matrice; i++) {
    for (int j = 0; j < taille_matrice; j++) {
      
      if (matrice.data[get_int(&max, 0)][get_int(&max, 1)] <
          matrice.data[i][j]) {
        set_int(&max, 0, i);
        set_int(&max, 1, j);

      }
    }
  }
  printf("Maxmum %d\n", get_int(&max, 0));
  char *vainqueur = get_char(&liste_candidat, get_int(&max, 0));
  fprintf(fichier,
          "[Condorcet] Maximum trouvé : correspondant au candidat %s\n",
          vainqueur);
  fprintf(fichier, "[Condorcet] Recherche d'égalité\n");
  /// \brief Vérifie s'il y a égalité avec le maximum,
  int c = 0;
  for (int i = 1; i < taille_matrice; i++) {
    for (int j = 0; j < taille_matrice; j++) {
      if (matrice.data[get_int(&max, 0)][get_int(&max, 1)] ==
              matrice.data[i][j] &&
          get_int(&max, 0) != i) {
        c++;
      }
    }
  }

  /// \brief Si c vaut 0, alors il n'y a pas d'égalité et on a un vainqueur
  if (c == 0) {
    fprintf(fichier, "[Condorcet] Pas d'égalité trouvée\n");
    return get_int(&max, 0);
  } else {
    fprintf(fichier, "[Condorcet] Égalité trouvée, il n'y a pas de vainqueur, "
                     "tentons la méthode de minimax\n\n");
    return minimax(matrice, liste_candidat,
                   fichier); ///< Retourne le résultat de la méthode Minimax en
                             ///< cas d'égalité.
  }
}

/// \brief Fonction principale pour la méthode Condorcet Minimax.
///
/// \param matrice Matrice des duels.
/// \param liste_candidat Liste des candidats.
/// \return le gagnant de la méthode de Condorcet, ou "NULL" s'il n'y en a pas
char *methodeCondorcetMinimax(t_mat_int_dyn matrice, DynamicList liste_candidat,
                              FILE *fichier) {

  taille_matrice = matrice.cols;

  fprintf(fichier, "[Condorcet] Début du calcul\n");
  /// \brief Appel de la fonction pour trouver le vainqueur.
  int vainqueur = condorcet_minimax(matrice, liste_candidat, fichier);

  /// \brief Retourne le résultat
  if (vainqueur == -1)
    return "NULL";
  else
    return get_char(&liste_candidat, vainqueur);
}
