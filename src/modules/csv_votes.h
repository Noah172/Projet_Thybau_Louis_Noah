#ifndef CSV_VOTE_H
#define CSV_VOTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types.h"

// Fonction pour initialiser la structure t_votes
t_votes *initialiserVotes(int nb_votants, int nb_candidats);

// Fonction pour libérer la mémoire allouée pour la structure t_votes
void libererVotes(t_votes *votes);

// Fonction pour lire les votes depuis un fichier CSV
t_votes *lireVotesDepuisCSV(const char *nomFichier);

// Fonction pour afficher les votes
void afficherVotes(t_votes *votes);

#endif // CSV_VOTE_H
