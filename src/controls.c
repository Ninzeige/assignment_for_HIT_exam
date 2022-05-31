#include "controls.h"
#include <string.h>

void highlight_buttom(WINDOW *win, int y, int *x, char *str)
{
    wattron(win, A_REVERSE);
    mvwprintw(win, y, *x, "[ ");
    *x += 2;
    mvwprintw(win, y, *x, str);
    *x += strlen(str);
    mvwprintw(win, y, *x, " ]");
    wattroff(win, A_REVERSE);
    *x += 3;
}

void buttom(WINDOW *win, int y, int *x, char *str)
{
    mvwprintw(win, y, *x, "[ ");
    *x += 2;
    mvwprintw(win, y, *x, str);
    *x += strlen(str);
    mvwprintw(win, y, *x, " ]");
    *x += 3;
}

/**
 * @brief helper method: 打印底部操作提示, 打印效果如: "[ Enter ] Comfirm   [ Tab ] Move around"
 * 
 * @param bar 底部的窗口
 * @param operation 按键
 * @param info 操作的内容
 * @param num 数组长度
 * @param x 打印的x坐标
 */
void info_bar_wprint(WINDOW *bar,char *operation, char *info, int *x)
{
    mvwprintw(bar, 0, *x, " [ ");
    *x += 3;
    mvwprintw(bar, 0, *x, "%s", operation);
    *x += strlen(operation);
    mvwprintw(bar, 0, *x, " ] ");
    *x += 3;
    mvwprintw(bar, 0, *x, "%s", info);
    *x += strlen(info);
    mvwprintw(bar, 0, *x, "   ");
    *x += 3;
    refresh();
    wrefresh(bar);
}
