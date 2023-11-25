/// \file test_sha.c
/// \brief fichier pour montrer comment on utilise la fonction sha256ofString
/// compiler avec : gcc test_sha.c sha256.c sha256_utils.c -o test_sha
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.h"
#include "sha256_utils.h"
#define STRLONG 30


char* creerHashCode(char* mess){
	int bufferSize = SHA256_BLOCK_SIZE;
	char* hashRes = malloc(STRLONG*sizeof(char)*4);; // contiendra le hash en hexadécimal
	char * item = malloc(STRLONG*sizeof(char)*2); // contiendra la chaîne à hasher
	strcpy(item,mess); // c'est elle
	sha256ofString((BYTE *)item,hashRes); // hashRes contient maintenant le hash de l'item
	int long_hash = strlen(hashRes); // sa longueur en caractères hexadécimaux
	return hashRes;
}
