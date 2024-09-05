#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototypes des fonctions
void afficherMotDePasseTrouve(const char *user, const char *password);
void afficherUtilisateurInexistant(const char *user);
void extraireUser(const char *data, char *user);
int trouverMotDePasse(FILE *file, const char *user, char *password);
void ecrireUserDansFichier(const char *user);