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

                    int peca_selecionada = tabuleiro_estado[selecionado_y][selecionado_x];
                    int tipo_peca = peca_selecionada % 10;

                    //Tentativa de Roque
                    int cor_rei = (peca_selecionada >= 20) ? PRETO : BRANCO;
                    if (cor_rei == turno_atual && tipo_peca == REI && abs(cursor_x - selecionado_x) == 2) {
                        if (validar_roque(selecionado_y, selecionado_x, cursor_y, cursor_x) == 1) {
                            mover_peca(selecionado_y, selecionado_x, cursor_y, cursor_x);

                            if (cursor_x == 6) {
                                    tabuleiro_estado[cursor_y][5] = tabuleiro_estado[cursor_y][7];
                                    tabuleiro_estado[cursor_y][7] = VAZIO;
                                }
                            if (cursor_x == 2) {
                                tabuleiro_estado[cursor_y][3] = tabuleiro_estado[cursor_y][0];
                                tabuleiro_estado[cursor_y][0] = VAZIO;
                            }

                            mvprintw(1, 5, "                               ");

                            if (xeque_mate(turno_atual) == 1) {
                                erase();
                                mvprintw(4, 5, "=================================");
                                if (turno_atual == BRANCO) {
                                    mvprintw(5, 5, "XEQUE-MATE! VITORIA DAS PRETAS! ");
                                } else {
                                    mvprintw(5, 5, "XEQUE-MATE! VITORIA DAS BRANCAS!");
                                }
                                mvprintw(6, 5, "=================================");
                                refresh();
                                getch();
                                break;
                            }

                        } else {
                            mvprintw(1, 5, "MOVIMENTO ILEGAL: ROQUE INVALIDO!");
                        }

                        selecionado_x = -1;
                    } else {

                    }

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

                            int peca_movida = tabuleiro_estado[cursor_y][cursor_x];

                            if (peca_movida % 10 == PEAO && abs(cursor_x - selecionado_x) == 1 && peca_destino == VAZIO) {
                                tabuleiro_estado[selecionado_y][cursor_x] = VAZIO;
                            }

                            mvprintw(1, 5, "                               ");

                            if (xeque_mate(turno_atual) == 1) {
                                erase();
                                mvprintw(4, 5, "=================================");
                                if (turno_atual == BRANCO) {
                                    mvprintw(5, 5, "XEQUE-MATE! VITORIA DAS PRETAS! ");
                                } else {
                                    mvprintw(5, 5, "XEQUE-MATE! VITORIA DAS BRANCAS!");
                                }
                                mvprintw(6, 5, "=================================");
                                refresh();
                                getch();
                                break;
                            }

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
