#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "creation_graphe.h"
#include "condorcet_paires.h"
#include "list.h"

#define COLOR_ORANGE "\x1b[38;5;208m"
#define COLOR_RESET "\x1b[0m"

void findMaxDuel(Graph *graph, int *max, FILE *fichier) {
    int maxScore = -1;

    for (int i = 0; i < graph->numNodes; ++i) {
        for (int j = 0; j < graph->numNodes; ++j) {
            if (i != j) {
                int score = 0;
                for (int k = 0; k < graph->sommets[i]->nb_next; ++k) {
                    if (graph->sommets[i]->next[k] == graph->sommets[j]) {
                        score += graph->sommets[i]->next_value[k];
                    }
                }

                if (score > maxScore) {
                    maxScore = score;
                    max[0] = i;
                    max[1] = j;
                }
            }
        }
    }

    fprintf(fichier, "[Condorcet Paires] Maximum trouvé : candidat %d vs candidat %d\n", max[0], max[1]);
}

void eliminateCandidates(Graph *graph, int *max, FILE *fichier) {
    Graph *newGraph = createGraph();
    addNode(newGraph, graph->sommets[max[0]]->data);
    addNode(newGraph, graph->sommets[max[1]]->data);

    for (int i = 0; i < newGraph->numNodes; ++i) {
        Sommet *currentSommet = newGraph->sommets[i];

        for (int j = 0; j < graph->numNodes; ++j) {
            if (i != j) {
                for (int k = 0; k < graph->sommets[j]->nb_next; ++k) {
                    if (graph->sommets[j]->next[k] == graph->sommets[max[0]] ||
                        graph->sommets[j]->next[k] == graph->sommets[max[1]]) {
                        addEdge(currentSommet, graph->sommets[j]->next[k], graph->sommets[j]->next_value[k]);
                    }
                }
            }
        }
    }

    graph = newGraph;

    fprintf(fichier, "[Condorcet Paires] Élimination des candidats sauf %s et %s\n", graph->sommets[0]->data, graph->sommets[1]->data);
}

int condorcet_pairs(t_mat_int_dyn matrice, DynamicList liste_candidat, FILE *fichier, int nb_votants) {
    Graph *graph = createGraph();

    for (int i = 0; i < matrice.rows; ++i) {
        addNode(graph, get_char(&liste_candidat, i));

        for (int j = 0; j < matrice.cols; ++j) {
            if (matrice.data[i][j] > 0) {
                addEdge(graph->sommets[i], graph->sommets[j], matrice.data[i][j]);
            }
        }
    }

    fprintf(fichier, "[Condorcet Paires] Initialisation du graphe à partir de la matrice\n");

    int max[2];
    findMaxDuel(graph, max, fichier);

    if (max[0] == max[1]) {
        fprintf(fichier, "[Condorcet Paires] Égalité trouvée, il n'y a pas de vainqueur\n");
        return -1;
    } else {
        fprintf(fichier, "[Condorcet Paires] Duel entre %d et %d\n", max[0], max[1]);
        eliminateCandidates(graph, max, fichier);

        if (max[0] == max[1]) {
            fprintf(fichier, COLOR_ORANGE"Mode de scrutin : Condorcet Paires, %d candidats, %d votants, vainqueur =  %s\n\n", matrice.cols, nb_votants, get_char(&liste_candidat, max[0]));
            return max[0];
        } else {
            fprintf(fichier, "[Condorcet Paires] Égalité trouvée, il n'y a pas de vainqueur\n");
            return -1;
        }
    }
}

int CondorcetouPaires(t_mat_int_dyn matrice, DynamicList liste_candidat, FILE *fichier, int nb_votants) {
    DynamicList max;
    initDynamicList(&max);
    int index0 = 1;
    int index1 = 0;
    add(&max, &index0, INT_TYPE);
    add(&max, &index1, INT_TYPE);
    fprintf(fichier, "[Condorcet] Recherche du maximum de chaque duel\n");
    int taille_matrice = matrice.cols;
    for (int i = 0; i < taille_matrice; i++) {
        for (int j = 0; j < taille_matrice; j++) {
            if (matrice.data[get_int(&max, 0)][get_int(&max, 1)] <
                matrice.data[i][j]) {
                set_int(&max, 0, i);
                set_int(&max, 1, j);
            }
        }
    }

    fprintf(fichier, "Maximum %d\n", get_int(&max, 0));
    char *vainqueur = get_char(&liste_candidat, get_int(&max, 0));
    fprintf(fichier, "[Condorcet] Maximum trouvé : correspondant au candidat %s\n", vainqueur);
    fprintf(fichier, "[Condorcet] Recherche d'égalité\n");
    int c = 0;
    for (int i = 1; i < taille_matrice; i++) {
        for (int j = 0; j < taille_matrice; j++) {
            if (matrice.data[get_int(&max, 0)][get_int(&max, 1)] == matrice.data[i][j] && get_int(&max, 0) != i) {
                c++;
            }
        }
    }
    if (c > 0) {
        fprintf(fichier, "[Condorcet] Égalité trouvée, application de la méthode de Condorcet Paires\n");
        int resultat_condorcet_paires = condorcet_pairs(matrice, liste_candidat, fichier, nb_votants);
        return resultat_condorcet_paires;
    } else {
        fprintf(fichier, "[Condorcet] Pas d'égalité, la méthode de Condorcet peut départager les candidats\n");
        fprintf(fichier, COLOR_ORANGE"Mode de scrutin : Condorcet Paires, %d candidats, %d votants, vainqueur =  %s\n\n", matrice.cols, nb_votants, get_char(&liste_candidat, get_int(&max, 0)));
        return get_int(&max, 0);
    }
}
