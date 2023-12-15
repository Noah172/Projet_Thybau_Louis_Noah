#include "condorcet_minimax.h"
#include "modules/lecture_csv.h"
#include "modules/csv_votes.h"
#include "uninominale.h"
#include "jugement_majoritaire.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_mat_int_dyn creation_matrice_int_depuis_char(t_mat_char_star_dyn *matrice_char) {
  t_mat_int_dyn matrice_duel;
  matrice_duel.cols = matrice_char->cols;
  matrice_duel.rows = matrice_char->rows - 1;
  matrice_duel.data = malloc(matrice_duel.rows * sizeof(char **));

  // Allouer de la mémoire pour chaque ligne de la nouvelle matrice
  for (int i = 0; i < matrice_duel.rows; ++i) {
    matrice_duel.data[i] = malloc(matrice_duel.cols * sizeof(char *));
  }
  // Copier les valeurs de la matrice originale dans la nouvelle matrice
  for (int i = 0; i < matrice_char->rows - 1; ++i) {
    for (int j = 0; j < matrice_char->cols; ++j) {
      matrice_duel.data[i][j] = atoi(matrice_char->data[i + 1][j]);
    }
  }

  return matrice_duel;
}

int balise_i = 0;
int balise_d = 0;

void check_balise() {
  if (balise_i && balise_d) {
    fprintf(stderr, "Balise -i et -d incompatible\n");
    exit(EXIT_FAILURE);
  }
}

int i;
int d;
int o;
int m;
char *param_o;
char *param_m;

void lire_balise(int argc, char *argv[]) {

  i = 0;
  d = 0;
  o = 0;
  m = 0;

  int option;
  while ((option = getopt(argc, argv, "ido:m:")) != -1) {

    if (option == 'i') {
      balise_i = 1;
      check_balise();
      printf("Le fichier csv est le resultat d'un vote\n\n");
      i = 1;
    }

    if (option == 'd') {
      balise_d = 1;
      check_balise();
      printf("Le fichier csv est une matrice de duet\n");
      printf("Désactive les parametres uni1 et uni2 de la balise -m\n\n");
      d = 1;
    }

    if (option == 'o') {
      printf("Le fichier donné juste après sera traité comme un fichier de "
             "log\n\n");
      printf("NOM du fichier : %s\n", optarg);
      param_o = optarg;
      o = 1;
    }
    if (option == 'm') {
      printf("Applique la/les méthodes de scrutins donnée.s juste après\n\n");
      printf("NOM du fichier : %s\n", optarg);
      param_m = optarg;
      m = 1;
    }
  }
}

int main(int argc, char *argv[]) {

  if (argc < 3) {
    fprintf(stderr, "Usage : <nom_fichier_csv> <liste des balises éventuels, "
                    "avec leur parametre>\n");
    exit(EXIT_FAILURE);
  }
  char *rep_fichier = "fich_tests/";
  char *nom_fichier =
      malloc(sizeof(char) * sizeof(rep_fichier) +
             sizeof(char) * sizeof(argv[1]) + sizeof(char) * 10);
  strcpy(nom_fichier, rep_fichier);
  strcat(nom_fichier, argv[1]);

  lire_balise(argc, argv);

  if (i) {
      t_votes *mat_votes = lireVotesDepuisCSV(nom_fichier);
      afficherVotes(mat_votes);
      // t_mat_int_dyn matrice_duel = creation_matrice_int_depuis_char(&mat_votes);

  }

  if (d) {
  }

  // methodeUninominales();
  // methodeCondorcetMinimax(matrice_duel, mat_votes.data[0]);
  // jugementMajoritaire();

  free(nom_fichier);
  return 0;
}
