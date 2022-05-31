#ifndef HIT_CTRL_H_
#define HIT_CTRL_H_

#include <ncurses.h>
#include <string.h>

void highlight_buttom(WINDOW *win, int y, int *x, char *str);
void buttom(WINDOW *win, int y, int *x, char *str);
void info_bar_wprint(WINDOW *bar,char *operation, char *info, int *x);

#endif /* HIT_CTRL_H_ */