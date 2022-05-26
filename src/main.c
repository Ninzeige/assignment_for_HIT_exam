#include <ncurses.h>
#include <locale.h>
#include "wins.h"

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    curs_set(0);
    
    cbreak();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    show_splash_win(yMax, xMax);
    show_help_win(yMax, xMax);
    endwin();

    return 0;
}
