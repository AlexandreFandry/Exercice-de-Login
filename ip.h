#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void valeurCible(char *ip, int *bit1, int *bit2, int *bit3, int *bit4);
void changeType(int bit1, int bit2, int bit3, int bit4, int *premier_bits, int *deuxieme_bits, int *troisieme_bits, int *quatrieme_bits);
void infoIP(int bit1, int bit2, int bit3, int bit4);
void end(int bit1, int bit2, int bit3, int bit4);
void start(char *ip);
void firstbits(int bit1, int j, int *tab, int i);
void secondbits(int bit2, int j, int *tab, int i);
void thirdbits(int bit3, int j, int *tab, int i);
void fourbits(int bit4, int j, int *tab, int i);