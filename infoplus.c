#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "infoplus.h"

int main(){
    int bits=0;
    char *data=NULL;
    int bit1, bit2, bit3, bit4;
    printf("content-text: text/html\n\n");
    data = getenv("QUERY_STRING");
    if(data != NULL){
        sscanf(data, "bits=%d&ip=%d.%d.%d.%d", &bits, &bit1, &bit2, &bit3, &bit4);
    }
    start();
    IPuser(bit1, bit2, bit3, bit4, bits);
    calcul(bit1, bit2, bit3, bit4, bits);
    
    end();
    return 0;
}
void start(){
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
	printf("<style>body{font-family: Arial;margin: 70px;padding: 70px;background-image: url('image.avif');background-size: cover;background-position: center;background-repeat: no-repeat;}h1{position:absolute;top:20%%;left:550px;}p{size-family: Manjari;position:absolute;font-size:20px;}.msr{color:blue;}.binaire{color: green;}.texte{font-size: 30px;font-family: Manjari;color: red;position:absolute;top:30%%;right:500px;}.container{max-width: 700px;max-height: 400px;width:auto;min-height:100px;margin: 0 auto;padding: 70px;background-color: aliceblue;border-radius: 8px;box-shadow: 0 0 10px;overflow:auto;}");
    printf("ion-icon{font-size:70px;position:absolute;left:0;top:2%%;}h3{color:white;margin:0 auto;position:absolute;top:6%%;left:80px;font-family:monospace;font-style:italic;}");
    printf(".label{margin-top:10px;color:purple;}.ac{display:flex;align-items:center;}.content{margin-right:10px;}.brace{font-size:10%%;line-height:0;margin-right:20px;height:35px;transform: scaleY(2);}.input[type=\"text\"]{width: 100px; padding: 2px; margin-bottom: 16px; border: 1px solid green; border-radius: 4px;}input[type=\"submit\"]{position:absolute;bottom:25%%;right:300px;width: 10%%; padding: 10px; background-color: #007bff; border: none;border-radius: 4px;color: #fff;font-size: 16px;cursor: pointer;}");
    printf(".dropdown {position: absolute;display: inline-block;top:6%%;left:150px;}.dropdown-content {display: none;position: absolute;background-color: black;min-width: 100px;box-shadow: 0px 8px 16px 0px black;z-index: 1;}.dropdown-content a {color: rgb(247, 242, 242);padding: 8px 16px;text-decoration: none;display: block;}.dropdown-content a:hover {background-color: black;}");
    printf(".dropdown:hover .dropdown-content {display: block;}.arrow {font-size: 20px;cursor: pointer;display: inline-block;transition: transform 0.3s;color:green;}.dropdown:hover .arrow {transform: rotate(180deg);}</style>");
	printf("</head><body><ion-icon name=\"person-circle-outline\"></ion-icon><h3>""%s""</h3><div class=\"container\">", nom);
    printf("<div class=\"dropdown\"><span class=\"arrow\">▼</span><div class=\"dropdown-content\"><a href=\"login.html\">Se déconnecter</a></div></div>");
}
void end(){
    printf("</div></p><script type=\"module\" src=\"https://unpkg.com/ionicons@7.1.0/dist/ionicons/ionicons.esm.js\">");
    printf("</script><script nomodule src=\"https://unpkg.com/ionicons@7.1.0/dist/ionicons/ionicons.js\"></script></body></html>");
}
void IPuser(int bit1, int bit2, int bit3, int bit4, int bits){
    printf("<p class=\"all\"><h1>%d.%d.%d.%d / %d</h1>", bit1, bit2, bit3, bit4, bits);
}
void calcul(int bit1, int bit2, int bit3, int bit4, int bits){
    int n=0, p=1, hote=0, nbr_machine=0;
    if (bit1 >= 192 && bit1 <= 223){ 
        n = bits - 24;
        p=n;
        printf("</br><center><span class=\"texte\">Vous effectue (%d) découpee</span></center>", p);
        n = 32 - bits;
            if (bit2 >= 0 && bit2 <= 255) {
                if (bit3 >= 0 && bit3 <= 255) {
                    if (bit4 >= 0 && bit4 <= 255){
                        bit4 = 256;
                        nbr_machine = pow(2,n) - 2;
                        printf("</br>Le nombre de machine possible : <mark>%d</mark></br>", nbr_machine);
                        for(int i=0; i<pow(2, p); i++){
                            printf("<div class=\"ac\"><div class=\"content\">");
                            printf("</br>L' adresse reseau n°%d : <span class=\"msr\">%d.%d.%d.%d</span>", i+1, bit1, bit2, bit3, hote);
                            hote = hote + (bit4) / pow(2, p);
                            printf("</br>L' adresse broadcast n°%d : <span class=\"binaire\">%d.%d.%d.%d</span></br>", i+1, bit1, bit2, bit3, (hote-1));
                            printf("</div><div class=\"brace\"><p>&#123</p></div><div class=\"label\">Sous reseau n°%d</div></div>", i+1);
                        }
                    }
                }
            }
    }
    if (bit1 >= 128 && bit1 <= 191){ 
        n = bits - 16;
        p=n;
        printf("</br><center><span class=\"texte\">Vous effectue (%d) découpee</span></center>", p);
        n = 32 - bits;
        if (bit2 >= 0 && bit2 <= 255) {
            if (bit3 >= 0 && bit3 <= 255) {
                if (bit4 >= 0 && bit4 <= 255){
                    bit3 = 256;
                    nbr_machine = pow(2,n) - 2;
                    printf("</br>Le nombre de machine possible : <mark>%d</mark></br>", nbr_machine);
                    for(int i=0; i<pow(2, p); i++){
                        bit4=0;
                        printf("<div class=\"ac\"><div class=\"content\">");
                        printf("</br>L' adresse reseau n°%d : <span class=\"msr\">%d.%d.%d.%d</span>", i+1, bit1, bit2, hote, bit4);
                        hote = hote + (bit3) / pow(2, p);
                        bit4=255;
                        printf("</br>L' adresse broadcast n°%d : <span class=\"binaire\">%d.%d.%d.%d</span></br>", i+1, bit1, bit2, hote-1, bit4);
                        printf("</div><div class=\"brace\"><p>&#123</p></div><div class=\"label\">Sous reseau n°%d</div></div>", i+1);
                        
                    }
                }
            }
        }
    }
    if (bit1 >= 0 && bit1 <= 127){ 
        n = bits - 8;
        p=n;
        printf("</br><center><span class=\"texte\">Vous effectue (%d) découpee</span></center>", p);
        n = 32 - bits;
        if (bit2 >= 0 && bit2 <= 255) {
            if (bit3 >= 0 && bit3 <= 255) {
                if (bit4 >= 0 && bit4 <= 255){
                    bit2 = 256;
                    nbr_machine = pow(2,n) - 2;
                    printf("</br>Le nombre de machine possible : <mark>%d</mark></br>", nbr_machine);
                    for(int i=0; i<pow(2, p); i++){
                        bit4=0;bit3=0;
                        printf("<div class=\"ac\"><div class=\"content\">");
                        printf("</br>L' adresse reseau n°%d : <span class=\"msr\">%d.%d.%d.%d</span>", i+1, bit1, hote, bit3, bit4);
                        hote = hote + (bit2) / pow(2, p);
                        bit4=255;bit3=255;
                        printf("</br>L' adresse broadcast n°%d : <span class=\"binaire\">%d.%d.%d.%d</span></br>", i+1, bit1, hote-1, bit3, bit4);
                        printf("</div><div class=\"brace\"><p>&#123</p></div><div class=\"label\">Sous reseau n°%d</div></div>", i+1);   
                    }
                }
            }
        }
    }
}