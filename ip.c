#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ip.h"

int main() {
    char ip[200];
    int bit1, bit2, bit3, bit4;
    int premier_bits, deuxieme_bits, troisieme_bits, quatrieme_bits;
	char *data=NULL;

	printf("content-text: text/html\n\n");
	data=getenv("QUERY_STRING");
	if(data != NULL){
		sscanf(data, "ip=%s", ip);
	}
	
    valeurCible(ip, &bit1, &bit2, &bit3, &bit4);
    changeType(bit1, bit2, bit3, bit4, &premier_bits, &deuxieme_bits, &troisieme_bits, &quatrieme_bits);
    start(ip);
	infoIP(premier_bits, deuxieme_bits, troisieme_bits, quatrieme_bits);
    end(premier_bits, deuxieme_bits, troisieme_bits, quatrieme_bits);

    return 0;
}
void start(char *ip){
    char line2[256], *nom=NULL;
    FILE *file2 = fopen("/home/mit/monHTML/donne.txt", "r");
    if(file2 == NULL){
        printf("<p>Erreur de fichier</p>");
    }
    if (fgets(line2, sizeof(line2), file2) != NULL) {
        char *c = strchr(line2, '\n');
        if (c != NULL) *c = '\0';
        nom = strtok(line2, ";");
    }
	printf("<html lang=\"fr\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
	printf("<style>body{font-family: Arial;margin: 70px;padding: 70px;background-image: url('image.avif');background-size: cover;background-position: center;background-repeat: no-repeat;}h1{position:absolute;top:20%%;left:600px;}p{size-family: Manjari;position:absolute;font-size:20px;}.msr{color:blue;}.binaire{color: green;font-size:20px;}.texte{font-size: 30px;font-family: Manjari;color: red;}.container{max-width: 700px;max-height: 400px;margin: 0 auto;padding: 70px;background-color: aliceblue;border-radius: 8px;box-shadow: 0 0 10px;}");
    printf("ion-icon{font-size:70px;position:absolute;left:0;top:2%%;}h3{color:white;margin:0 auto;position:absolute;top:6%%;left:80px;font-family:monospace;font-style:italic;}");
    printf("input[type=\"text\"]{width: 100px; padding: 2px; margin-bottom: 16px; border: 1px solid green; border-radius: 4px;}input[type=\"submit\"]{position:absolute;bottom:25%%;right:300px;width: 10%%; padding: 10px; background-color: #007bff; border: none;border-radius: 4px;color: #fff;font-size: 16px;cursor: pointer;}");
    printf(".dropdown {position: absolute;display: inline-block;top:6%%;left:150px;}.dropdown-content {display: none;position: absolute;background-color: black;min-width: 100px;box-shadow: 0px 8px 16px 0px black;z-index: 1;}.dropdown-content a {color: rgb(247, 242, 242);padding: 8px 16px;text-decoration: none;display: block;}.dropdown-content a:hover {background-color: black;}");
    printf(".dropdown:hover .dropdown-content {display: block;}.arrow {font-size: 20px;cursor: pointer;display: inline-block;transition: transform 0.3s;color:green;}.dropdown:hover .arrow {transform: rotate(180deg);}</style>");
	printf("</head><body><ion-icon name=\"person-circle-outline\"></ion-icon><h3>""%s""</h3><div class=\"container\">", nom);
    printf("<div class=\"dropdown\"><span class=\"arrow\">▼</span><div class=\"dropdown-content\"><a href=\"login.html\">Se déconnecter</a></div></div>");
}
void end(int bit1, int bit2, int bit3, int bit4){
    printf("</br></br><form action=\"infoplus.cgi\" method=\"get\"><b>Entrer le nombre de bits (32 bits maximum) </b>");
    printf("<input type=\"text\" name=\"bits\"><input type=\"hidden\" name=\"ip\" value=\"%d.%d.%d.%d\"><input type=\"submit\" value=\"Voir plus d'info\"></form>", bit1, bit2, bit3, bit4);
    printf("</div></p><script type=\"module\" src=\"https://unpkg.com/ionicons@7.1.0/dist/ionicons/ionicons.esm.js\">");
    printf("</script><script nomodule src=\"https://unpkg.com/ionicons@7.1.0/dist/ionicons/ionicons.js\"></script></body></html>");
}
void valeurCible(char *ip, int *bit1, int *bit2, int *bit3, int *bit4) {
    char *token;
    token = strtok(ip, ".");
    *bit1 = atoi(token);
    token = strtok(NULL, ".");
    *bit2 = atoi(token);
    token = strtok(NULL, ".");
    *bit3 = atoi(token);
    token = strtok(NULL, ".");
    *bit4 = atoi(token);
}

void changeType(int bit1, int bit2, int bit3, int bit4, int *premier_bits, int *deuxieme_bits, int *troisieme_bits, int *quatrieme_bits) {
    *premier_bits = bit1;
    *deuxieme_bits = bit2;
    *troisieme_bits = bit3;
    *quatrieme_bits = bit4;
}

void infoIP(int bit1, int bit2, int bit3, int bit4) {
	int i=0, j, tab[20];
    printf("<p><h1>%d.%d.%d.%d</h1>", bit1, bit2, bit3, bit4);
    if(bit1<=255 && bit2<=255 && bit3<=255 && bit4<=255){
            printf("</br>En binaire : ");    
        if (bit1 >= 0 && bit1 <= 127) {
            firstbits(bit1, j, tab, i);
            if (bit2 >= 0 && bit2 <= 255) {
                i=0;
                secondbits(bit2, j, tab, i);
                if (bit3 >= 0 && bit3 <= 255) {
                    i=0;
                    thirdbits(bit3, j, tab, i);
                    if (bit4 >= 0 && bit4 <= 255) {
                        i=0;
                        fourbits(bit4, j, tab, i);
                        printf("</br>valeur masque de sous reseau par defaut : <span class=\"msr\">255.0.0.0</span></br></br>");
                    printf("<center><span class=\"texte\">Votre adresse IP est de classe A\n</span></center>");
                    printf("</br>Adresse reseau : ");
                    bit2=0;bit3=0;bit4=0;
                    printf("<span class=\"msr\">%d.%d.%d.%d</span>", bit1, bit2, bit3, bit4);
                    printf("</br>Adresse broadcast : ");
                    bit2=255;bit3=255;bit4=255;
                    printf("<span class=\"msr\">%d.%d.%d.%d</span>", bit1, bit2, bit3, bit4);
                    }
    			}
            }
        }
        if (bit1 >= 128 && bit1 <= 191) {
            firstbits(bit1, j, tab, i);
            if (bit2 >= 0 && bit2 <= 255) {
                i=0;
                secondbits(bit2, j, tab, i);
                if (bit3 >= 0 && bit3 <= 255) {
                    i=0;
                    thirdbits(bit3, j, tab, i);
                    if (bit4 >= 0 && bit4 <= 255) {
                        i=0;
                        fourbits(bit4, j, tab, i);
                        printf("</br>valeur masque de sous reseau par defaut : <span class=\"msr\">255.255.0.0</span></br></br>");
                        printf("<center><span class=\"texte\">Votre adresse IP est de classe B\n</span></center>");
                        printf("</br>Adresse reseau : ");
                    bit3=0;bit4=0;
                    printf("<span class=\"msr\">%d.%d.%d.%d</span>", bit1, bit2, bit3, bit4);
                    printf("</br>Adresse broadcast : ");
                    bit3=255;bit4=255;
                    printf("<span class=\"msr\">%d.%d.%d.%d</span>", bit1, bit2, bit3, bit4);
                    }
                }
            }
        }
        if (bit1 >= 192 && bit1 <= 223) {
            firstbits(bit1, j, tab, i);
            if (bit2 >= 0 && bit2 <= 255) {
                i=0;
                secondbits(bit2, j, tab, i);
                if (bit3 >= 0 && bit3 <= 255) {
                    i=0;
                    thirdbits(bit3, j, tab, i);
                    if (bit4 >= 0 && bit4 <= 255) {
                        i=0;
                        fourbits(bit4, j, tab, i);
                        printf("</br>valeur masque de sous reseau par defaut : <span class=\"msr\">255.255.255.0</span></br></br>");
                        printf("<center><span class=\"texte\">Votre adresse IP est de classe C\n</span></center>");
                    printf("</br>Adresse reseau : ");
                    bit4=0;
                    printf("<span class=\"msr\">%d.%d.%d.%d</span>", bit1, bit2, bit3, bit4);
                    printf("</br>Adresse broadcast : ");
                    bit4=255;
                    printf("<span class=\"msr\">%d.%d.%d.%d</span>", bit1, bit2, bit3, bit4);
                    }
                }
            }
        }
        if (bit1 >= 224 && bit1 <= 239) {
            firstbits(bit1, j, tab, i);
            if (bit2 >= 0 && bit2 <= 255) {
                i=0;
                secondbits(bit2, j, tab, i);
                if (bit3 >= 0 && bit3 <= 255) {
                    i=0;
                    thirdbits(bit3, j, tab, i);
                    if (bit4 >= 0 && bit4 <= 255) {
                        i=0;
                        fourbits(bit4, j, tab, i);
                        printf("</center><span>Votre adresse IP est de classe D\n</span></center>");
                    }
                }
            }
        }
        if (bit1 >= 240 && bit1 <= 255) {
            firstbits(bit1, j, tab, i);
            if (bit2 >= 0 && bit2 <= 255) {
                i=0;
                secondbits(bit2, j, tab, i);
                if (bit3 >= 0 && bit3 <= 255) {
                    i=0;
                    thirdbits(bit3, j, tab, i);
                    if (bit4 >= 0 && bit4 <= 255) {
                        i=0;
                        fourbits(bit4, j, tab, i);
                        printf("<center><span class=\"texte\">Votre adresse IP est de classe E\n</span></center>");
                    }
                }
            }
        }
    }
    
    else{
		printf("<form action=\"ip.html\"><center><span class=\"texte\">Chaque chiffre doit entre 0 et 255</span></center><input type=\"submit\" value=\"Resaisir\"></form>");
	}
}
void firstbits(int bit1, int j, int *tab, int i){
    for(j=0; j<8; j++)
        tab[j]=0;    
    while(bit1 > 0){
        tab[i]= bit1 % 2;
        bit1= bit1 / 2;
        i++;
    }
    for(j=7; j>=0; j--)
        printf("<span class=\"binaire\">%d</span>", tab[j]);
    printf("<span class=\"binaire\">.</span>");
}
void secondbits(int bit2, int j, int *tab, int i){
    for(j=0; j<8; j++)
        tab[j]=0;
    while(bit2 > 0){
        tab[i]= bit2 % 2;
        bit2= bit2 / 2;
        i++;
    }
    for(j=7; j>=0; j--)
        printf("<span class=\"binaire\">%d</span>", tab[j]);
    printf("<span class=\"binaire\">.</span>");
}
void thirdbits(int bit3, int j, int *tab, int i){
    for(j=0; j<8; j++)
        tab[j]=0;
    while(bit3 > 0){            
        tab[i]= bit3 % 2;
        bit3= bit3 / 2;
        i++;
    }
    for(j=7; j>=0; j--)
        printf("<span class=\"binaire\">%d</span>", tab[j]);
    printf("<span class=\"binaire\">.</span>");
}
void fourbits(int bit4, int j, int *tab, int i){
     for(j=0; j<8; j++)
        tab[j]=0;
    while(bit4 > 0){
        tab[i]= bit4 % 2;
        bit4= bit4 / 2;
        i++;
    }
    for(j=7; j>=0; j--)
        printf("<span class=\"binaire\">%d</span>", tab[j]);
}