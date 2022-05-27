#ifndef HIT_WINS_H_
#define HIT_WINS_H_
#include <ncurses.h>

extern WINDOW *oper_bar;

void wprintw_hit_logo(WINDOW *win, int start_y, int start_x);
void oper_bar_init(int max_y, int max_x);

int show_splash_win(int max_y, int max_x);
void show_help_win(int max_y, int max_x);



#endif /* HIT_WINS_H_ */