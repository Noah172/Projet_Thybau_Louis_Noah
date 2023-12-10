#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int **data;
  int rows;
  int cols;
} t_mat_int_dyn;

typedef struct {
  char **candidats;
  int nb_candidats;
  char *vainqueur;
  int nb_votants;
  int score;
} t_resultat_uninominale;

t_mat_int_dyn init_mat_int_dyn(int rows, int cols) {
  t_mat_int_dyn mat;
  mat.data = (int **)malloc(rows * sizeof(int *));
  for (int i = 0; i < rows; ++i) {
    mat.data[i] = (int *)malloc(cols * sizeof(int));
  }
  mat.rows = rows;
  mat.cols = cols;
  return mat;
}

void free_mat_int_dyn(t_mat_int_dyn *mat) {
  for (int i = 0; i < mat->rows; ++i) {
    free(mat->data[i]);
  }
  free(mat->data);
}

t_resultat_uninominale init_resultat_uninominale(int nb_candidats) {
  t_resultat_uninominale resultat;
  resultat.candidats = (char **)malloc(nb_candidats * sizeof(char *));
  for (int i = 0; i < nb_candidats; ++i) {
    // Allouer de la mémoire pour le nom du candidat
    resultat.candidats[i] = (char *)malloc(
        100 * sizeof(char)); // Ajustez la taille selon vos besoins
    // Initialiser les noms des candidats si nécessaire
    strcpy(resultat.candidats[i], ""); // Chaîne vide par défaut
  }
  resultat.nb_candidats = nb_candidats;
  resultat.vainqueur = NULL; // Initialiser le nom du vainqueur si nécessaire
  resultat.nb_votants = 0;   // Initialiser le nombre de votants
  resultat.score = 0;        // Initialiser le score
  return resultat;
}

void free_resultat_uninominale(t_resultat_uninominale *resultat) {
  for (int i = 0; i < resultat->nb_candidats; ++i) {
    free(resultat->candidats[i]);
  }
  free(resultat->candidats);
  free(resultat->vainqueur);
}

t_resultat_uninominale uninominale_un_tour(const t_mat_int_dyn *mat_votes,
                                           int nb_candidats) {
  t_resultat_uninominale resultat = init_resultat_uninominale(nb_candidats);

  // Calculer le total des votes pour chaque candidat
  int *scores = (int *)malloc(nb_candidats * sizeof(int));
  for (int i = 0; i < nb_candidats; ++i) {
    scores[i] = 0;
    for (int j = 0; j < nb_candidats; ++j) {
      scores[i] += mat_votes->data[i][j];
    }
    resultat.nb_votants +=
        scores[i]; // Ajouté : mise à jour du nombre de votants
  }

  // Trouver le candidat avec le score le plus élevé
  int max_score = -1;
  int vainqueur_index = -1;
  for (int i = 0; i < nb_candidats; ++i) {
    if (scores[i] > max_score) {
      max_score = scores[i];
      vainqueur_index = i;
    }
  }

  // Enregistrer le vainqueur dans la structure de résultat
  if (vainqueur_index != -1) {
    resultat.vainqueur = strdup(resultat.candidats[vainqueur_index]);
    resultat.score =
        (max_score * 100) /
        resultat.nb_votants; // Ajouté : calcul du score en pourcentage
  }

  free(scores);
  return resultat;
}

t_resultat_uninominale uninominale_deux_tours(const t_mat_int_dyn *mat_votes,
                                              int nb_candidats) {
  t_resultat_uninominale resultat = init_resultat_uninominale(nb_candidats);

  // Tableau pour stocker les scores après le premier tour
  int *scores_premier_tour = (int *)malloc(nb_candidats * sizeof(int));

  // Premier tour
  for (int i = 0; i < nb_candidats; ++i) {
    scores_premier_tour[i] = 0;
    for (int j = 0; j < nb_candidats; ++j) {
      scores_premier_tour[i] += mat_votes->data[i][j];
    }
    resultat.nb_votants +=
        scores_premier_tour[i]; // Ajouté : mise à jour du nombre de votants
  }

  // Trouver les deux candidats avec les scores les plus élevés
  int max_score1 = -1;
  int max_score2 = -1;
  int index_candidat1 = -1;
  int index_candidat2 = -1;

  for (int i = 0; i < nb_candidats; ++i) {
    if (scores_premier_tour[i] > max_score1) {
      max_score2 = max_score1;
      index_candidat2 = index_candidat1;

      max_score1 = scores_premier_tour[i];
      index_candidat1 = i;
    } else if (scores_premier_tour[i] > max_score2) {
      max_score2 = scores_premier_tour[i];
      index_candidat2 = i;
    }
  }

  // Second tour entre les deux candidats restants
  int score_candidat1 = 0;
  int score_candidat2 = 0;

  for (int i = 0; i < nb_candidats; ++i) {
    if (i != index_candidat1 && i != index_candidat2) {
      // Ajouter les votes pour le second tour
      score_candidat1 += mat_votes->data[i][index_candidat1];
      score_candidat2 += mat_votes->data[i][index_candidat2];
    }
  }

  // Déterminer le vainqueur du second tour
  if (score_candidat1 > score_candidat2) {
    resultat.vainqueur = strdup(resultat.candidats[index_candidat1]);
  } else {
    resultat.vainqueur = strdup(resultat.candidats[index_candidat2]);
  }

  resultat.score =
      ((score_candidat1 + score_candidat2) * 100) /
      resultat.nb_votants; // Ajouté : calcul du score en pourcentage

  free(scores_premier_tour);
  return resultat;
}

void afficher_resultat_uninominale(int tour, t_resultat_uninominale resultat) {
  printf("Mode de scrutin : uninominal à %d tour(s), %d candidat(s), %d "
         "votant(s), vainqueur = %s, score = %d%%\n",
         tour, resultat.nb_candidats, resultat.nb_votants, resultat.vainqueur,
         resultat.score);
}

int main() {
  // Exemple de matrice de votes (à adapter selon vos besoins)
  int votes[3][3] = {{5, 3, 2}, {2, 5, 3}, {3, 2, 5}};

  // Initialisation de la matrice dynamique
  t_mat_int_dyn mat_votes;
  mat_votes = init_mat_int_dyn(3, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      mat_votes.data[i][j] = votes[i][j];
    }
  }

  // Test de la méthode uninominale à un tour
  t_resultat_uninominale resultat_un_tour = uninominale_un_tour(&mat_votes, 3);
  afficher_resultat_uninominale(1, resultat_un_tour);
  free_resultat_uninominale(&resultat_un_tour);

  // Test de la méthode uninominale à deux tours
  t_resultat_uninominale resultat_deux_tours =
      uninominale_deux_tours(&mat_votes, 3);
  afficher_resultat_uninominale(2, resultat_deux_tours);
  free_resultat_uninominale(&resultat_deux_tours);

  // Libération de la mémoire
  free_mat_int_dyn(&mat_votes);

  return 0;
}
