#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct donne {
    char user[100];
    char password[100];
};
void init_files(FILE **file, FILE **file2);
void recup_env(struct donne *donne);
void ecrirefichier(FILE *file2, struct donne *donne);
int compare_files(FILE *file, FILE *file2);
void success(struct donne *donne);
void error();