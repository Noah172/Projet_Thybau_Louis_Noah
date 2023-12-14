#include "condorcet_minimax.h"
#include "modules/lecture_csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int taille_matrice;
int minimax(t_mat_int_dyn matrice) {

  int *resultats = malloc(sizeof(int) * taille_matrice);

  // Trouver le min de chaque duel
  int min[2] = {1, 1};
  for (int i = 1; i < taille_matrice; i++) {
    for (int j = 0; j < taille_matrice; j++) {
      if (matrice.data[min[0]][min[1]] > matrice.data[i][j] &&
          matrice.data[i][j] != 0) {
        min[0] = i;
        min[1] = j;
      }
    }
    resultats[i] = matrice.data[min[0]][min[1]];
  }

  // trouver le max des min
  int max = 0;
  for (int i = 0; i < taille_matrice; i++) {
    if (resultats[i] > resultats[max]) {
      max = i;
    }
  }

  // verifier s'il y a des égalité
  int egalite = 0;
  for (int i = 0; i < taille_matrice; i++) {
    if (resultats[i] == resultats[max] && i != max)
      egalite = 1;
  }

  free(resultats);

  if (egalite)
    return -1;

  return max;
}

int condorcet_minimax(t_mat_int_dyn matrice) {
  // chercher le max de chaque ligne
  int max[2] = {1, 0};
  for (int i = 1; i < taille_matrice; i++) {
    for (int j = 0; j < taille_matrice; j++) {
      if (matrice.data[max[0]][max[1]] < matrice.data[i][j]) {
        max[0] = i;
        max[1] = j;
      }
    }
  }

  // verifier s'il y a égalité avec le max, c étant le compteur d'égalité
  int c = 0;
  for (int i = 1; i < taille_matrice; i++) {
    for (int j = 0; j < taille_matrice; j++) {
      if (matrice.data[max[0]][max[1]] == matrice.data[i][j] && max[0] != i) {
        c++;
      }
    }
  }

  // si c vaut 0, alors il n'y a pas d'égalité et on a un vainqueur
  if (c == 0) {
    return max[0];
  } else {
    printf("Il n'y a pas de vainqueur, tentons la méthode de minimax\n");
    return minimax(matrice);
  }
}

int methodeCondorcetMinimax(t_mat_int_dyn matrice, char **liste_candidat) {
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
           liste_candidat[vainqueur]);
  return 0;
}
