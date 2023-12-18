#include "condorcetpaires.h"
#include "graph.h"  // Assurez-vous d'avoir votre propre implementation de graph.h
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

ResultatPaires initialiserResultatPaires(int nbCandidats) {
    ResultatPaires resultat;
    resultat.paires = (Paire *)malloc(nbCandidats * (nbCandidats - 1) / 2 * sizeof(Paire));
    resultat.nbPaires = 0;
    return resultat;
}

void ajouterPaire(ResultatPaires *resultat, int candidat1, int candidat2, int votesCandidat1, int votesCandidat2) {
    Paire nouvellePaire;
    nouvellePaire.candidat1 = candidat1;
    nouvellePaire.candidat2 = candidat2;
    nouvellePaire.votesCandidat1 = votesCandidat1;
    nouvellePaire.votesCandidat2 = votesCandidat2;

    resultat->paires[resultat->nbPaires++] = nouvellePaire;
}

char *condorcetPaires(ResultatPaires *resultat, FILE *fichier) {
    Graph *graphe = createGraph(resultat->nbPaires);
    for (int i = 0; i < resultat->nbPaires; ++i) {
        Paire paire = resultat->paires[i];
        if (paire.votesCandidat1 > paire.votesCandidat2) {
            addEdge(graphe, paire.candidat1, paire.candidat2);
        } else {
            addEdge(graphe, paire.candidat2, paire.candidat1);
        }
    }

    for (int i = 0; i < graphe->numNodes; ++i) {
        Sommet *currentSommet = graphe->sommets[i];
        // Faire quelque chose avec le sommet
    }

    // Libérer la mémoire du graphe
    freeGraph(graphe);

    return NULL;
}
