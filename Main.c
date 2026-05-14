#define NCURSES_STATIC
#include <ncursesw/ncurses.h>
#include <locale.h>
#include <windows.h>
#include "Tabuleiro.h"
#include "Pecas.h"
#include "Jogo.h"

int main() {
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "");
    
    initscr();
    start_color();
    can_change_color();

    cbreak();

    //raw();
    noecho();
    keypad(stdscr, TRUE);
    //curs_set(0);
    clear();

    int ch;
    int cursor_y = 0, cursor_x = 0;
    int selecionado_y = -1, selecionado_x = -1;

    
    inicializar_cores();
    inicializar_jogo();
    desenhar_grelha(cursor_y, cursor_x, selecionado_y, selecionado_x);

    

    keypad(stdscr, TRUE);

    while(1) {

        mostrar_status();
        desenhar_grelha(cursor_y, cursor_x, selecionado_y, selecionado_x);
        refresh();


        ch = getch();
        if (ch == 'q') break;

        switch(ch) {
            case KEY_UP: if(cursor_y > 0) cursor_y--; break;
            case KEY_DOWN: if(cursor_y < 7) cursor_y++; break;
            case KEY_LEFT: if(cursor_x > 0) cursor_x--; break;
            case KEY_RIGHT: if(cursor_x < 7) cursor_x++; break;

            case '\n': 
                if(selecionado_x == -1) {
                    //Selecionar Peça
                    selecionado_y = cursor_y;
                    selecionado_x = cursor_x;
                } else {
                    if (validar_movimento(selecionado_y, selecionado_x, cursor_y, cursor_x) == 1) {
                        //--- Simulação de Xeque ---
                        //Guardar o estado original das duas casas envolvidas
                        int peca_origem = tabuleiro_estado[selecionado_y][selecionado_x];
                        int peca_destino = tabuleiro_estado[cursor_y][cursor_x];

                        //Jogada fantasma
                        tabuleiro_estado[cursor_y][cursor_x] = peca_origem;
                        tabuleiro_estado[selecionado_y][selecionado_x] = VAZIO;

                        //Localização do Rei
                        int rei_y, rei_x;
                        encontrar_rei(turno_atual, &rei_y, &rei_x);

                        //Verificar se Xeque
                        int rei_em_xeque = xeque(rei_y, rei_x, turno_atual);

                        //Desfazer a jogada fantasma
                        tabuleiro_estado[selecionado_y][selecionado_x] = peca_origem;
                        tabuleiro_estado[cursor_y][cursor_x] = peca_destino;
                        //--- Fim da simulação ---

                        if (rei_em_xeque == 1) {
                            mvprintw(1, 5, "MOVIMENTO ILEGAL: REI EM XEQUE!");
                        } else {
                            //Mover Peça
                            mover_peca(selecionado_y, selecionado_x, cursor_y, cursor_x);
                            mvprintw(1, 5, "                               ");
                        }
                        
                        selecionado_x = -1;
                        
                    } else {
                        selecionado_x = -1;
                    }
                    
                }
                break;
        }
        

        
    }

    mvprintw(MARGEM_Y + (8 * ALTURA_CASA) + 1, MARGEM_X, "Pressiona qualquer tecla para sair...");

    refresh();
    
    getch();
    endwin();

    return 0;
}
