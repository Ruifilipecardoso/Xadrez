#include <ncurses.h>

int main() {
    initscr();

    raw();
    noecho();
    keypad(stdscr, true);
    curs_set(0);
}