#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Prototypes des fonctions
void InscriptionReussie();
void LoginUtilise();
int verifierUtilisateur(FILE *file, const char *user, const char *password);
void ajouterUtilisateur(FILE *file, const char *user, const char *password);
void extraireParametres(char *data, char *user, char *password);
