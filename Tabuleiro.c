#define NCURSES_STATIC
#include <ncurses.h>

int main() {
    initscr();

    raw();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    getch();
    endwin();
}