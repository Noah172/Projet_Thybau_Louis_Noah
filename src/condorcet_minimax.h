#ifndef CONDORCETM_H
#define CONDORCETM_H

extern int taille_matrice;

int minimax(int votes[taille_matrice][taille_matrice]);
int condorcet_minimax(int votes[taille_matrice][taille_matrice]);
int methodeCondorcetMinimax();

#endif /* CONDORCET_H */
