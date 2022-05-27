#include "wins.h"
#include "ncurses.h"
#include "controls.h"

#define MIN_X 100
#define MIN_Y 40

WINDOW *oper_bar = NULL;    // 底部栏, 用于提示现在可用的操作

void oper_bar_init(int max_y, int max_x)
{
    if (oper_bar != NULL)
    {
        return;
    }

    oper_bar = newwin(max_y, max_x, max_y - 1, 0);
}

void wprintw_hit_logo(WINDOW *win, int start_y, int start_x)
{
    mvwprintw(win, start_y, start_x, "                        o");
    mvwprintw(win, start_y + 1, start_x, "                        v");
    mvwprintw(win, start_y + 2, start_x, "                        │");
    mvwprintw(win, start_y + 3, start_x, "                        │");
    mvwprintw(win, start_y + 4, start_x, "                        ╪");
    mvwprintw(win, start_y + 5, start_x, "                       ╓║╖");
    mvwprintw(win, start_y + 6, start_x, "                      ╓║║║╖");
    mvwprintw(win, start_y + 7, start_x, "            ◢════════╓║║║║║╖════════◣");
    mvwprintw(win, start_y + 8, start_x, "◢═ ═╱ ╲═ ═ ═╣▓ ▓ ▓ ▓ ║║║║║║║ ▓ ▓ ▓ ▓╠═ ═ ═╱ ╲═ ═◣");
    mvwprintw(win, start_y + 9, start_x, "║░░░░░░░░░░░║▓ ▓ ▓ ▓ ══===══ ▓ ▓ ▓ ▓║░░░░░░░░░░░║");
    mvwprintw(win, start_y + 10, start_x, "║░░░░░░░░░░░║▓ ▓ ▓ ▓ ▌█ █ █▐ ▓ ▓ ▓ ▓║░░░░░░░░░░░║");
    mvwprintw(win, start_y + 11, start_x, "═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═");
}

/**
 * @brief 打印欢迎界面
 * 
 * @return 是否可以正常运行
 */
int show_splash_win(int max_y, int max_x)
{
    /* 确保整个程序运行的时候具有足够的空间打印字符 */
    if (max_x < MIN_X || max_y < MIN_Y)
    {
        WINDOW *splash_src = newwin(max_y, max_x, 0, 0);
        box(splash_src, 0, 0);
        refresh();
        wrefresh(splash_src);
        mvprintw(max_y / 2 - 1, (max_x - 49) / 2, "the window size is not enough for starting the software,");
        mvprintw(max_y / 2, (max_x - 49) / 2, "please resize the window,");
        mvprintw(max_y / 2 + 1, (max_x - 49) / 2, "at least %d characters width and %d chars height", MIN_X, MIN_Y);
        mvprintw(max_y / 2 + 2, (max_x - 49) / 2, "press any key to quit...");
        getch();
        return false;
    }
    WINDOW *splash_scr = newwin(25, max_x - 6, (max_y - 25) / 2, 4);
    box(splash_scr, 0, 0);
    mvwprintw(splash_scr, 1, (max_x - 66) / 2, "               _/    _/  _/_/_/  _/_/_/_/_/");
    mvwprintw(splash_scr, 2, (max_x - 66) / 2, "              _/    _/    _/        _/     ");
    mvwprintw(splash_scr, 3, (max_x - 66) / 2, "             _/_/_/_/    _/        _/      ");
    mvwprintw(splash_scr, 4, (max_x - 66) / 2, "            _/    _/    _/        _/       ");
    mvwprintw(splash_scr, 5, (max_x - 66) / 2, "Welcome to _/    _/  _/_/_/      _/       Grade Management system!");

    wprintw_hit_logo(splash_scr, 7, (max_x - 49) / 2);
    mvwprintw(splash_scr, 22, 1, "Author: Chen Han, Harbin Institute of Technology, 2022/5");
    mvwprintw(splash_scr, 23, 1, "press any key to start...");
    refresh();
    wrefresh(splash_scr);
    getch();
    delwin(splash_scr);
    return true;
}

void show_help_win(int max_y, int max_x)
{
    int height = 35; int width = 72;
    WINDOW *out_border = newwin(height, width, (max_y - 3 - height) / 2, (max_x - width) / 2);
    WINDOW *inner_border = newwin(height - 2, width - 2, (max_y - 3 - height) / 2 + 1, (max_x - width) / 2  +1);
    box(out_border, 0, 0);
    box(inner_border, 0, 0);

    int x = 1;
    mvwprintw(inner_border, x++, 1, "   __       __ ");
    mvwprintw(inner_border, x++, 1, "  / /  ___ / /__ ");
    mvwprintw(inner_border, x++, 1, " / _ \\/ -_) / _ \\");
    mvwprintw(inner_border, x++, 1, "/_//_/\\__/_/ .__/");
    mvwprintw(inner_border, x++, 1, "          /_/  ");
    x++;

    mvwprintw(inner_border, x++, 1, " 1. Input record");
    mvwprintw(inner_border, x++, 1, " 2. Calculate total and average score of every course");
    mvwprintw(inner_border, x++, 1, " 3. Calculate total and average score of every student");
    mvwprintw(inner_border, x++, 1, " 4. Sort in descending order by total score of every student");
    mvwprintw(inner_border, x++, 1, " 5. Sort in ascending order by total score of every student");
    mvwprintw(inner_border, x++, 1, " 6. Sort in ascending order by number");
    mvwprintw(inner_border, x++, 1, " 7. Sort in dictionary order by name");
    mvwprintw(inner_border, x++, 1, " 8. Search by number");
    mvwprintw(inner_border, x++, 1, " 9. Search by name");
    mvwprintw(inner_border, x++, 1, " 10, Statistic analysis for every course");
    mvwprintw(inner_border, x++, 1, " 11. List record");
    mvwprintw(inner_border, x++, 1, " 12. Write to a file");
    mvwprintw(inner_border, x++, 1, " 13. Read from a file");
    mvwprintw(inner_border, x++, 1, " 0. Exit");
    mvwprintw(inner_border, x++, 1, " h. Show this help again");
    highlight_buttom(inner_border, height - 5, width  -15, "OK");

    int bar_x = 0;
    info_bar_wprint(oper_bar, "Enter", "Confirm", 1, &bar_x);

    refresh();
    wrefresh(out_border);
    wrefresh(inner_border);
    int input = 0;
    do
    {
        input = getch();
    } while (input != '\n');
    delwin(out_border);
    delwin(inner_border);
    
    return;
}