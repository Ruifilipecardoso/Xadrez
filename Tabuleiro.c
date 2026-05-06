#define NCURSES_STATIC
#include <ncurses.h>
#include <locale.h>
#include <windows.h>
#include "Tabuleiro.h"

//Estilo

#define LARGURA_CASA 6
#define ALTURA_CASA 3
#define MARGEM_Y 2
#define MARGEM_X 5

//Cores
void inicializar_cores() {
    start_color();
    //Texto preto em fundo branco
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    //Texto branco em fundo escuro
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
}

//Grelha
void desenhar_grelha() {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            //Alterna a cor com base na posição
            if ((x + y) % 2 == 0) {
                attron(COLOR_PAIR(1));
            } else {
                attron(COLOR_PAIR(2));
            }
            //Desenha a casa
            for (int i = 0; i < ALTURA_CASA; i++) {
                mvprintw(MARGEM_Y + (y * ALTURA_CASA) + i, MARGEM_X + (x * LARGURA_CASA), "      ");
            }

            attroff(COLOR_PAIR(1));
            attroff(COLOR_PAIR(2));
        }
    }
}
