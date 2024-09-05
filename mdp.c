#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mdp.h"

int main() {
    char *data = NULL;
    char user[100];
    char password[100];
    int found = 0;
    FILE *file = NULL;
    FILE *file2 = NULL;

    // Affichage de l'en-tête HTML
    printf("content-text: text/html\n\n");

    // Extraction des paramètres de la chaîne de requête
    data = getenv("QUERY_STRING");
    if (data != NULL) {
        extraireUser(data, user);
    }

    // Écriture du nom d'utilisateur dans le fichier
    ecrireUserDansFichier(user);

    // Réouverture des fichiers
    file = fopen("/home/mit/monHTML/donne.txt", "r");
    file2 = fopen("/home/mit/monHTML/forget.txt", "r");
    if (file == NULL || file2 == NULL) {
        printf("<h1>Erreur d'ouverture du fichier</h1>");
        return 1;
    }

    // Lecture du nom d'utilisateur depuis le fichier
    char line2[256];
    if (fgets(line2, sizeof(line2), file2) != NULL) {
        char *c = strchr(line2, '\n');
        if (c != NULL) *c = '\0';
    } else {
        fprintf(stderr, "Erreur de lecture du fichier forget.txt\n");
        fclose(file);
        fclose(file2);
        return 1;
    }
    fclose(file2);

    // Trouver le mot de passe associé à l'utilisateur
    found = trouverMotDePasse(file, line2, password);
    fclose(file);

    // Afficher le résultat en fonction de la recherche
    if (found) {
        afficherMotDePasseTrouve(user, password);
    } else {
        afficherUtilisateurInexistant(user);
    }

    return 0;
}

void afficherMotDePasseTrouve(const char *user, const char *password) {
    printf("<html><head><style>body{margin: 0;padding: 0;height: 100vh;background-image: url('image.avif');background-size: cover;background-position: center;background-repeat: no-repeat;font-family: Arial, sans-serif;}");
    printf(".container{border: 1px solid black;background-color: black;border-radius: 40px;width: 600px;height: 200px;margin: 0 auto;padding: 60px;position: absolute;right: 310px;bottom: 140px;}");
    printf("h1{color: bisque;text-align: center;margin-top: -20px;}p{color: aqua;font-size: larger;font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;}");
    printf(".log{border: 1px solid rgb(19, 223, 53);background-color: rgb(19, 223, 53);border-color: rgb(19, 223, 53);border-radius: 7px;padding: 10px;position: absolute;bottom: 100px;left:40%%;}input[value=\"Retour au login\"]{font-size: larger;cursor:pointer;}</style>");
    printf("<form action=\"login.html\" method=\"get\"><div class=\"container\"><h1>MOT DE PASSE TROUVE</h1><p>\"%s\" votre mot de passe est : \"%s\"</p><center><p>Merci, pour votre confiance !</p></center>", user, password);
    printf("<input class=\"log\" type=\"submit\" value=\"Retour au login\"> </div></form></body></html>");
}

void afficherUtilisateurInexistant(const char *user) {
    printf("<html><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><style>body{margin: 0;padding: 0;height: 100vh;background-image: url('image.avif');background-size: cover;background-position: center;background-repeat: no-repeat;font-family: Arial, sans-serif;}");
    printf(".container{border: 1px solid black;background-color: black;border-radius: 40px;width: 600px;height: 200px;margin: 0 auto;padding: 60px;position: absolute;right: 310px;bottom: 140px;}");
    printf("h1{color: bisque;text-align: center;margin-top: -20px;}p{color: red;font-size: larger;font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;}");
    printf(".log{border: 1px solid rgb(19, 223, 53);background-color: rgb(19, 223, 53);border-color: rgb(19, 223, 53);border-radius: 7px;padding: 10px;position: absolute;bottom: 100px;left:40%%;}input[value=\"Retour au login\"]{font-size: larger;cursor:pointer;}</style>");
    printf("<form action=\"login.html\" method=\"get\"><div class=\"container\"><h1>IMPOSSIBLE</h1><p>L'utilisateur \"%s\" n'existe pas, entrez un vrai nom</p><center><p>DÉSOLÉ !</p></center>", user);
    printf("<input class=\"log\" type=\"submit\" value=\"Retour au login\"> </div></form></body></html>");
}

void extraireUser(const char *data, char *user) {
    sscanf(data, "user=%s", user);
}

int trouverMotDePasse(FILE *file, const char *user, char *password) {
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        char *c = strchr(line, '\n');
        char *nom1 = strtok(line, ";");
        char *mdp1 = strtok(NULL, ";");
        if (c != NULL) *c = '\0';
        if (strcmp(nom1, user) == 0) {
            strcpy(password, mdp1);
            return 1;
        }
    }
    return 0;
}

void ecrireUserDansFichier(const char *user) {
    FILE *file2 = fopen("/home/mit/monHTML/forget.txt", "w");
    if (file2 == NULL) {
        printf("<h1>Erreur d'ouverture du fichier</h1>");
        exit(1);
    }
    fprintf(file2, "%s\n", user);
    fclose(file2);
}
