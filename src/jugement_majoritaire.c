/* \file jugement_majoritaire.c
 * \brief Implémentation de la méthode de Jugement Majoritaire.
 *
 * Ce fichier contient l'implémentation de la méthode de Jugement Majoritaire,
 * une méthode de scrutin qui utilise des médianes pour déterminer le vainqueur.
 */
#include "jugement_majoritaire.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define COLOR_ORANGE "\x1b[38;5;208m"
#define COLOR_RESET "\x1b[0m"

/* \fn int compare(const void *a, const void *b)
 * \brief Fonction de comparaison pour le tri des valeurs.
 * \param[in] a Pointeur vers la première valeur.
 * \param[in] b Pointeur vers la deuxième valeur.
 * \return Différence entre les deux valeurs.
 */
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

/* \fn int calculerPourcentages(t_mat_char_star_dyn votes, int numCandidat, int mentionMajoritaire)
 * \brief Calcule les pourcentages de partisans et d'opposants pour un candidat donné.
 * \param[in] votes La matrice des votes.
 * \param[in] numCandidat Le numéro du candidat.
 * \param[in] mentionMajoritaire La mention considérée comme majoritaire.
 * \return Le pourcentage le plus élevé entre partisans et opposants.
 */
int calculerPourcentages(t_mat_char_star_dyn votes, int numCandidat,int mentionMajoritaire) {
    int nbVotants = votes.rows - 1;
    int partisans = 0;
    int opposants = 0;

    for (int i = 0; i < nbVotants; i++) {
        if (atoi(votes.data[i][numCandidat+4]) > mentionMajoritaire) {
            partisans++;
        } else if (atoi(votes.data[i][numCandidat+4]) < mentionMajoritaire) {
            opposants++;
        }

    }
    // printf("nbVotants : %d \n",nbVotants );
    // printf("Partisans : %d \n", partisans);
    // printf("opposants : %d\n\n",opposants );

    int pourcentagePlus = (double)partisans / nbVotants * 100;
    int pourcentageMoins = (double)opposants / nbVotants * 100;
    //
    // printf("pourcentagePlus : %d\n", pourcentagePlus);
    // printf("pourcentageMoins : %d\n", pourcentageMoins);
    if (pourcentagePlus<pourcentageMoins) {
        return pourcentageMoins;
    }
    return pourcentagePlus;
}


/* \fn char* jugementMajoritaire(t_mat_char_star_dyn votes, FILE *fichier)
 * \brief Applique la méthode de Jugement Majoritaire.
 * \param[in] votes La matrice des votes.
 * \param[in] fichier Le fichier de sortie pour enregistrer les résultats.
 * \return Le nom du vainqueur selon la méthode de Jugement Majoritaire.
 */
char* jugementMajoritaire(t_mat_char_star_dyn votes,FILE *fichier) {
    fprintf(fichier, "[JugementMajoritaire] Début du calcul\n");
    t_resultat_majoritaire resultat;
    int nb_candidats = votes.cols - 4; // Il semble que les colonnes 0 à 3 ne sont pas utilisées
    int nb_votants = votes.rows - 1;

    resultat.nb_candidats = nb_candidats;
    resultat.nb_votants = nb_votants;
    resultat.candidats = malloc(nb_candidats * sizeof(char *));
    resultat.notes = malloc(nb_candidats * sizeof(int));
    resultat.medianes = malloc(nb_candidats * sizeof(int));

    if (resultat.candidats == NULL || resultat.notes == NULL || resultat.medianes == NULL) {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nb_candidats; i++) {
        resultat.candidats[i] = votes.data[0][i + 4];
        resultat.notes[i] = 0;
    }
    fprintf(fichier, "[JugementMajoritaire] Listes des candidats créée\n");
    for (int i = 0; i < nb_candidats; i++) {
        int *valeurs = malloc(nb_votants * sizeof(int));
        if (valeurs == NULL) {
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < nb_votants; j++) {
            valeurs[j] = atoi(votes.data[j + 1][i + 4]);
        }

        qsort(valeurs, nb_votants, sizeof(int), compare);
        if (nb_votants % 2 == 1) {
            resultat.medianes[i] = valeurs[nb_votants / 2];
        } else {
            resultat.medianes[i] = (valeurs[nb_votants / 2 - 1] + valeurs[nb_votants / 2]) / 2;
        }

        free(valeurs);
    }
    fprintf(fichier, "[JugementMajoritaire] Listes des médianes créée\n");
    int index_gagnant = 0;
    for (int i = 1; i < nb_candidats; i++) {
        if (resultat.medianes[i] < resultat.medianes[index_gagnant]) {
            index_gagnant = i;
        }
        else if (resultat.medianes[i] == resultat.medianes[index_gagnant]) {
            int i_percent= calculerPourcentages(votes,i,resultat.medianes[i]);
            int index_gagnant_percent= calculerPourcentages(votes,index_gagnant,resultat.medianes[i]);
            index_gagnant = (i_percent > index_gagnant_percent) ? i : index_gagnant;


        }
    }
    fprintf(fichier, COLOR_ORANGE"Mode de scrutin : Jugement Majoritaire, %d candidats, %d votants, vainqueur =  %s\n\n",nb_candidats,nb_votants,resultat.candidats[index_gagnant] );

    return resultat.candidats[index_gagnant];
}
