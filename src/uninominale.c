#define _DEFAULT_SOURCE
#define _SVID_SOURCE
#include "uninominale.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define COLOR_ORANGE "\x1b[38;5;208m"
#define COLOR_RESET "\x1b[0m"

/**
 * \brief Trouve le vainqueur avec la méthode uninominale.
 *
 * Cette fonction identifie le candidat vainqueur en utilisant la méthode uninominale,
 * où la note la plus basse est considérée comme la meilleure.
 *
 * \param[in] mat_votes La matrice des votes, représentant les évaluations de chaque votant pour chaque candidat.
 * \return Le nom du candidat vainqueur.
 *
 * \note La fonction suppose que les votes sont stockés dans la matrice, avec les noms de candidats
 * commençant à la colonne 4 et les votes correspondants commençant à la ligne 1.
 *
 * \remarks La fonction alloue de la mémoire pour stocker les scores intermédiaires et le nom du vainqueur,
 * assurez-vous de libérer correctement cette mémoire après utilisation.
 */
char* trouver_vainqueur(t_mat_char_star_dyn *mat_votes) {
	int nb_candidats = mat_votes->cols - 4;

	int *scores = (int *)malloc(nb_candidats * sizeof(int));
	for (int i = 0; i < nb_candidats; ++i) {
		scores[i] = 0;
	}

	for (int row = 1; row < mat_votes->rows; ++row) {
		for (int col = 4; col < mat_votes->cols; ++col) {
			int vote = atoi(mat_votes->data[row][col]);
			if (vote > 0) {
				scores[col - 4] += vote;
			}
		}
	}
	int max_score = scores[0];
	int index_winner = 0;

	for (int i = 1; i < nb_candidats; ++i) {
		if (scores[i] > max_score) {
			max_score = scores[i];
			index_winner = i;
		}
	}
	char *vainqueur = strdup(mat_votes->data[0][index_winner + 4]);
	free(scores);
	return vainqueur;
}

/**
 * \brief Calcule le score du candidat gagnant avec la méthode uninominale.
 *
 * Cette fonction calcule le score du candidat gagnant en pourcentage, en utilisant la méthode uninominale.
 * Le score est déterminé en considérant la note la plus basse comme la meilleure, et en comptant le nombre de votants
 * ayant donné leur vote au candidat gagnant.
 *
 * \param[in] mat_votes La matrice des votes, représentant les évaluations de chaque votant pour chaque candidat.
 * \param[in] vainqueur Le nom du candidat gagnant.
 * \return Le score en pourcentage du candidat gagnant.
 *
 * \note La fonction suppose que les votes sont stockés dans la matrice, avec les noms de candidats
 * commençant à la colonne 4 et les votes correspondants commençant à la ligne 1.
 *
 * \remarks La fonction utilise l'algorithme pour trouver le vote le plus bas, et compte les votants qui ont voté
 * pour le candidat gagnant.
 *
 * \warning Assurez-vous que le candidat gagnant passé en paramètre correspond à un candidat présent dans la matrice,
 * sinon les résultats peuvent être imprévisibles.
 */
int calculer_score(t_mat_char_star_dyn *mat_votes, char *vainqueur) {
	int nb_votants = mat_votes->rows - 1;
	int index_winner = -1;
	for (int i = 4; i < mat_votes->cols; ++i) {
		if (strcmp(mat_votes->data[0][i], vainqueur) == 0) {
			index_winner = i;
			break;
		}
	}
	int total_winner_votes = 0;
	for (int row = 1; row < mat_votes->rows; ++row) {
		int min_vote = atoi(mat_votes->data[row][4]);
		int index = 4;
		for (int col = 5; col < mat_votes->cols; ++col) {
			if (atoi(mat_votes->data[row][col]) < min_vote || (atoi(mat_votes->data[row][col]) == min_vote && col == index_winner)) {
				min_vote = atoi(mat_votes->data[row][col]);
				index = col;
			}
		}
		if (index == index_winner) {
			total_winner_votes += 1;
		}
	}
	int score = (total_winner_votes * 100) / nb_votants;
	return score;
}

