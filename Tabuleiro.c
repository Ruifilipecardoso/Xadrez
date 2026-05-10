#define NCURSES_STATIC
#include <ncurses.h>
#include <locale.h>
#include <windows.h>
#include "Tabuleiro.h"
#include "Jogo.h"
#include "Pecas.h"


//Cores
void inicializar_cores() {
    start_color();
    use_default_colors();
    
    init_pair(1, COLOR_WHITE, COLOR_BLUE);

    init_pair(2, COLOR_WHITE, COLOR_WHITE);

    //Com as peças brancas
    init_pair(3, COLOR_YELLOW, COLOR_BLUE);
    init_pair(4, COLOR_YELLOW, COLOR_WHITE);

    //Com as peças pretas
    init_pair(5, COLOR_RED, COLOR_BLUE);
    init_pair(6, COLOR_RED, COLOR_WHITE);
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
                mvprintw(MARGEM_Y + (y * ALTURA_CASA) + i, MARGEM_X + (x * LARGURA_CASA), "  ");
            }

            attroff(COLOR_PAIR(1));
            attroff(COLOR_PAIR(2));

            int peca_valor = tabuleiro_estado[y][x];

            if (peca_valor != VAZIO) {
                int tipo = peca_valor % 10;
                int cor = (peca_valor >= 20) ? PRETO : BRANCO;


                desenhar_peca(y, x, tipo, cor);
            }


        }
    }
}
