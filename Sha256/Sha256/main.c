#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "test_sha.h"
#define STRLONG 30


int balise_i = 0;
int balise_d = 0;

void check_balise(){
  if(balise_i && balise_d){
    fprintf(stderr, "Balise -i et -d incompatible\n");
    exit(EXIT_FAILURE);
  }
}

void calculerHashCode(char* arg1, char* arg2, char* arg3){

  size_t taille_message = strlen(arg1) + strlen(arg2) + strlen(arg3) + 1;
  char *message = (char *)malloc(taille_message*2);
  strcpy(message, arg1);
  strcat(message, arg2);
  strcat(message, arg3);

  char* hashCode = creerHashCode(message);
  printf("arg1 : %s, arg2 : %s, arg3 : %s, mess : %s\n", arg1, arg2, arg3, message);
  printf("Le hash code : %s\n", hashCode);

  char* nomFichier = "csv/VoteCondorcet.csv";
  FILE *fichier = fopen(nomFichier, "r");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier : %s\n", nomFichier);
        exit(EXIT_FAILURE);
    }

    int num_ligne = 1;
    int trouve = 0;
    char ligne[1024];
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
      if (strstr(ligne, hashCode) != NULL) {
        printf("Lla ligne correspondante au hashé '%s' est la numéro %d\n", hashCode, num_ligne);
        trouve = 1;
      }
      else
      {
        num_ligne++;
      }
    }
    if(trouve == 0)
    {
      printf("Hashé pas trouvé :/\n");
    }

    // Fermer le fichier
    fclose(fichier);

}


int main(int argc, char *argv[]) {

  if(argc < 2){
    fprintf(stderr, "Il faut au moins 1 balise\n");
    exit(EXIT_FAILURE);
  }



  int option;

  while ((option = getopt(argc, argv, "ido:m:")) != -1) {

    if(option == 'i') {
      balise_i = 1;
      check_balise();
      printf("Le fichier csv est le resultat d'un vote\n");
      if(argc >= 4){
        char* arg1 = argv[1];
        char* arg2 = argv[2];
        char* arg3 = argv[3];
        calculerHashCode(arg1, arg2, arg3);
      }
    }

    if(option == 'd') {
      balise_d = 1;
      check_balise();
      printf("Le fichier csv est une matrice de duet\n");
      printf("Désactive les parametres uni1 et uni2 de la balise -m\n");
    }


    if(option == 'o') {
      printf("Le fichier donné juste après sera traité comme un fichier de log\n");
      printf("NOM du fichier : %s\n", optarg);
    }
    if(option == 'm') {
      printf("Applique la/les méthodes de scrutins donnée.s juste après\n");
      printf("NOM du fichier : %s\n", optarg);
    }

  }
  return 0;
}
