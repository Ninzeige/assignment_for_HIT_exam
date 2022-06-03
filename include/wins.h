#ifndef HIT_WINS_H_
#define HIT_WINS_H_
#include <ncurses.h>
#include <form.h>
#include "student.h"

extern WINDOW *oper_bar;

enum word_ids
{
    MAIN_GUIDE = 0,
    TABLE_GUIDE,
    COW_GUIDE,
    COMMAND_GUIDE,
    FORTUNE1,
    FORTUNE2,
    FORTUNE3,
    FORTUNE4,
    NOSTUDY,
    STUDY,
    LOVE_HIT,
    TOTAL,
};



typedef struct
{
    WINDOW *win;
    int word_id;
    const char *words[TOTAL];
}CowWin;

typedef struct 
{
    WINDOW *win;
    int row;    // the position focus on
    int col;
    char **subject_name;
    student **stu;
    int max_col;
    int max_row;
    int stu_num;
    int actual_num; // 实际登记的学生成绩数量
    int sub_num;
    int start_row;  // 当学生记录太多的时候选择开始展示的位置
    int start_col;  // 当科目太多的时候...
}TableWin;

typedef struct
{
    WINDOW *win;
    char* input;
    int input_num;
    int buffer_size;
}CommandWin;
typedef struct
{
    WINDOW *win;
    
}OutputWin;

typedef struct
{
    CowWin *cow_win;
    TableWin *table_win;
    CommandWin *command_win;
    OutputWin *output_win;
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
int show_numeric_input_box(int max_y, int max_x, char *info, FIELDTYPE *type);
void show_input_str_box(int max_y, int max_x, char *info, char *dest);
void show_message_box_without_select(int max_y, int max_x, char *str);
void cow_say(WINDOW *win, const char *word, char eye);
void show_output_win(OutputWin *output_win);
void show_main_win(MainWin *main_win);
void flush_box_win(WINDOW *win);

CommandWin *new_command_win(int height, int width, int start_y, int start_x);
TableWin *new_table_win(int height, int width, int start_y, int start_x, int sub_num, int stu_num);
CowWin *new_cow_win(int height, int width, int start_y, int start_x);
MainWin *new_main_win(int max_y, int max_x, int sub_num, int stu_num);

void command_operate(CommandWin *com_win, MainWin *main_win);
void cow_operate(CowWin *cow_win);
void table_operate(TableWin *tab_win);
void main_oper(MainWin *main_win);
void listen_to_cow(CowWin *cow_win);

void show_info(OutputWin *output_win, char *str);
void main_win_show(MainWin *main_win);


#endif /* HIT_WINS_H_ */