#ifndef PECAS_H
#define PECAS_H

#include <ncurses.h>

#define BRANCO 10
#define PRETO 20

#define VAZIO 0
#define PEAO 1
#define TORRE 2
#define CAVALO 3
#define BISPO 4
#define RAINHA 5
#define REI 6

void cor_peca(int cor, int y, int x);

void desenhar_peca(int y, int x, int tipo, int cor);

void desenhar_peao(int y, int x);
void desenhar_torre(int y, int x);
void desenhar_cavalo(int y, int x);
void desenhar_bispo(int y, int x);
void desenhar_rainha(int y, int x);
void desenhar_rei(int y, int x);


#endif