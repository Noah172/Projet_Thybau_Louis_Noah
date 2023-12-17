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
/// \return L'indice du candidat qui a le plus petit score dans chaque duel, ou
/// -1 s'il y a une égalité.
int minimax(t_mat_int_dyn matrice) {

  DynamicList resultats;
  initDynamicList(&resultats);

  /// \brief Initialisation des indices du minimum
  DynamicList min;
  initDynamicList(&min);
  int index1 = 1;
  add(&min, &index1, INT_TYPE);
  add(&min, &index1, INT_TYPE);

  /// \brief Parcours de la matrice pour trouver le minimum de chaque duel
  for (int i = 1; i < taille_matrice; i++) {
    for (int j = 0; j < taille_matrice; j++) {
      if (matrice.data[get_int(&min, 0)][get_int(&min, 1)] >
              matrice.data[i][j] &&
          matrice.data[i][j] != 0) {
        set_int(&min, 0, i);
        set_int(&min, 1, j);
      }
    }
    set_int(&resultats, i, matrice.data[get_int(&min, 0)][get_int(&min, 1)]);
  }

  /// \brief Trouve le maximum parmi les minimaux
  int max = 0;
  for (int i = 0; i < taille_matrice; i++) {
    if (get_int(&resultats, i) > get_int(&resultats, max)) {
      max = i;
    }
  }

  /// \brief Vérifie s'il y a des égalités
  int egalite = 0;
  for (int i = 0; i < taille_matrice; i++) {
    if (get_int(&resultats, i) == get_int(&resultats, max) && i != max)
      egalite = 1;
  }

  freeDynamicList(&resultats);

  if (egalite)
    return -1;

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
int condorcet_minimax(t_mat_int_dyn matrice) {

  /// \brief Initialisation des indices du maximum

  DynamicList max;
  initDynamicList(&max);
  int index0 = 1;
  int index1 = 0;
  add(&max, &index0, INT_TYPE);
  add(&max, &index1, INT_TYPE);
  /// \brief Parcours de la matrice pour trouver le maximum de chaque duel

  for (int i = 1; i < taille_matrice; i++) {
    for (int j = 0; j < taille_matrice; j++) {
      if (matrice.data[get_int(&max, 0)][get_int(&max, 1)] <
          matrice.data[i][j]) {
        set_int(&max, 0, i);
        set_int(&max, 1, j);
      }
    }
  }

  /// \brief Vérifie s'il y a égalité avec le maximum, c étant le compteur
  /// d'égalité
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
    return get_int(&max, 0);
  } else {
    printf("Il n'y a pas de vainqueur, tentons la méthode de minimax\n");
    return minimax(matrice); ///< Retourne le résultat de la méthode Minimax en
                             ///< cas d'égalité.
  }
}

/// \brief Fonction principale pour la méthode Condorcet Minimax.
///
/// \param matrice Matrice des duels.
/// \param liste_candidat Liste des candidats.
/// \return 0 en cas de succès, affiche le vainqueur ou informe qu'il n'y en a
/// pas.
int methodeCondorcetMinimax(t_mat_int_dyn matrice, DynamicList liste_candidat) {
  printf("\n\n\033[1;34m======================================================="
         "=====\n");
  printf("============================================================\n");
  printf("=====================\033[1;31mCONDORCET "
         "MINIMAX\033[1;34m======================\n");
  printf("============================================================\n");
  printf("============================================================\n\n\033["
         "0m");

  taille_matrice = matrice.cols;

  /// \brief Appel de la fonction pour trouver le vainqueur.
  int vainqueur = condorcet_minimax(matrice);

  /// \brief Affiche le résultat
  if (vainqueur == -1)
    printf("Il n'y a pas de vainqueur par la méthode Condorcet et Minimax\n");
  else
    printf("Le vainqueur par la méthode de condorcet est est le candidat %s\n",
           get_char(&liste_candidat, vainqueur));
  return 0;
}
