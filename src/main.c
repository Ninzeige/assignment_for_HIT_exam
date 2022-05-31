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

    if (!show_splash_win(yMax, xMax)) { return -1; };
    oper_bar_init(yMax, xMax);
    // MainWin *main_win = new_main_win(yMax, xMax);
    show_message_box(yMax, xMax, "Hello msg box! this is nzg, subject.hhhhh");
    show_help_win(yMax, xMax);
    // show_command_win(yMax, xMax);
    // show_cow(yMax, xMax); 
    
    endwin();

    return 0;
}
