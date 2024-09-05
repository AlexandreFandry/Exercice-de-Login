#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "confirm.h"
int main() {
    char *nom = NULL, *mdp = NULL, *data = NULL;
    char user[100];
    char password[100];
    FILE *file = NULL;
    int found = 0;

    // Affichage de l'en-tête HTML
    printf("content-text: text/html\n\n");

    // Extraction des paramètres de la chaîne de requête
    data = getenv("QUERY_STRING");
    if (data != NULL) {
        extraireParametres(data, user, password);
    }

    // Ouverture du fichier en lecture
    file = fopen("/home/mit/monHTML/donne.txt", "r");
    if (file == NULL) {
        printf("<h1>Erreur d'ouverture du fichier</h1>");
        return 1;
    }

    // Vérification si l'utilisateur existe déjà
    found = verifierUtilisateur(file, user, password);
    fclose(file);

    // Ouverture du fichier en écriture si l'utilisateur n'existe pas
    if (!found) {
        file = fopen("/home/mit/monHTML/donne.txt", "a");
        if (file == NULL) {
            printf("<h1>Erreur d'ouverture du fichier</h1>");
            return 1;
        }
        ajouterUtilisateur(file, user, password);
        fclose(file);
        InscriptionReussie();
    } else {
        LoginUtilise();
    }

    return 0;
}

void InscriptionReussie() {
    printf("<!DOCTYPE html><html lang=\"fr\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Inscription Réussie</title>");
    printf("<style>body {display: flex;justify-content: center;align-items: center;height: 100vh;margin: 0;background-color: #f0f8ff;overflow: hidden;position: relative;font-family: Arial, sans-serif;}");
    printf(".message {text-align: center;font-size: 2em;color: #4caf50;padding: 20px;border: 2px solid #4caf50;border-radius: 10px;background-color: #ffffff;box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);}");
    printf("@keyframes confetti {0%% { transform: translateY(0); }100%% { transform: translateY(100vh); }}.confetti {position: absolute;width: 5px;height: 10px;background: #ff5722;opacity: 0.8;animation: confetti 2s linear infinite;pointer-events: none;}");
    printf(".confetti:nth-child(2) {background: #ffc107;animation-duration: 2.5s;}.confetti:nth-child(3) {background: #4caf50;animation-duration: 3s;}.confetti:nth-child(4) {background: #2196f3;animation-duration: 3.5s;}.confetti:nth-child(5) {background: #9c27b0;animation-duration: 4s;}form{padding:20px;position:absolute;bottom:200px;border-radius:10px;}</style>");
    printf("</head><body><div class=\"message\">Inscription Réussie !</div><div class=\"confetti\" style=\"left: 10%%; animation-delay: 0s;\"></div><div class=\"confetti\" style=\"left: 30%%; animation-delay: 0.5s;\"></div><div class=\"confetti\" style=\"left: 50%%; animation-delay: 1s;\"></div><div class=\"confetti\" style=\"left: 70%%; animation-delay: 1.5s;\"></div><div class=\"confetti\" style=\"left: 90%%; animation-delay: 2s;\"></div>");
    printf("<form action=\"login.html\"><input type=\"submit\" value=\"se connecter maintenant\"></form></body></html>");
}

void LoginUtilise() {
    printf("<!DOCTYPE html><html lang=\"fr\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Login Déjà Utilisé</title><style>");
    printf("body {display: flex;justify-content: center;align-items: center;height: 100vh;margin: 0;background-color: #f8f9fa;font-family: Arial, sans-serif;}.container {text-align: center;background-color: #ffffff;padding: 20px;border-radius: 10px;box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);}");
    printf(".message {font-size: 2em;color: #dc3545;margin-bottom: 20px;}.emoji {font-size: 5em;display: inline-block;animation: shake 1s ease-in-out infinite;}@keyframes shake {0%%, 100%% { transform: translateX(0); }25%% { transform: translateX(-10px); }50%% { transform: translateX(10px); }75%% { transform: translateX(-10px); }}");
    printf("form{padding:20px;position:absolute;bottom:200px;border-radius:10px;}</style></head><body><div class=\"container\"><div class=\"message\">Login déjà utilisé</div><div class=\"emoji\">😞</div></div>");
    printf("<form action=\"login.html\"><input type=\"submit\" value=\"Retour au login\"></form></body></html>");
}

int verifierUtilisateur(FILE *file, const char *user, const char *password) {
    char line[256];
    while (fgets(line, 256, file) != NULL) {
        char *c = strchr(line, '\n');
        char *nom1 = strtok(line, ";");
        char *mdp1 = strtok(NULL, ";");
        if (c != NULL) *c = '\0';
        if (strcmp(nom1, user) == 0 || strcmp(mdp1, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void ajouterUtilisateur(FILE *file, const char *user, const char *password) {
    fprintf(file, "%s;%s\n", user, password);
}

void extraireParametres(char *data, char *user, char *password) {
    char *nom = strtok(data, "&");
    char *mdp = strtok(NULL, "&");
    if (nom != NULL) 
        sscanf(nom, "user=%s", user);
    if (mdp != NULL) 
        sscanf(mdp, "password=%s", password);
    for(int i=0; i<strlen(user); i++){
        if(user[i]=='+')
            user[i]= 0;
    }
}
