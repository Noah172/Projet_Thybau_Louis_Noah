#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "condorcet.h"

int nb_votant;
int nb_candidat;

void condorcet(int nb_votant, int nb_candidat, int votes[nb_votant][nb_candidat], int *resultats) {
  // int c = 0;
  for (int i = 0; i < nb_votant; i++) {
    for (int j = 0; j < nb_votant; j++) {
      int positionCandidat1 = -1;
      int positionCandidat2 = -1;

      for (int k = i + 1; k < nb_votant; k++) {

        char mess[250];
        strcpy(mess, "Dans la ligne : [");
        for (int l = 0; l < nb_candidat - 1; l++) {
          char a[20];
          sprintf(a, "%d, ", votes[j][l]);
          strcat(mess, a);
        }
        char b[30];
        sprintf(b, "%d] ", votes[j][nb_votant - 1]);
        strcat(mess, b);
        int c1 = i + 1;
        int c2 = k + 1;

        char c[34];
        sprintf(c, "Le préféré entre %d et %d est : ", c1, c2);
        strcat(mess, c);

        for (int l = 0; l < nb_candidat; l++) {
          if (votes[j][l] == c1) {
            positionCandidat1 = l;
          }
          if (votes[j][l] == c2) {
            positionCandidat2 = l;
          }
        }

        if (positionCandidat1 > positionCandidat2) {
          char d[10];
          sprintf(d, "%d", c2);
          strcat(mess, d);
          printf("%s\n", mess);
          resultats[c2 - 1]++;
        } else {
          char d[10];
          sprintf(d, "%d", c1);
          strcat(mess, d);
          printf("%s\n", mess);
          resultats[c1 - 1]++;
        }
      }
      printf("\n");
    }
  }

}

int trouverVainqueur(int *resultats) {
  int vainqueur = 0;

  for (int i = 1; i < nb_candidat; i++) {
    if (resultats[i] > resultats[vainqueur]) {
      vainqueur = i;
    }
  }

  return vainqueur;
}

int methodeCondorcet() {
    printf("\n\n\033[1;34m============================================================\n");
printf("============================================================\n");
printf("=========================\033[1;31mCONDORCET\033[1;34m==========================\n");
printf("============================================================\n");
printf("============================================================\n\n\033[0m");

  int votes[5][4] = {
      {1, 3, 2, 4}, {4, 1, 2, 3}, {4, 1, 3, 2}, {4, 2, 1, 3}, {4, 3, 2, 1}};

  nb_candidat = sizeof(votes[0]) / sizeof(votes[0][0]);
  nb_votant = sizeof(votes) / sizeof(votes[0]);

  printf("nb_votant %d, nb_candidat %d\n", nb_votant, nb_candidat);

  int *resultats =malloc(sizeof(int) * nb_candidat);
  condorcet(nb_votant, nb_candidat, votes, resultats);


  int vainqueur = trouverVainqueur(resultats);

  printf("Résultats de la méthode de Condorcet :\n");
  for (int i = 0; i < nb_candidat; i++) {
    printf("Candidat %d : %d victoires\n", i + 1, resultats[i]);
  }

  printf("Le vainqueur est le candidat %d\n", vainqueur + 1);

  return 0;
}
