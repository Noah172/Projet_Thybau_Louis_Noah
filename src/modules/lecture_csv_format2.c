#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture_csv_format2.h"

t_vote_format2_data lire_fichier_csv_format2(const char *nom_fichier) {
    t_vote_format2_data votes_format2;
    votes_format2.noms_candidats = NULL;
    votes_format2.nb_candidats = 0;
    votes_format2.votes = NULL;
    votes_format2.nb_votes = 0;

    // Ouvrir le fichier en mode lecture
    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    // Lire la première ligne pour obtenir les noms des candidats
    char ligne_noms[1024];
    if (fgets(ligne_noms, sizeof(ligne_noms), fichier) != NULL) {
        char *token = strtok(ligne_noms, ",");

        // Ignorer les 4 premières colonnes
        for (int i = 0; i < 4; ++i) {
            token = strtok(NULL, ",");
        }

        while (token != NULL) {
            votes_format2.noms_candidats = realloc(votes_format2.noms_candidats, (votes_format2.nb_candidats + 1) * sizeof(char *));
            votes_format2.noms_candidats[votes_format2.nb_candidats] = strdup(token);

            token = strtok(NULL, ",");
            votes_format2.nb_candidats++;
        }
    }

    // Lire les lignes suivantes avec les votes
    char ligne[1024];
    votes_format2.votes = NULL;
    votes_format2.nb_votes = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        t_vote_format2 vote;
        vote.votes = malloc(votes_format2.nb_candidats * sizeof(int));

        char *token = strtok(ligne, ",");

        // Ignorer les 4 premières colonnes
        for (int i = 0; i < 4; ++i) {
            token = strtok(NULL, ",");
        }

        int i = 0;
        // Récupérer les votes pour chaque candidat
        while ((token != NULL) && (i < votes_format2.nb_candidats)) {
            sscanf(token, "%d", &vote.votes[i]);
            token = strtok(NULL, ",");
            i++;
        }

        // Ajouter le vote à la liste
        votes_format2.votes = realloc(votes_format2.votes, (votes_format2.nb_votes + 1) * sizeof(t_vote_format2));
        votes_format2.votes[votes_format2.nb_votes] = vote;
        votes_format2.nb_votes++;
    }

    // Fermer le fichier
    fclose(fichier);

    return votes_format2;
}


void afficher_vote_format2_data(t_vote_format2_data data) {
    printf("Nombre de candidats : %d\n", data.nb_candidats);

    printf("Noms des candidats : ");
    for (int i = 0; i < data.nb_candidats; ++i) {
        printf("%s -- ", data.noms_candidats[i]);
    }
    printf("\n");

    printf("Nombre de votes : %d\n", data.nb_votes);

    for (int i = 0; i < data.nb_votes; ++i) {
        printf("Vote %d:\n", i + 1);
        printf("ID votant : %d\n", data.votes[i].ID_votant);
        printf("Date : %s\n", data.votes[i].Date);
        printf("Code vote : %s\n", data.votes[i].Code_vote);
        printf("Votant : %s\n", data.votes[i].Votant);

        printf("Votes pour chaque candidat : ");
        for (int j = 0; j < data.nb_candidats; ++j) {
            printf("%d ", data.votes[i].votes[j]);
        }
        printf("\n\n");
    }
}
