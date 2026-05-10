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

    
    inicializar_cores();
    inicializar_jogo();
    desenhar_grelha();

    mvprintw(MARGEM_Y + (8 * ALTURA_CASA) + 1, MARGEM_X, "Pressiona qualquer tecla para sair...");

    refresh();
    
    getch();
    endwin();

    return 0;
}
