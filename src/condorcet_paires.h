#ifndef CONDORCETPAIRS_H
#define CONDORCETPAIRS_H

#include "graph.h"

typedef struct {
    int candidat1;
    int candidat2;
    int votesCandidat1;
    int votesCandidat2;
} Paire;

typedef struct {
    Paire *paires;
    int nbPaires;
} ResultatPaires;

ResultatPaires initialiserResultatPaires(int nbCandidats);

void ajouterPaire(ResultatPaires *resultat, int candidat1, int candidat2, int votesCandidat1, int votesCandidat2);

char *condorcetPaires(ResultatPaires *resultat, FILE *fichier);

#endif
