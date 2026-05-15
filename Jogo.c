#include "Jogo.h"
#include <stdlib.h>

int tabuleiro_estado[8][8];
int turno_atual = BRANCO;

int rei_branco_moveu = 0;
int rei_preto_moveu = 0;
int torre_branca_esq_moveu = 0; 
int torre_branca_dir_moveu = 0; 
int torre_preta_esq_moveu = 0;  
int torre_preta_dir_moveu = 0;

int en_passant_coluna = -1;

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
    tabuleiro_estado[0][3] = RAINHA + PRETO;
    tabuleiro_estado[0][4] = REI + PRETO;
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
    tabuleiro_estado[7][3] = RAINHA + BRANCO;
    tabuleiro_estado[7][4] = REI + BRANCO;
    tabuleiro_estado[7][5] = BISPO + BRANCO;
    tabuleiro_estado[7][6] = CAVALO + BRANCO;
    tabuleiro_estado[7][7] = TORRE + BRANCO;
}

int xeque(int target_y, int target_x, int cor_defensora) {
    int cor_atacante = (cor_defensora == BRANCO) ? PRETO : BRANCO;

    //Procurar peças inimigas
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            int peca = tabuleiro_estado[y][x];
            if (peca != VAZIO) {
                int cor_peca = (peca >= 20) ? PRETO : BRANCO;

                if (cor_peca == cor_atacante) {
                    int turno_salvo = turno_atual;
                    turno_atual = cor_atacante;

                    if (validar_movimento(y, x, target_y, target_x) == 1) {
                        turno_atual = turno_salvo;
                        return 1; //Xeque
                    }
                    turno_atual = turno_salvo;
                }
            }
            
        }
    }
    return 0;
}

void encontrar_rei (int cor, int *rei_y, int *rei_x) {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            int peca = tabuleiro_estado[y][x];
            if (peca != VAZIO) {
                int tipo = peca % 10;
                int cor_peca = (peca >= 20) ? PRETO : BRANCO;

                if (tipo == REI && cor_peca == cor) {
                    *rei_y = y;
                    *rei_x = x;
                    return;
                }
            }
        }
    }
}

