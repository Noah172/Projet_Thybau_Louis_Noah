#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int taille_matrice;

int minimax(int votes[taille_matrice][taille_matrice]) {
  int *resultats = malloc(sizeof(int) * taille_matrice);

  //Trouver le min de chaque duel
  int min[2] = {0, 1};
  for (int i = 0; i < taille_matrice; i++) {
    for (int j = 0; j < taille_matrice; j++) {
      if (votes[min[0]][min[1]] > votes[i][j] && votes[i][j] != 0) {
        min[0] = i;
        min[1] = j;
      }
    }
    resultats[i] = votes[min[0]][min[1]];
  }

  //trouver le max des min
  int max = 0;
  for(int i = 0; i < taille_matrice; i++) {
    if(resultats[i] > resultats[max]) {
        max =i;
    }
  }
  
  //verifier s'il y a des égalité
  int egalite = 0;
  for(int i = 0; i < taille_matrice; i++) {
    if(resultats[i] == resultats[max] && i != max) 
        egalite = 1;
  }

  free(resultats);
  
  if(egalite)
    return -1;
  
  return max;
}

int condorcet(int votes[taille_matrice][taille_matrice]) {
  //chercher le max de chaque ligne
  int max[2] = {0, 0};
  for (int i = 0; i < taille_matrice; i++) {
    for (int j = 0; j < taille_matrice; j++) {
      if (votes[max[0]][max[1]] < votes[i][j]) {
        max[0] = i;
        max[1] = j;
      }
    }
  }

  //verifier s'il y a égalité avec le max, c étant le compteur d'égalité
  int c = 0;
  for (int i = 0; i < taille_matrice; i++) {
    for (int j = 0; j < taille_matrice; j++) {
      if (votes[max[0]][max[1]] == votes[i][j] && max[0] != i) {
        c++;
      }
    }
  }  

  //si c vaut 0, alors il n'y a pas d'égalité et on a un vainqueur
  if (c == 0){
    return max[0];
  }
  else {
    printf("Il n'y a pas de vainqueur, tentons la méthode de minimax\n");
    return minimax(votes);
  }
}



int main() {
  char liste_candidat[3] = {'A', 'B', 'C'};
  //int votes[3][3] = {{0, 25, 23}, {35, 0, 19}, {37, 41, 0}};
  int votes[3][3] = {{0, 2, 1}, {1, 0, 2}, {2, 1, 0}};

  taille_matrice = sizeof(votes[0]) / sizeof(votes[0][0]);

  int vainqueur = condorcet(votes);

  if(vainqueur == -1)
    printf("Il n'y a pas de vainqueur par la méthode Condorcet et      Minimax\n");
  else
    printf("Le vainqueur par la méthode de condorcet est est le candidat %c\n", liste_candidat[vainqueur]);

  return 0;
}
