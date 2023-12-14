#ifndef LECTURE_CSV_FORMAT2_H
#define LECTURE_CSV_FORMAT2_H

typedef struct {
    int ID_votant;
    char Date[30];
    char Code_vote[20];
    char Votant[20];
    int *votes;  // tableau dynamique pour les votes
} t_vote_format2;

typedef struct {
    t_vote_format2 *votes;
    char **noms_candidats;  // tableau dynamique pour les noms des candidats
    int nb_votes;
    int nb_candidats;
} t_vote_format2_data;

t_vote_format2_data lire_fichier_csv_format2(const char *nom_fichier);
void afficher_vote_format2_data(t_vote_format2_data data);

#endif
