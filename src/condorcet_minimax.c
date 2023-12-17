#include "condorcet_minimax.h"
#include "list.h"
#include "modules/lecture_csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int taille_matrice;

int minimax(t_mat_int_dyn matrice) {

  DynamicList resultats;
  initDynamicList(&resultats);

  // Trouver le min de chaque duel
  DynamicList min;
  initDynamicList(&min);
  int index1 = 1;
  add(&min, &index1, INT_TYPE);
  add(&min, &index1, INT_TYPE);

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

  // trouver le max des min
  int max = 0;
  for (int i = 0; i < taille_matrice; i++) {
    if (get_int(&resultats, i) > get_int(&resultats, max)) {
      max = i;
    }
  }

  // verifier s'il y a des égalité
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

int condorcet_minimax(t_mat_int_dyn matrice) {

  DynamicList max;
  initDynamicList(&max);
  int index0 = 1;
  int index1 = 0;
  add(&max, &index0, INT_TYPE);
  add(&max, &index1, INT_TYPE);
  for (int i = 1; i < taille_matrice; i++) {
    for (int j = 0; j < taille_matrice; j++) {
      if (matrice.data[get_int(&max, 0)][get_int(&max, 1)] <
          matrice.data[i][j]) {
        set_int(&max, 0, i);
        set_int(&max, 1, j);
      }
    }
  }

  // verifier s'il y a égalité avec le max, c étant le compteur d'égalité
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

  // si c vaut 0, alors il n'y a pas d'égalité et on a un vainqueur
  if (c == 0) {
    return get_int(&max, 0);
  } else {
    printf("Il n'y a pas de vainqueur, tentons la méthode de minimax\n");
    return minimax(matrice);
  }
}

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

  int vainqueur = condorcet_minimax(matrice);

  if (vainqueur == -1)
    printf("Il n'y a pas de vainqueur par la méthode Condorcet et Minimax\n");
  else
    printf("Le vainqueur par la méthode de condorcet est est le candidat %s\n",
           get_char(&liste_candidat, vainqueur));
  return 0;
}
