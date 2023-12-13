#ifndef CONDORCET_H
#define CONDORCET_H

// Déclarer les fonctions
void condorcet(int nb_votant, int nb_candidat, int votes[nb_votant][nb_candidat], int *resultats);
int trouverVainqueur(int *resultats);
int methodeCondorcet();

#endif
