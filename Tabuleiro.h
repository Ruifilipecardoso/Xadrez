#define NCURSES_STATIC
#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <ncurses.h>

#define LARGURA_CASA 6
#define ALTURA_CASA 3
#define MARGEM_Y 2
#define MARGEM_X 5

void inicializar_cores();
void desenhar_grelha();

#endif