#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "verification.h"

int main() {
    struct donne donne;
    FILE *file = NULL, *file2 = NULL;

    printf("content-text: text/html\n\n");

    init_files(&file, &file2);
    recup_env(&donne);
    ecrirefichier(file2, &donne);

    fclose(file2); // Close file2 as it's no longer needed

    file2 = fopen("/home/mit/monHTML/check.txt", "r");
    if (file2 == NULL) {
        printf("<h1>Erreur d'ouverture de fichier</h1>");
        fclose(file);
        exit(1);
    }

    int found = compare_files(file, file2);

    if (found) {
        success(&donne);
    } else {
        error();
    }

    fclose(file);
    fclose(file2);

    return 0;
}

void init_files(FILE **file, FILE **file2) {
    *file = fopen("/home/mit/monHTML/donne.txt", "r");
    *file2 = fopen("/home/mit/monHTML/check.txt", "w");
    if (*file == NULL || *file2 == NULL) {
        printf("<h1>Erreur d'ouverture de fichier</h1>");
        exit(1);
    }
}

void recup_env(struct donne *donne) {
    char *nom = NULL, *mdp = NULL;
    char *data = getenv("QUERY_STRING");
    
    if (data != NULL) {
        nom = strtok(data, "&");
        mdp = strtok(NULL, "&");
    }
    if (nom != NULL) {
        sscanf(nom, "user=%s", donne->user);
    }
    if (mdp != NULL) {
        sscanf(mdp, "password=%s", donne->password);
    }
    for(int i=0; i<strlen(donne->user); i++){
        if(donne->user[i]=='+')
            donne->user[i] = 0;
    }
}

void ecrirefichier(FILE *file2, struct donne *donne) {
    fprintf(file2, "%s;%s", donne->user, donne->password);
}

int compare_files(FILE *file, FILE *file2) {
    char line[500], line2[100];
    int found = 0;

    if (fgets(line2, sizeof(line2), file2) != NULL) {
        char *c = strchr(line2, '\n');
        if (c != NULL) *c = '\0';
    } else {
        fprintf(stderr, "Erreur de lecture du fichier check.txt\n");
        fclose(file);
        fclose(file2);
        exit(1);
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        char *c = strchr(line, '\n');
        if (c != NULL) *c = '\0';
        if (strcmp(line, line2) == 0) {
            found = 1;
            break;
        }
    }

    return found;
}

void success(struct donne *donne) {
    printf("<html lang=\"fr\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Adresse IP</title>");
    printf("<style>ion-icon{font-size:70px;position:absolute;left:0;top:2%%;}h3{color:white;margin:0 auto;position:absolute;top:6%%;left:80px;font-family:monospace;font-style:italic;}body{font-family: Arial;margin: 70px;padding: 70px;background-image: url('image.avif');background-size: cover;background-position: center;background-repeat: no-repeat;}.container{max-width: 700px;max-height: 400px;margin: 0 auto;padding: 70px;background-color: aliceblue;border-radius: 8px;box-shadow: 0 0 10px; }");
    printf("h1{text-align: center;}input[type=\"text\"]{width: calc(100%% - 20px); padding: 10px; margin-bottom: 16px; border: 1 px solid #ddd; border-radius: 4px;}input[type=\"submit\"]{width: 100%%; padding: 10px; background-color: #007bff; border: none;border-radius: 4px;color: #fff;font-size: 16px;cursor: pointer;}");
    printf(".dropdown {position: absolute;display: inline-block;top:6%%;}.dropdown-content {display: none;position: absolute;background-color: black;min-width: 100px;box-shadow: 0px 8px 16px 0px black;z-index: 1;}.dropdown-content a {color: rgb(247, 242, 242);padding: 8px 16px;text-decoration: none;display: block;}.dropdown-content a:hover {background-color: black;}");
    printf(".dropdown:hover .dropdown-content {display: block;}.arrow {font-size: 20px;cursor: pointer;display: inline-block;transition: transform 0.3s;color:green;}.dropdown:hover .arrow {transform: rotate(180deg);}");     
    printf("input[type=\"submit\"]:hover{background-color: #0056b3;}</style></head><body>");
    printf("<div class=\"dropdown\"><span class=\"arrow\">▼</span><div class=\"dropdown-content\"><a href=\"login.html\">Se déconnecter</a></div></div>");
    printf("<ion-icon name=\"person-circle-outline\"></ion-icon><h3>""%s""</h3>", donne->user);
    printf("<div class=\"container\"><h1>INFORMATION D'ADRESSE IP</h1><form action=\"ip.cgi\" method=\"get\"><span>Entrer votre adresse IP</span><input type=\"texte\" placeholder=\"192.243.1.2\" name=\"ip\"><input type=\"submit\" value=\"voir info\"></form></div></body>");
    printf("<script type=\"module\" src=\"https://unpkg.com/ionicons@7.1.0/dist/ionicons/ionicons.esm.js\"></script><script nomodule src=\"https://unpkg.com/ionicons@7.1.0/dist/ionicons/ionicons.js\"></script></html>");
}

void error() {
    printf("<!DOCTYPE html><html lang=\"fr\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Erreur de Mot de Passe</title>");
    printf("<style>body {display: flex;justify-content: center;align-items: center;height: 100vh;margin: 0;background-color: #ffebee;font-family: Arial, sans-serif;}.message {text-align: center;font-size: 2em;color: #d32f2f;padding: 20px;border: 2px solid #d32f2f;border-radius: 10px;background-color: #ffffff;box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);animation: shake 0.5s;}");
    printf("@keyframes shake {0%% { transform: translateX(0); }25%% { transform: translateX(-10px); }50%% { transform: translateX(10px); }75%% { transform: translateX(-10px); }100%% { transform: translateX(0); }}form{padding:20px;position:absolute;bottom:200px;border-radius:10px;}</style></head><body>");
    printf("<div class=\"message\">Mot de passe incorrect !</div>");
    printf("<form action=\"login.html\"><input type=\"submit\" value=\"Retour au login\"></form></body></html>");
}
