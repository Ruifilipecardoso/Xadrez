#ifndef JOGO_H
#define JOGO_H

#include "Pecas.h"

//A matriz externa para que todos os ficheiros a vejam
extern int tabuleiro_estado[8][8];
extern int turno_atual;

extern int en_passant_coluna;


//Funções de lógica
void inicializar_jogo();

int xeque(int target_y, int target_x, int cor_defensora);

void encontrar_rei (int cor, int *rei_y, int *rei_x);

int xeque_mate(int cor_atual);

int validar_peao(int oy, int ox, int dy, int dx, int cor);

int validar_torre(int oy, int ox, int dy, int dx);

int validar_cavalo(int oy, int ox, int dy, int dx);

int validar_bispo(int oy, int ox, int dy, int dx);

int validar_rainha(int oy, int ox, int dy, int dx);

int validar_rei_basico(int oy, int ox, int dy, int dx);

int validar_roque(int oy, int ox, int dy, int dx);

int validar_movimento(int oy, int ox, int dy, int dx);

void mover_peca(int oy, int ox, int dy, int dx);


#endif