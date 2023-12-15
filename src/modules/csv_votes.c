#define _DEFAULT_SOURCE
#define _SVID_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types.h"  // Assurez-vous d'inclure votre fichier types.h ici

// Fonction pour initialiser la structure t_votes
t_votes *initialiserVotes(int nb_votants, int nb_candidats) {
    t_votes *votes = malloc(sizeof(t_votes));
    if (votes == NULL) {
        perror("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }

    votes->votants = malloc(nb_votants * sizeof(t_votants *));
    if (votes->votants == NULL) {
        perror("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nb_votants; i++) {
        votes->votants[i] = malloc(sizeof(t_votants));
        if (votes->votants[i] == NULL) {
            perror("Erreur d'allocation de mémoire");
            exit(EXIT_FAILURE);
        }
        votes->votants[i]->id = i + 1;  // Id des votants, commençant à 1
        votes->votants[i]->vote = malloc(nb_candidats * sizeof(int));
        if (votes->votants[i]->vote == NULL) {
            perror("Erreur d'allocation de mémoire");
            exit(EXIT_FAILURE);
        }
    }
    votes->candidats = malloc(nb_candidats * sizeof(char *));
    if (votes->candidats == NULL) {
        perror("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }

    votes->nb_candidats = nb_candidats;
    votes->nb_votants = nb_votants;

    return votes;
}

// Fonction pour libérer la mémoire allouée pour la structure t_votes
void libererVotes(t_votes *votes) {
    for (int i = 0; i < votes->nb_votants; i++) {
        free(votes->votants[i]->vote);
        free(votes->votants[i]);
    }
    free(votes->votants);
    free(votes);
}

// Fonction pour lire les votes depuis un fichier CSV
t_votes *lireVotesDepuisCSV(const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur d'ouverture du fichier");
        exit(EXIT_FAILURE);
    }


    // Compter le nombre de votants et de candidats
    int nb_votants = 0;
    int nb_candidats = 0;
    char ligne[256];

    if (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        // Supprimer le retour à la ligne de la fin de la ligne
        ligne[strcspn(ligne, "\n")] = '\0';

        // Compter le nombre de virgules pour obtenir le nombre de candidats
        for (size_t i = 0; i < strlen(ligne); i++) {
            if (ligne[i] == ',') {
                nb_candidats++;
            }
        }

        // Le nombre de votants est le nombre de lignes restantes dans le fichier
        while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
            nb_votants++;
        }
    }

    // Retourner au début du fichier
    rewind(fichier);

    // Initialiser la structure t_votes
    t_votes *votes = initialiserVotes(nb_votants, nb_candidats);

    // Lire les données depuis le fichier CSV
    for (int i = 0; i < nb_votants+1; i++) {
        if (fgets(ligne, sizeof(ligne), fichier) != NULL) {
            // Supprimer le retour à la ligne de la fin de la ligne
            ligne[strcspn(ligne, "\n")] = '\0';
            if (i==0) {

                char* token = strtok(ligne,",");
                for (int j = 0; j < 4; j++) {
                    token = strtok(NULL, ",");
                }
                int x=0;
                while (token != NULL) {
                    // Affichez chaque token
                    votes->candidats[x] = strdup(token);
                    x+=1;
                    token = strtok(NULL, ",");
                    // Obtenez le prochain token

                }
            }else{
                printf("Ligne lue : %s\n", ligne);
                // Utiliser sscanf pour extraire les valeurs du CSV
                sscanf(ligne, "%*d,%*[^,],%*[^,],%*[^,],%d,%d,%d,%d,%d",
                       &votes->votants[i-1]->vote[0],
                       &votes->votants[i-1]->vote[1],
                       &votes->votants[i-1]->vote[2],
                       &votes->votants[i-1]->vote[3],
                       &votes->votants[i-1]->vote[4]);
            }


        }
    }


    votes->nb_candidats-=3;
    fclose(fichier);

    return votes;
}

void afficherVotes(t_votes *votes) {
    printf("Nombre de candidats : %d\n", votes->nb_candidats);
    printf("Noms des candidats : ");
    for (int i = 0; i < votes->nb_candidats; i++) {
        printf("%s - ", votes->candidats[i]);
    }
    printf("\n");
    printf("Nombre de votants : %d\n", votes->nb_votants);

    for (int i = 0; i < votes->nb_votants; i++) {
        printf("\nVotant %d:\n", votes->votants[i]->id);
        printf("Votes: ");
        for (int j = 0; j < votes->nb_candidats; j++) {
            printf("%d ", votes->votants[i]->vote[j]);
        }
        printf("\n");
    }
}
