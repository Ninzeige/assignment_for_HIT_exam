#ifndef HIT_WINS_H_
#define HIT_WINS_H_
#include <ncurses.h>

extern WINDOW *oper_bar;


typedef struct
{
    WINDOW *win;
    int word_id;
    
}CowWin;

typedef struct 
{
    WINDOW *win;
}TableWin;

typedef struct
{
    WINDOW *win;
    char* input;
    int buffer_size;
}CommandWin;

typedef struct
{
    CowWin *cow_win;
    TableWin *table_win;
    CommandWin *command_win;
    int select_win;
}MainWin;


void wprintw_hit_logo(WINDOW *win, int start_y, int start_x);
void oper_bar_init(int max_y, int max_x);

int show_splash_win(int max_y, int max_x);
void show_help_win(int max_y, int max_x);
WINDOW* show_command_win(int max_y, int max_x);
WINDOW* show_cow(int max_y, int max_x);
void cow_say(WINDOW *win, char* word, char eye, char togue);

CommandWin *new_command_win(int max_y, int max_x);
TableWin *new_table_win(int max_y, int max_x);
CowWin *new_cow_win(int max_y, int max_x);
MainWin *new_main_win(int max_y, int max_x);

void *main_win_show(MainWin *main_win);

#endif /* HIT_WINS_H_ */