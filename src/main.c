#include "condorcet_minimax.h"
#include "creation_graphe.h"
#include "jugement_majoritaire.h"
#include "list.h"
#include "modules/csv_votes.h"
#include "modules/lecture_csv.h"
#include "uninominale.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_mat_int_dyn
creation_matrice_int_depuis_vote_ballots(t_mat_char_star_dyn *mat_votes) {
  DynamicList liste_candidat;
  initDynamicList(&liste_candidat);

  for (int i = 4; i < mat_votes->cols; i++) {
    add(&liste_candidat, mat_votes->data[0][i], CHAR_TYPE);
  }

  // creer matrce de duel
  t_mat_int_dyn matrice_duel;
  matrice_duel.cols = mat_votes->cols - 4;
  matrice_duel.rows = mat_votes->cols - 4;
  matrice_duel.data = malloc(matrice_duel.rows * sizeof(int *));

  // Allouer de la mémoire pour chaque ligne de la nouvelle matrice
  for (int i = 0; i < matrice_duel.rows; ++i) {
    matrice_duel.data[i] = malloc(matrice_duel.cols * sizeof(int));
  }

  int nb_candidats = mat_votes->cols - 4;
  int nb_votants = mat_votes->rows;
  for (int i = 0; i < nb_candidats; i++) {
    matrice_duel.data[i] = (int *)malloc(nb_candidats * sizeof(int));
    memset(matrice_duel.data[i], 0, nb_candidats * sizeof(int));
  }
  for (int i = 1; i < nb_votants; i++) {
    for (int j = 0; j < nb_candidats; j++) {
      for (int k = j; k < nb_candidats; k++) {
        int classement_candidat1 = atoi(mat_votes->data[i][j + 4]);
        int classement_candidat2 = atoi(mat_votes->data[i][k + 4]);

        if (classement_candidat1 < classement_candidat2) {
          matrice_duel.data[j][k]++;
        } else if (classement_candidat1 > classement_candidat2) {
          matrice_duel.data[k][j]++;
        }
      }
    }
  }
  return matrice_duel;
}

t_mat_int_dyn
creation_matrice_int_depuis_char(t_mat_char_star_dyn *matrice_char) {
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

  t_mat_char_star_dyn mat_votes = lire_fichier_csv(nom_fichier);
  t_mat_int_dyn matrice_duels;
  DynamicList liste_candidat;
  initDynamicList(&liste_candidat);

  for (int i = 0; i < mat_votes.cols; i++) {
    add(&liste_candidat, mat_votes.data[0][i], CHAR_TYPE);
  }
  if (i) {

    if (strcmp(mat_votes.data[0][0], "ID votant") == 0) {
      matrice_duels = creation_matrice_int_depuis_vote_ballots(&mat_votes);
    } else {
      matrice_duels = creation_matrice_int_depuis_char(&mat_votes);
    }
  }

  if (d) {

    matrice_duels = creation_matrice_int_depuis_char(&mat_votes);

    /*t_graph graphe = creer_graphe(mat_duel, liste_candidat);

    confirmerGraphe(&graphe);

    afficherGraphe(graphe);*/
  }
  FILE *fichier = stdout;
  
  if (param_o != NULL) {
    fichier = fopen(param_o,"w"); // Ouverture du fichier en mode écriture ("w")

    if (fichier == NULL) {
      fichier = stdout;
    }
  }
  
  char *vainqueur_condor = NULL;
  char *vainqueur_uni1 = NULL;
  ;
  char *vainqueur_uni2 = NULL;
  ;
  char *vainqueur_jm = NULL;
  ;

  if (m) {
    if (strcmp(param_m, "uni1") == 0) {
      // vainqueur_uni1 = methodeUninominales(..., fichier);
    } else if (strcmp(param_m, "uni2") == 0) {
      // vainqueur_uni2 = methodeUninominales(..., fichier);
    } else if (strcmp(param_m, "cm") == 0) {
      vainqueur_condor = methodeCondorcetMinimax(matrice_duels, liste_candidat, fichier);
    } else if (strcmp(param_m, "cp") == 0) {
      // PAS IMPLÉMENTÉ :/
    } else if (strcmp(param_m, "cs") == 0) {
      // PAS IMPLÉMENTÉ :/
    } else if (strcmp(param_m, "jm") == 0) {
      // vainqueur_jm = jugementMajoritaire(..., fichier);
    } else if (strcmp(param_m, "all") == 0) {
      // vainqueur_uni1 = methodeUninominales(..., fichier);
      // vainqueur_uni2 = methodeUninominales(..., fichier);
      vainqueur_condor = methodeCondorcetMinimax(matrice_duels, liste_candidat, fichier);
      // vainqueur_jm = jugementMajoritaire(..., fichier);
    }
  }

  if (vainqueur_condor != NULL) {
    printf("\n\n\033[1;34m====================================================="
           "======\n");
    printf("=====================\033[1;31mCONDORCET "
           "MINIMAX\033[1;34m======================\n");
    printf("============================================================"
           "\n\n\033[0m");

    if (strcmp(vainqueur_condor, "NULL") == 0) {
      printf("Il n'y a pas de vainqueur par la méthode de Condorcet Minimax\n");
    } else {
      printf("Le vainqueur par la méthode de Condorcet Minimax est %s\n",
             vainqueur_condor);
    }
  }

  if (vainqueur_uni1 != NULL) {
    printf("\n\n\033[1;34m====================================================="
           "======\n");
    printf("=====================\033[1;31mUNINOMINAL 1 "
           "TOUR\033[1;34m======================\n");
    printf("============================================================"
           "\n\n\033[0m");

    /*TRAITEMENT AFFICHAGE*/
  }

  if (vainqueur_uni2 != NULL) {
    printf("\n\n\033[1;34m====================================================="
           "======\n");
    printf("=====================\033[1;31mUNINOMINAL 2 "
           "TOURS\033[1;34m======================\n");
    printf("============================================================"
           "\n\n\033[0m");

    /*TRAITEMENT AFFICHAGE*/
  }

  if (vainqueur_jm != NULL) {
    printf("\n\n\033[1;34m====================================================="
           "======\n");
    printf("=====================\033[1;31mJUGEMENT "
           "MAJORITAIRE\033[1;34m======================\n");
    printf("============================================================"
           "\n\n\033[0m");

    /*TRAITEMENT AFFICHAGE*/
  }

  free(nom_fichier);
  return 0;
}
