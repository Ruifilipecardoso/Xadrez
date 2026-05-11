#include "Jogo.h"

int tabuleiro_estado[8][8];

void inicializar_jogo() {
    //Limpar tabuleiro
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            tabuleiro_estado[y][x] = VAZIO;
        }
    }

    tabuleiro_estado[0][0] = TORRE + PRETO;
    tabuleiro_estado[0][1] = CAVALO + PRETO;
    tabuleiro_estado[0][2] = BISPO + PRETO;
    tabuleiro_estado[0][3] = REI + PRETO;
    tabuleiro_estado[0][4] = RAINHA + PRETO;
    tabuleiro_estado[0][5] = BISPO + PRETO;
    tabuleiro_estado[0][6] = CAVALO + PRETO;
    tabuleiro_estado[0][7] = TORRE + PRETO;

    for(int x = 0; x < 8; x++) {
        tabuleiro_estado[1][x] = PEAO + PRETO;
    }

    for(int x = 0; x < 8; x++) {
        tabuleiro_estado[6][x] = PEAO + BRANCO;
    }

    tabuleiro_estado[7][0] = TORRE + BRANCO;
    tabuleiro_estado[7][1] = CAVALO + BRANCO;
    tabuleiro_estado[7][2] = BISPO + BRANCO;
    tabuleiro_estado[7][3] = REI + BRANCO;
    tabuleiro_estado[7][4] = RAINHA + BRANCO;
    tabuleiro_estado[7][5] = BISPO + BRANCO;
    tabuleiro_estado[7][6] = CAVALO + BRANCO;
    tabuleiro_estado[7][7] = TORRE + BRANCO;
}

void mover_peca(int oy, int ox, int dy, int dx) {
    tabuleiro_estado[dy][dx] = tabuleiro_estado[oy][ox];
    tabuleiro_estado[oy][ox] = VAZIO;
}