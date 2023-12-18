// fich_tests/tests.c
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#include "../uninominale.h"
#include "../condorcet_minimax.h"
#include "../jugement_majoritaire.h"
#include "../modules/lecture_csv.h"
#include "../list.h"


#define COLOR_BLUE "\x1b[34m"  // Code ANSI pour la couleur bleue
#define COLOR_GREEN "\x1b[32m" // Code ANSI pour la couleur verte
#define COLOR_RED "\x1b[31m"   // Code ANSI pour la couleur rouge
#define COLOR_RESET "\x1b[0m"
int compteur = 0;

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

t_mat_int_dyn creation_matrice_int_depuis_vote_ballots(t_mat_char_star_dyn *mat_votes) {
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

void afficher_resultat_test(const char *nom_test, const char *fichier_csv, const char *vainqueur_attendu, const char *vainqueur_obtenu, int reussi) {
    printf("\n{Test} : |%s|", nom_test);
    printf(" avec Fichier CSV : %s\n", fichier_csv);
    if (reussi) {
        compteur+=1;
        printf(COLOR_GREEN "                          [RÉUSSI]\n" COLOR_RESET);
    } else {
        printf(COLOR_RED "                          ÉCHOUÉ\n" COLOR_RESET);
        printf(COLOR_RED "( Vainqueur attendu : %s )", vainqueur_attendu);
        printf(COLOR_RED "( Vainqueur obtenu : %s )"COLOR_RESET, vainqueur_obtenu);
    }
    printf("\n");
}

void test_uninominale_1_tour(char *fichier_csv, char *vainqueur_attendu) {
    FILE *fichierSortie = fopen("EtapesTests.txt", "w");
    if (fichierSortie == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
    }
    t_mat_char_star_dyn votes = lire_fichier_csv(fichier_csv);
    char *vainqueur = uninominale_un_tour(&votes,fichierSortie);
    afficher_resultat_test("UNINOMINALE 1 TOUR", fichier_csv, vainqueur_attendu, vainqueur, strcmp(vainqueur, vainqueur_attendu) == 0);
}

void test_uninominale_2_tours(char *fichier_csv, char *vainqueur_attendu) {
    FILE *fichierSortie = fopen("EtapesTests.txt", "w");
    if (fichierSortie == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
    }
    t_mat_char_star_dyn votes = lire_fichier_csv(fichier_csv);
    char *vainqueur = uninominale_deux_tours(&votes,fichierSortie);  // Remplacez uninominale_2_tours par le nom réel de votre fonction
    afficher_resultat_test("UNINOMINALE 2 TOURS", fichier_csv, vainqueur_attendu, vainqueur, strcmp(vainqueur, vainqueur_attendu) == 0);
}

void test_condorcet_minimax(char *fichier_csv, char *vainqueur_attendu) {
    FILE *fichierSortie = fopen("EtapesTests.txt", "w");
    if (fichierSortie == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
    }
    t_mat_char_star_dyn votes = lire_fichier_csv(fichier_csv);
    DynamicList liste_candidat;
    initDynamicList(&liste_candidat);
    t_mat_int_dyn matrice_duels;
    for (int i = 0; i < votes.cols; i++) {
      add(&liste_candidat, votes.data[0][i], CHAR_TYPE);
    }

    if (strcmp(votes.data[0][0], "ID votant") == 0) {
      matrice_duels = creation_matrice_int_depuis_vote_ballots(&votes);
    } else {
      matrice_duels = creation_matrice_int_depuis_char(&votes);
    }
    char *vainqueur = methodeCondorcetMinimax(matrice_duels,liste_candidat,fichierSortie);
    afficher_resultat_test("CONCORCET MINIMAX", fichier_csv, vainqueur_attendu, vainqueur, strcmp(vainqueur, vainqueur_attendu) == 0);
}

void test_jugement_majoritaire(char *fichier_csv,char *vainqueur_attendu) {
    FILE *fichierSortie = fopen("EtapesTests.txt", "w");
    if (fichierSortie == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
    }
    t_mat_char_star_dyn votes=lire_fichier_csv(fichier_csv);
    char *vainqueur = jugementMajoritaire(votes,fichierSortie);
    afficher_resultat_test("JUGEMENT MAJORITAIRE", fichier_csv, vainqueur_attendu, vainqueur, strcmp(vainqueur, vainqueur_attendu) == 0);
    fclose(fichierSortie);
}


int main() {
    // UNINOMINALE 1 TOUR
    test_uninominale_1_tour("fich_tests/vote10.csv", "Baba au rhum");
    test_uninominale_1_tour("fich_tests/vote100.csv", "Asterix");
    test_uninominale_1_tour("fich_tests/ballots_va.csv","A");

    // UNINOMINALE 2 TOURS
    test_uninominale_2_tours("fich_tests/vote10.csv", "Baba au rhum");
    test_uninominale_2_tours("fich_tests/vote100.csv", "Asterix");//ou Assurenceousrisque
    test_uninominale_2_tours("fich_tests/ballots_va.csv","A");

    // CONCORDET MINIMAX
    test_condorcet_minimax("fich_tests/vote10.csv", "Tarte à la fraise");
    test_condorcet_minimax("fich_tests/vote100.csv", "Astérix");
    test_condorcet_minimax("fich_tests/ballots_va.csv","A");
    test_condorcet_minimax("fich_tests/calcul1.csv","Z");
    test_condorcet_minimax("fich_tests/calcul2.csv","Y");
    test_condorcet_minimax("fich_tests/2012.csv","h");
    test_condorcet_minimax("fich_tests/wiki_paires.csv","A");

    //JUGEMENT MAJORITAIRE
    test_jugement_majoritaire("fich_tests/vote10.csv","Charlotte aux poires");
    test_jugement_majoritaire("fich_tests/vote100.csv","Abraracourcix");
    test_jugement_majoritaire("fich_tests/ballots_va.csv","B");


    printf(COLOR_GREEN"\n--------------------------------------------------------------------\n-----------------------------%d/16 RÉUSSIS---------------------------\n--------------------------------------------------------------------\n\n",compteur );
    return 0;
}
