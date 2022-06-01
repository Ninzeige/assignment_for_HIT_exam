#include <ncurses.h>
#include <locale.h>
#include "wins.h"
#include "interface.h"

int main(int argc, char **argv)
{   
    initialize_colors();
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    curs_set(0);
    
    cbreak();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    if (!show_splash_win(yMax, xMax)) { return -1; };
    show_input_box(yMax, xMax, "input subject number", TYPE_NUMERIC);
    oper_bar_init(yMax, xMax);
    MainWin *main_win = new_main_win(yMax, xMax);
    show_help_win(yMax, xMax);
    endwin();

    return 0;
}
