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

    init_pair(7, COLOR_BLACK, COLOR_YELLOW);
    init_pair(8, COLOR_BLACK, COLOR_GREEN);

    //Com as peças brancas
    init_pair(3, COLOR_YELLOW, COLOR_BLUE);
    init_pair(4, COLOR_YELLOW, COLOR_WHITE);

    //Com as peças pretas
    init_pair(5, COLOR_RED, COLOR_BLUE);
    init_pair(6, COLOR_RED, COLOR_WHITE);
}

//Turnos
void mostrar_status() {
    //Apagar mensagem anterior
    move(2, 0);
    clrtoeol();

    if (turno_atual == BRANCO) {
        attron(COLOR_PAIR(4));
        mvprintw(2, 5, "VES DAS BRANCAS");
        attroff(COLOR_PAIR(4));
    } else {
        attron(COLOR_PAIR(5));
        mvprintw(2, 5, "VEZ DAS PRETAS");
        attroff(COLOR_PAIR(5));
    }

    refresh();
}

//Grelha
void desenhar_grelha(int cursor_y, int cursor_x, int selecionado_y, int selecionado_x) {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            int cor_da_casa;

            if (y == cursor_y && x == cursor_x) {
                cor_da_casa = 7;
            } else if (y == selecionado_y && x == selecionado_x) {
                cor_da_casa = 8;
            } else if ((x + y) % 2 == 0) {
                cor_da_casa = 1;
            } else {
                cor_da_casa = 2;
            }

            //Alterna a cor com base na posição

            attron(COLOR_PAIR(cor_da_casa));

            //Desenha a casa
            for (int i = 0; i < ALTURA_CASA; i++) {
                mvprintw(MARGEM_Y + (y * ALTURA_CASA) + i + 2, MARGEM_X + (x * LARGURA_CASA), "  ");
            }

            attroff(COLOR_PAIR(cor_da_casa));
            

            int peca_valor = tabuleiro_estado[y][x];

            if (peca_valor != VAZIO) {
                int tipo = peca_valor % 10;
                int cor = (peca_valor >= 20) ? PRETO : BRANCO;


                desenhar_peca(y, x, tipo, cor, cursor_y, cursor_x, selecionado_y, selecionado_x);
            }


        }
    }
}
