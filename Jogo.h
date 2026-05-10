#ifndef JOGO_H
#define JOGO_H

#include "Pecas.h"

//A matriz externa para que todos os ficheiros a vejam
extern int tabuleiro_estado[8][8];

//Funções de lógica
void inicializar_jogo();

int validar_movimento(int origem_y, int origem_x, int destino_y, int destino_x);


#endif