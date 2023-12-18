#define _DEFAULT_SOURCE
#define _SVID_SOURCE
#include "uninominale.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



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

	// initialiser le tableau des scores
	int *scores = (int *)malloc(nb_candidats * sizeof(int));
	for (int i = 0; i < nb_candidats; ++i) {
		scores[i] = 0;
	}

	// parcourir les votes et maj les scores
	for (int row = 1; row < mat_votes->rows; ++row) {
		for (int col = 4; col < mat_votes->cols; ++col) {
			int vote = atoi(mat_votes->data[row][col]);
			if (vote > 0) {
				scores[col - 4] += vote;
			}
		}
	}

	// trouver le candidat avec le score le plus bas
	int min_score = scores[0];
	int index_winner = 0;

	for (int i = 1; i < nb_candidats; ++i) {
		if (scores[i] < min_score) {
			min_score = scores[i];
			index_winner = i;
		}
	}

	// récupérer le nom du vainqueur
	char *vainqueur = strdup(mat_votes->data[0][index_winner + 4]);

	// libérer la mémoire allouée pour les scores
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

	// trouver l'index du candidat gagnant
	int index_winner = -1;
	for (int i = 4; i < mat_votes->cols; ++i) {
		if (strcmp(mat_votes->data[0][i], vainqueur) == 0) {
			index_winner = i;
			break;
		}
	}

	// calculer le score en pourcentage
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
char* uninominale_un_tour(t_mat_char_star_dyn *mat_votes,FILE *fichier) {
	t_resultat_uninominale resultat;

	// trouver le vainqueur
	char *vainqueur = trouver_vainqueur(mat_votes);

	// remplir la structure de résultat
	resultat.nb_candidats = mat_votes->cols - 4;
	resultat.nb_votants = mat_votes->rows - 1;
	resultat.vainqueur = strdup(vainqueur);
	resultat.score = calculer_score(mat_votes, vainqueur); // calculer le score
	fprintf(fichier, "UNINOMINALE 1 tour : %s\n",resultat.vainqueur );
	return resultat.vainqueur;
}

// Fonction pour le scrutin uninominal à deux tours
char* uninominale_deux_tours(t_mat_char_star_dyn *mat_votes,FILE *fichier) {
	char* resultat1 = uninominale_un_tour(mat_votes,fichier);
	fprintf(fichier, "UNINOMINALE 1 tour : %s\n",resultat1 );
	return resultat1;
	/*******************************************
	t_resultat_uninominale resultat;
	int nb_votants = mat_votes->rows - 1;

	// Premier tour
	t_resultat_uninominale premier_tour_resultat = uninominale_un_tour(mat_votes);
	char *premier_tour_vainqueur = strdup(premier_tour_resultat.vainqueur);

	// Deuxième tour virtuel
	char *second_tour_candidat1 = strdup(premier_tour_vainqueur);
	char *second_tour_candidat2 = trouver_deuxieme_tour_candidat(mat_votes, second_tour_candidat1);

	// Créer une matrice de votes pour le deuxième tour
	t_mat_char_star_dyn mat_votes_tour2;
	init_mat_char_star_dyn(&mat_votes_tour2, mat_votes->rows, mat_votes->cols);

	for (int row = 0; row < mat_votes->rows; ++row) {
		mat_votes_tour2.data[row][0] = strdup(mat_votes->data[row][0]);  // Copie ID votant
		mat_votes_tour2.data[row][1] = strdup(mat_votes->data[row][1]);  // Copie Date
		mat_votes_tour2.data[row][2] = strdup(mat_votes->data[row][2]);  // Copie Code vote
		mat_votes_tour2.data[row][3] = strdup(mat_votes->data[row][3]);  // Copie Votant
		mat_votes_tour2.data[row][4] = strdup(mat_votes->data[row][getIndexFromName(mat_votes, second_tour_candidat1)]);
		mat_votes_tour2.data[row][5] = strdup(mat_votes->data[row][getIndexFromName(mat_votes, second_tour_candidat2)]);
	}

	// Deuxième tour réel
	t_resultat_uninominale deuxieme_tour_resultat = uninominale_un_tour(&mat_votes_tour2);

	// Remplir la structure de résultat
	resultat.nb_candidats = mat_votes->cols - 4;
	resultat.nb_votants = nb_votants;
	resultat.vainqueur = strdup(deuxieme_tour_resultat.vainqueur);
	resultat.score = deuxieme_tour_resultat.score;

	// Libérer la mémoire allouée
	free_mat_char_star_dyn(&mat_votes_tour2);
	free(premier_tour_vainqueur);
	free(second_tour_candidat1);
	free(second_tour_candidat2);

	return resultat;
	****************************************************/
}



// fonction pour afficher les résultats d'un scrutin uninominal
// void afficher_resultat_uninominal(t_resultat_uninominale resultat, bool deuxTours) {
// 	printf("Mode de scrutin : uninominal %s, %d candidats, %d votants, vainqueur = %s, score = %d%%\n",
// 		   (deuxTours) ? "à deux tours" : "à un tour", resultat.nb_candidats, resultat.nb_votants,
// 		   resultat.vainqueur, resultat.score);
// }


// fonction principale pour la méthode uninominale
char* methode_uninomale(t_mat_char_star_dyn *votes, bool deuxTours, FILE *fichier) {
	char* resultat;

	if (deuxTours) {
		resultat = uninominale_deux_tours(votes,fichier);
	} else {
		resultat = uninominale_un_tour(votes,fichier);
	}

	return resultat;
}
