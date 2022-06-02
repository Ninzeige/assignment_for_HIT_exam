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
    oper_bar_init(yMax, xMax);
    int sub_num = show_input_box(yMax, xMax, "input subject number", TYPE_NUMERIC); // 获取科目数量
    int stu_num = show_input_box(yMax, xMax, "input student number", TYPE_NUMERIC); // 获取学生数量
    MainWin *main_win = new_main_win(yMax, xMax, sub_num, stu_num);
    show_help_win(yMax, xMax);
    main_oper(main_win);

    endwin();

    return 0;
}
