#define _XOPEN_SOURCE_EXTENDED 1
#define NCURSES_STATIC
#include "Pecas.h"
#include "Tabuleiro.h"

//Cor de cada peça
void cor_peca(int cor, int y, int x, int cursor_y, int cursor_x, int selecionado_y, int selecionado_x) {
    if (y == cursor_y && x == cursor_x) {
        attron(COLOR_PAIR(7));
        return;
    }
    if (y == selecionado_y && x == selecionado_x) {
        attron(COLOR_PAIR(8));
        return;
    }

    int casa_azul = ((x + y) % 2 == 0);
    if (cor == BRANCO) {
        attron(COLOR_PAIR(casa_azul ? 3 : 4));
    } else {
        attron(COLOR_PAIR(casa_azul ? 5 : 6));
    }
}

void desenhar_peao(int y, int x) {
    mvaddwstr(y, x, L"♙");
    move(0, 0);
}

void desenhar_torre(int y, int x) {
    mvaddwstr(y, x, L"♜");
    move(0, 0);
}

void desenhar_cavalo(int y, int x) {
    mvaddwstr(y, x, L"♞");
    move(0, 0);
}

void desenhar_bispo(int y, int x) {
    mvaddwstr(y, x, L"♝");
    move(0, 0);
}

void desenhar_rainha(int y, int x) {
    mvaddwstr(y, x, L"♛");
    move(0, 0);
}

void desenhar_rei(int y, int x) {
    mvaddwstr(y, x, L"♚");
    move(0, 0);
}

void desenhar_peca(int y, int x, int tipo, int cor, int cursor_y, int cursor_x, int selecionado_y, int selecionado_x) {
    if (tipo == VAZIO) return;

    cor_peca(cor, y, x, cursor_y, cursor_x, selecionado_y, selecionado_x);

    int screen_y = MARGEM_Y + (y * ALTURA_CASA) + 0;
    int screen_x = MARGEM_X + (x * LARGURA_CASA) + 0;

    //attron(A_BOLD);

    switch (tipo) {
        case PEAO: desenhar_peao(screen_y, screen_x); break;
        case TORRE: desenhar_torre(screen_y, screen_x); break;
        case CAVALO: desenhar_cavalo(screen_y, screen_x); break;
        case BISPO: desenhar_bispo(screen_y, screen_x); break;
        case RAINHA: desenhar_rainha(screen_y, screen_x); break;
        case REI: desenhar_rei(screen_y, screen_x); break;
    }

    //attroff(A_BOLD);

    attroff(COLOR_PAIR(3));
    attroff(COLOR_PAIR(4));
    attroff(COLOR_PAIR(5));
    attroff(COLOR_PAIR(6));
}