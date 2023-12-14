#include "lecture_csv.h"
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


t_mat_int_dyn lire_fichier_csv(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier CSV.\n");
        exit(EXIT_FAILURE);
    }

    // Comptez le nombre de lignes et de colonnes dans le fichier
    int rows = 0;
    int cols = 0;
    char ligne[1024];
    while (fgets(ligne, sizeof(ligne), fichier)) {
        rows++;
        int colonnes_actuelles = 0;
        char *token = strtok(ligne, ",");
        while (token) {
            colonnes_actuelles++;
            token = strtok(NULL, ",");
        }
        if (colonnes_actuelles > cols) {
            cols = colonnes_actuelles;
        }
    }

    // Retournez au début du fichier
    rewind(fichier);

    // Allouez la matrice d'entiers
    int **matrice = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrice[i] = (int *)malloc(cols * sizeof(int));
    }

    // Remplissez la matrice avec les données du fichier
    char buffer[1024];
    for (int i = 0; i < rows; i++) {
        if (fgets(buffer, sizeof(buffer), fichier)) {
            int colonne = 0;
            char *token = strtok(buffer, ",");
            while (token) {
                matrice[i][colonne] = atoi(token);
                colonne++;
                token = strtok(NULL, ",");
            }
        }
    }

    // Fermez le fichier
    fclose(fichier);

    // Créez et retournez la structure t_mat_int_dyn
    t_mat_int_dyn resultat;
    resultat.data = matrice;
    resultat.rows = rows;
    resultat.cols = cols;
    return resultat;
}

void afficherMatrice(t_mat_int_dyn *matrice) {
    for (int i = 0; i < matrice->rows; i++) {
        for (int j = 0; j < matrice->cols; j++) {
            printf("%d\t", matrice->data[i][j]);
        }
        printf("\n");
    }
}

void afficherMatriceInt(t_mat_int_dyn *matrice) {
  for (int i = 0; i < matrice->rows; i++) {
    for (int j = 0; j < matrice->cols; j++) {
      printf("%d\t", matrice->data[i][j]);
    }
    printf("\n");
  }
}
