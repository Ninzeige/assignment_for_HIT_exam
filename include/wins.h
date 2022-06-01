#ifndef HIT_WINS_H_
#define HIT_WINS_H_
#include <ncurses.h>
#include <form.h>

extern WINDOW *oper_bar;


typedef struct
{
    WINDOW *win;
    int word_id;
    
}CowWin;

typedef struct 
{
    WINDOW *win;
    int row;    // the position focus on
    int col;
    char **subject_name;
    int max_col;
    int max_row;
    FIELD *charts;  // 记录学生的成绩
    FORM *form;
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
    int max_x, max_y;
}MainWin;

bool show_message_box(int max_y, int max_x, char *str);

void wprintw_hit_logo(WINDOW *win, int start_y, int start_x);
void oper_bar_init(int max_y, int max_x);

int show_splash_win(int max_y, int max_x);
void show_help_win(int max_y, int max_x);
void show_table_win(TableWin *tab_win, int highlight);
void show_cow_win(CowWin *cow_win, int highlight);
void show_command_win(CommandWin *com_win, int highlight);
int show_input_box(int max_y, int max_x, char *info, FIELDTYPE *type);
void cow_say(WINDOW *win, char *word, char eye, char togue);

CommandWin *new_command_win(int height, int width, int start_y, int start_x);
TableWin *new_table_win(int height, int width, int start_y, int start_x);
CowWin *new_cow_win(int height, int width, int start_y, int start_x);
MainWin *new_main_win(int max_y, int max_x);

void command_operate(CommandWin *com_win);
void cow_operate(CowWin *cow_win);
void table_operate(TableWin *tab_win);
void main_oper(MainWin *main_win);

void main_win_show(MainWin *main_win);

#endif /* HIT_WINS_H_ */