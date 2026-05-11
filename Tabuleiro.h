#define NCURSES_STATIC
#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <ncurses.h>

#define LARGURA_CASA 2
#define ALTURA_CASA 1
#define MARGEM_Y 2
#define MARGEM_X 5

void inicializar_cores();
void desenhar_grelha(int cursor_y, int cursor_x, int selecionado_y, int selecionado_x);

#endif