/**
 * \brief Effectue un scrutin uninominal à un tour et renvoie les résultats.
 *
 * Cette fonction réalise un scrutin uninominal à un tour en utilisant la méthode uninominale,
 * trouve le vainqueur et calcule son score en pourcentage. Les résultats sont stockés dans une structure
 * de données t_resultat_uninominale.
 *
 * \param[in] mat_votes La matrice des votes, représentant les évaluations de chaque votant pour chaque candidat.
 * \return Une structure t_resultat_uninominale contenant le nombre de candidats, le nombre de votants, le vainqueur
 * et son score en pourcentage.
 *
 * \note La fonction suppose que les votes sont stockés dans la matrice, avec les noms de candidats
 * commençant à la colonne 4 et les votes correspondants commençant à la ligne 1.
 *
 * \warning Assurez-vous que la matrice de votes est correctement formatée pour représenter un scrutin uninominal à un tour.
 */
 t_resultat_uninominale resultat;
char* uninominale_un_tour(t_mat_char_star_dyn *mat_votes,FILE *fichier) {
	fprintf(fichier, "[Uninominale] Début du scrutin à un tour\n");
	char *vainqueur = trouver_vainqueur(mat_votes);

	resultat.nb_candidats = mat_votes->cols - 4;
	resultat.nb_votants = mat_votes->rows - 1;
	resultat.vainqueur = strdup(vainqueur);
	resultat.score = calculer_score(mat_votes, vainqueur);
	fprintf(fichier, "[Uninominale 1 Tour] Fin du scrutin\n");
	fprintf(fichier, COLOR_ORANGE"Mode de scrutin : Uninominale 1 tour, %d candidats, %d votants, vainqueur = %s, score = %d pourcents",resultat.nb_candidats,resultat.nb_votants,resultat.vainqueur ,resultat.score);
	return resultat.vainqueur;
}

char* uninominale_deux_tours(t_mat_char_star_dyn *mat_votes,FILE *fichier) {
	fprintf(fichier, "[Uninominale] Début du scrutin à deux tours\n");
	FILE *fichierSortie = fopen("SortieUni1.txt", "w");
    if (fichierSortie == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
    }
	uninominale_un_tour(mat_votes,fichierSortie);
	if (resultat.score>49) {
		fprintf(fichier, "[Uninominale 2 Tours] Fin du scrutin (2ème tour) : un candidat a obtenu la majoritée\n");
		fprintf(fichier, COLOR_ORANGE"Mode de scrutin : Uninominale 2 tour, %d candidats, %d votants, vainqueur = %s, score = %d pourcents",resultat.nb_candidats,resultat.nb_votants,resultat.vainqueur ,resultat.score);
		return resultat.vainqueur;
	}
	int nb_candidats=resultat.nb_candidats;
	int nb_votants=resultat.nb_votants;
	float score_candidat1=0;
	float score_candidat2=0;
	int vainqueur1=0;
	float tab[nb_candidats];

	for (int i = 0; i < nb_candidats; i++) {
		tab[i]=0;
		for (int j = 0; j < nb_votants; j++) {
			tab[i]+=atoi(mat_votes->data[j+1][i+4]);
		}
		if (tab[i]>score_candidat1) {
			score_candidat2=score_candidat1;
			score_candidat1=tab[i];
			vainqueur1=i;
		}
		else if (score_candidat2 < tab[i] && tab[i] < score_candidat1) {
			score_candidat2=tab[i];
		}
	}
	char* vainqueur=mat_votes->data[0][vainqueur1+4];
	float score_vaiqueur=(score_candidat1/(score_candidat1+score_candidat2))*100;
	fprintf(fichier, COLOR_ORANGE"Mode de scrutin : Uninominale 2 tour, %d candidats, %d votants, vainqueur = %s, score = %f pourcents",resultat.nb_candidats,resultat.nb_votants,vainqueur ,score_vaiqueur);
	return vainqueur;
}

char* methode_uninomale(t_mat_char_star_dyn *votes, bool deuxTours, FILE *fichier) {
	char* resultat;

	if (deuxTours) {
		resultat = uninominale_deux_tours(votes,fichier);
	} else {
		resultat = uninominale_un_tour(votes,fichier);
	}

	return resultat;
}
