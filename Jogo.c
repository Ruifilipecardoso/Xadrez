#include "Jogo.h"
#include <stdlib.h>

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

int validar_peao(int oy, int ox, int dy, int dx, int cor) {
    int direcao = (cor == BRANCO) ? -1 : 1;

    //Movimento simples (1 casa à frente)
    if (ox == dx && dy == oy + direcao && tabuleiro_estado[dy][dx] == VAZIO) {
        return 1;
    }

    //Salto duplo inicial
    if (ox == dx && dy == oy + (2 * direcao)) {
        if ((cor == BRANCO && oy == 6) || (cor == PRETO && oy == 1)) {
            if (tabuleiro_estado[oy + direcao][ox] == VAZIO && tabuleiro_estado[dy][dx] == VAZIO) {
                return 1;
            }
        }
    }

    //Comer (Diagonal)
    if (abs(ox - dx) == 1 && dy == oy + direcao) {
        int peca_destino = tabuleiro_estado[dy][dx];
        if (peca_destino != VAZIO) {
            return 1;
        }
    }

    return 0;
}

int validar_torre(int oy, int ox, int dy, int dx) {
    //A Torre só move se apenas modar o x ou o y.
    if (oy != dy && ox != dx) return 0;

    //Verificara se o caminho está livre.
    int passo_y = (dy > oy) ? 1 : (dy < oy) ? -1 : 0;
    int passo_x = (dx > ox) ? 1 : (dx < ox) ? -1 : 0;

    int cur_y = oy + passo_y;
    int cur_x = ox + passo_x;

    while (cur_y != dy || cur_x != dx) {
        if (tabuleiro_estado[cur_y][cur_x] != VAZIO) return 0;
        cur_y += passo_y;
        cur_x += passo_x;
    }

    return 1;

}

int validar_movimento(int oy, int ox, int dy, int dx) {
    int peca = tabuleiro_estado[oy][ox];
    int tipo = peca % 10;
    int cor = (peca >= 20) ? PRETO : BRANCO;

    //Regra nº1: Não pode comer as peças da mesma cor.
    int peca_destino = tabuleiro_estado[dy][dx];
    if (peca_destino != VAZIO) {
        int cor_destino = (peca_destino >= 20) ? PRETO : BRANCO;
        if (cor == cor_destino) return 0; //Inválido
    }

    //Regra por Peça.
    switch(tipo) {
        case PEAO: return validar_peao(oy, ox, dy, dx, cor);
        case TORRE: return validar_torre(oy, ox, dy, dx);
        //case CAVALO: return validar_cavalo(oy, ox, dy, dx);
        //case BISPO: return validar_bispo(oy, ox, dy, dx);
        //case RAINHA: return validar_rainha(oy, ox, dy, dx);
        //case REI: return validar_rei(oy, ox, dy, dx);
    }
    return 0;
}

void mover_peca(int oy, int ox, int dy, int dx) {
    //Mover a Peça
    tabuleiro_estado[dy][dx] = tabuleiro_estado[oy][ox];
    tabuleiro_estado[oy][ox] = VAZIO;

    //Extrai as informações da peça que moveu
    int peca_movida = tabuleiro_estado[dy][dx];
    int tipo = peca_movida % 10;
    int cor = (peca_movida >= 20) ? PRETO : BRANCO;

    //Promoção do peão
    if (tipo == PEAO && (dy == 0 || dy == 7)) {
        tabuleiro_estado[dy][dx] = RAINHA + cor;
    }
}