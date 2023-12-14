#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modules/lecture_csv_format2.h"

#define NB_MENTIONS 6  // Mention de 0 à 5

// Structure pour stocker les résultats du jugement majoritaire
typedef struct {
    int *points;  // Tableau des points de chaque candidat
} t_resultat_majoritaire;

// Fonction pour initialiser la structure des résultats du jugement majoritaire
t_resultat_majoritaire initialiser_resultat_majoritaire(int nb_candidats) {
    t_resultat_majoritaire resultat;
    resultat.points = calloc(nb_candidats, sizeof(int));
    return resultat;
}

// Fonction pour effectuer le jugement majoritaire
t_resultat_majoritaire jugement_majoritaire(t_vote_format2_data data) {
    int nb_candidats = data.nb_candidats;
    int nb_votes = data.nb_votes;

    // Initialiser la structure des résultats
    t_resultat_majoritaire resultat = initialiser_resultat_majoritaire(nb_candidats);

    // Parcourir les votes
    for (int i = 0; i < nb_votes; ++i) {
        t_vote_format2 vote = data.votes[i];

        // Attribution des points selon les mentions
        for (int j = 0; j < nb_candidats; ++j) {
            int mention = vote.votes[j];
            resultat.points[j] += NB_MENTIONS - mention;
        }
    }

    return resultat;
}

// Fonction pour afficher les résultats du jugement majoritaire
void afficher_resultat_majoritaire(t_resultat_majoritaire resultat, t_vote_format2_data data) {
    int nb_candidats = data.nb_candidats;

    printf("Résultat du jugement majoritaire :\n");

    for (int i = 0; i < nb_candidats; ++i) {
        printf("Candidat %s : %d points\n", data.noms_candidats[i], resultat.points[i]);
    }

    // Trouver le candidat avec le plus de points
    int max_points = resultat.points[0];
    int index_max = 0;

    for (int i = 1; i < nb_candidats; ++i) {
        if (resultat.points[i] > max_points) {
            max_points = resultat.points[i];
            index_max = i;
        }
    }

    printf("Le gagnant est : %s\n", data.noms_candidats[index_max]);
}

int jugementMajoritaire() {
    // Remplacez "votre_fichier.csv" par le nom de votre fichier CSV
    t_vote_format2_data data = lire_fichier_csv_format2("fich_tests/vote10");

    // Effectuer le jugement majoritaire
    t_resultat_majoritaire resultat = jugement_majoritaire(data);

    // Afficher les résultats
    afficher_resultat_majoritaire(resultat, data);

    // Libérer la mémoire
    free(resultat.points);
    for (int i = 0; i < data.nb_candidats; ++i) {
        free(data.noms_candidats[i]);
    }
    free(data.noms_candidats);
    for (int i = 0; i < data.nb_votes; ++i) {
        free(data.votes[i].votes);
    }
    free(data.votes);

    return 0;
}