int xeque_mate(int cor_atual) {
    int rei_y, rei_x;
    encontrar_rei(cor_atual, &rei_y, &rei_x);

    if (xeque(rei_y, rei_x, cor_atual) == 0) {return 0;}

    for (int oy = 0; oy < 8; oy++) {
        for (int ox = 0; ox < 8; ox++) {
            int peca = tabuleiro_estado[oy][ox];
            if (peca != VAZIO) {
                int cor_peca = (peca >= 20) ? PRETO : BRANCO;

                if (cor_peca == cor_atual) {
                    for (int dy = 0; dy < 8; dy++) {
                        for (int dx = 0; dx < 8; dx++) {
                            if (validar_movimento(oy, ox, dy, dx) == 1) {
                                int peca_origem = tabuleiro_estado[oy][ox];
                                int peca_destino = tabuleiro_estado[dy][dx];

                                tabuleiro_estado[dy][dx] = peca_origem;
                                tabuleiro_estado[oy][ox] = VAZIO;

                                int novo_rei_y, novo_rei_x;
                                encontrar_rei(cor_atual, &novo_rei_y, &novo_rei_x);
                                int ainda_em_xeque = xeque(novo_rei_y, novo_rei_x, cor_atual);

                                tabuleiro_estado[oy][ox] = peca_origem;
                                tabuleiro_estado[dy][dx] = peca_destino;

                                if (ainda_em_xeque == 0) {
                                    return 0;//Apenas Xeque
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 1;//Xeque Mate
}

int validar_peao(int oy, int ox, int dy, int dx, int cor) {
    int direcao = (cor == BRANCO) ? -1 : 1;
    int diff_x = dx - ox;
    int diff_y = dy - oy;
    

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
    if (abs(diff_x) == 1 && diff_y == direcao) {
        int peca_destino = tabuleiro_estado[dy][dx];
        
        if (peca_destino != VAZIO) {
            return 1;
        } else {
            //En-Passant
            if (dx == en_passant_coluna) {
                if ((cor == BRANCO && oy == 3) || (cor == PRETO && oy == 4)) {
                    return 1;
                }
            }
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

int validar_bispo(int oy, int ox, int dy, int dx) {
    //Verificar se o movimento é uma diagonal.
    if (abs(dx - ox) != abs(dy - oy)) return 0;

    //Determinar a direção
    int passo_y = (dy > oy) ? 1 : -1;
    int passo_x = (dx > ox) ? 1 : -1;

    //Verificar se o caminho está livre
    int cur_y = oy + passo_y;
    int cur_x = ox + passo_x;

    while (cur_y != dy || cur_x != dx) {
        if (tabuleiro_estado[cur_y][cur_x] != VAZIO) return 0;
        cur_y += passo_y;
        cur_x += passo_x;
    }

    return 1;
}

int validar_cavalo(int oy, int ox, int dy, int dx) {
    int diff_x = abs(dx - ox);
    int diff_y = abs(dy - oy);

    //Movimento em L
    if ((diff_x == 1 && diff_y == 2) || (diff_x == 2 && diff_y == 1)) {
        return 1;
    }

    return 0;
}

int validar_rainha(int oy, int ox, int dy, int dx) {
    if (validar_torre(oy, ox, dy, dx) || validar_bispo(oy, ox, dy, dx)) {
        return 1;
    }

    return 0;
}

int validar_rei_basico(int oy, int ox, int dy, int dx) {
    int diff_x = abs(dx - ox);
    int diff_y = abs(dy - oy);
    if (diff_x <= 1 && diff_y <= 1) {
        return 1;
    }
    return 0;
}

int validar_roque(int oy, int ox, int dy, int dx) {
    int diff_x = dx - ox;
    int diff_y = dy - oy;

    if (diff_y == 0 && abs(diff_x) == 2) {
        int cor = (tabuleiro_estado[oy][ox] >= 20) ? PRETO : BRANCO;

        if (cor == BRANCO && rei_branco_moveu) return 0;
        if (cor == PRETO && rei_preto_moveu) return 0;
        if (xeque(oy, ox, cor)) return 0;

        if (diff_x == -2) {
            if (cor == BRANCO && torre_branca_esq_moveu) return 0;
            if (cor == PRETO && torre_preta_esq_moveu) return 0;

            if (tabuleiro_estado[oy][1] != VAZIO || tabuleiro_estado[oy][2] != VAZIO || tabuleiro_estado[oy][3] != VAZIO) return 0;
            if (xeque(oy, 2, cor) || xeque(oy, 3, cor)) return 0;

            return 1;
        }

        if (diff_x == 2) {
            if (cor == BRANCO && torre_branca_dir_moveu) return 0;
            if (cor == PRETO && torre_preta_dir_moveu) return 0;

            if (tabuleiro_estado[oy][5] != VAZIO || tabuleiro_estado[oy][6] != VAZIO) return 0;
            if (xeque(oy, 5, cor) || xeque(oy, 6, cor)) return 0;

            return 1;
        }
    }

    //Movimento para a casa adjacente
    if (diff_x <= 1 && diff_y <= 1) {
        return 1;
    }

    return 0;
}

int validar_movimento(int oy, int ox, int dy, int dx) {
    int peca = tabuleiro_estado[oy][ox];
    int tipo = peca % 10;
    int cor = (peca >= 20) ? PRETO : BRANCO;

    //Regra nº1: Só pode mover as peças da cor do turno atual.
    if (cor != turno_atual) return 0;

    //Regra nº2: Não pode comer as peças da mesma cor.
    int peca_destino = tabuleiro_estado[dy][dx];
    if (peca_destino != VAZIO) {
        int cor_destino = (peca_destino >= 20) ? PRETO : BRANCO;
        if (cor == cor_destino) return 0; //Inválido
    }

    //Regra por Peça.
    switch(tipo) {
        case PEAO: return validar_peao(oy, ox, dy, dx, cor);
        case TORRE: return validar_torre(oy, ox, dy, dx);
        case CAVALO: return validar_cavalo(oy, ox, dy, dx);
        case BISPO: return validar_bispo(oy, ox, dy, dx);
        case RAINHA: return validar_rainha(oy, ox, dy, dx);
        case REI: return validar_rei_basico(oy, ox, dy, dx);
    }
    return 0;
}

void mover_peca(int oy, int ox, int dy, int dx) {
    int peca = tabuleiro_estado[oy][ox];
    int tipo = peca % 10;
    int cor = (peca >= 20) ? PRETO : BRANCO;

    int proxima_coluna_enpa = -1;

    if (tipo == PEAO && abs(dy - oy) == 2) {
        proxima_coluna_enpa = ox;
    }

    //Atualizar histórico para impedir Roque futuro
    if (tipo == REI) {
        if (cor == BRANCO) rei_branco_moveu = 1;
        else rei_preto_moveu = 1;
    }
    if (tipo == TORRE) {
        if (cor == BRANCO) {
            if (ox == 0) torre_branca_esq_moveu = 1;
            if (ox == 7) torre_branca_dir_moveu = 1;
        } else {
            if (ox == 0) torre_preta_esq_moveu = 1;
            if (ox == 7) torre_preta_dir_moveu = 1;
        }
    }
    //Mover a Peça
    tabuleiro_estado[dy][dx] = tabuleiro_estado[oy][ox];
    tabuleiro_estado[oy][ox] = VAZIO;

    //Extrai as informações da peça que moveu
    int peca_movida = tabuleiro_estado[dy][dx];
    tipo = peca_movida % 10;
    cor = (peca_movida >= 20) ? PRETO : BRANCO;

    //Promoção do peão
    if (tipo == PEAO && (dy == 0 || dy == 7)) {
        tabuleiro_estado[dy][dx] = RAINHA + cor;
    }

    en_passant_coluna = proxima_coluna_enpa;

    //Alternar o turno
    if (turno_atual == BRANCO) {
        turno_atual = PRETO;
        
    } else {
        turno_atual = BRANCO;
    }
}