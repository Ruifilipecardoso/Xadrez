#ifndef JOGO_H
#define JOGO_H

#include "Pecas.h"

//A matriz externa para que todos os ficheiros a vejam
extern int tabuleiro_estado[8][8];
extern int turno_atual = BRANCO;

//Funções de lógica
void inicializar_jogo();

int validar_peao(int oy, int ox, int dy, int dx, int cor);

int validar_torre(int oy, int ox, int dy, int dx);

int validar_cavalo(int oy, int ox, int dy, int dx);

int validar_bispo(int oy, int ox, int dy, int dx);

int validar_rainha(int oy, int ox, int dy, int dx);

int validar_rei(int oy, int ox, int dy, int dx);

int validar_movimento(int oy, int ox, int dy, int dx);

void mover_peca(int oy, int ox, int dy, int dx);


#endif