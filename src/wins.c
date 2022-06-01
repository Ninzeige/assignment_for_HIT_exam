#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>
#include <form.h>
#include "wins.h"
#include "controls.h"
#include "interface.h"

#define MIN_X 100
#define MIN_Y 40

#define TABLE_WIN 0
#define COMMAND_WIN 1
#define COW_WIN 2

#define MAIN_GUIDE 0
#define TABLE_GUIDE 1
#define COW_GUIDE 2
#define COMMAND_GUIDE 3
#define FORTURE 4

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
    initialize_colors();
    box(splash_scr, 0, 0);
    mvwprintw(splash_scr, 1, (max_x - 66) / 2, "               _/    _/  _/_/_/  _/_/_/_/_/");
    mvwprintw(splash_scr, 2, (max_x - 66) / 2, "              _/    _/    _/        _/     ");
    mvwprintw(splash_scr, 3, (max_x - 66) / 2, "             _/_/_/_/    _/        _/      ");
    mvwprintw(splash_scr, 4, (max_x - 66) / 2, "            _/    _/    _/        _/       ");
    mvwprintw(splash_scr, 5, (max_x - 66) / 2, "Welcome to _/    _/  _/_/_/      _/       Grade Management system!");

    wattr_set(splash_scr, A_NORMAL, blue_color, NULL);
    wprintw_hit_logo(splash_scr, 7, (max_x - 49) / 2);
    wattr_set(splash_scr, A_NORMAL, -1, NULL);
    mvwprintw(splash_scr, 22, 1, "Author: Chen Han, Harbin Institute of Technology, width22/5");
    mvwprintw(splash_scr, 23, 1, "press any key to start...");
    refresh();
    wrefresh(splash_scr);
    getch();
    delwin(splash_scr);
    clear();
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
    int x2 = width - 15;
    highlight_buttom(inner_border, height - 5, &x2, "OK");

    int bar_x = 0;
    info_bar_wprint(oper_bar, "Enter", "Confirm", &bar_x);

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
    clear();
    refresh();
    return;
}


WINDOW* show_cow(int max_y, int max_x)
{
    curs_set(0);
    WINDOW *cow_win = newwin(10, 36, max_y - 15, max_x - 39);
    box(cow_win, 0, 0);
    cow_say(cow_win, "", '@', ' ');
    refresh();
    wrefresh(cow_win);
    getch();
}

void cow_say(WINDOW *win, char* word, char eye, char togue)
{
    int x, y;
    y = 9;
    // getyx(win, y, x);
    y -= 1;
    x = 1;

    mvwprintw(win, y--, 1, "                ||     ||");
    mvwprintw(win, y--, 1, "                ||----w |");
    mvwprintw(win, y--, 1, "            (__)\\       )\\/\\");
    mvwprintw(win, y, 1, "         \\  (");
    x += 13;
    mvwprintw(win, y, x, "%c%c", eye, eye);
    x += 2;
    mvwprintw(win, y--, x, ")\\_______");
    x = 1;
    mvwprintw(win, y--, 1, "        \\   ^__^");
}

CommandWin *new_command_win(int height, int width, int start_y, int start_x)
{
    WINDOW *command_win = newwin(height, width, start_y, start_x);
    CommandWin *new_win = (CommandWin *)malloc(sizeof(CommandWin));
    new_win->buffer_size = 19;
    new_win->input = (char *)malloc(sizeof(char) * new_win->buffer_size);
    return new_win;
}

CowWin *new_cow_win(int height, int width, int start_y, int start_x)
{
    WINDOW *cow_win = newwin(height, width, start_y, start_x);
    CowWin *res = (CowWin *)malloc(sizeof(CowWin));
    res->win = cow_win;
    res->word_id = MAIN_GUIDE;
    return res;
}

TableWin *new_table_win(int height, int width, int start_y, int start_x)
{
    WINDOW *table_win = newwin(height, width, start_y, start_x);
    // ask the user to input the subject number
    
    TableWin *res = (TableWin *)malloc(sizeof(TableWin));
    res->row = 0;
    res->col = 0;
    res->max_col = width - 3;
    res->max_row = height - 3;
}

MainWin *new_main_win(int max_y, int max_x)
{
    MainWin *result = (MainWin *)malloc(sizeof(MainWin));
    result->command_win = new_command_win(3, max_x - 5, max_y - 5, 2);
    result->cow_win = new_cow_win(10, 30, max_y - 16, max_x - 19);
    result->table_win = new_table_win(max_y - 14, max_x - 32, 0, 0);
    result->max_x = max_x;
    result->max_y = max_y;
    return result;
}

void main_win_show(MainWin *main_win)
{
    char input = 0;

    while (input != 27)
    {

        switch (main_win->select_win)
        {
        case TABLE_WIN:
            show_table_win(main_win->table_win, 1);
            show_cow_win(main_win->cow_win, 0);
            show_command_win(main_win->command_win, 0);
            break;
        case COW_WIN:
            show_table_win(main_win->table_win, 0);
            show_cow_win(main_win->cow_win, 1);
            show_command_win(main_win->command_win, 0);
            break;
        case COMMAND_WIN:
            show_table_win(main_win->table_win, 0);
            show_cow_win(main_win->cow_win, 0);
            show_command_win(main_win->command_win, 1);
            break;
        default:
            show_table_win(main_win->table_win, 0);
            show_cow_win(main_win->cow_win, 0);
            show_command_win(main_win->command_win, 0);
            break;
        }
    }
}


void command_operate(CommandWin *com_win)
{
    echo();
    noraw();
    keypad(com_win->win, true);
    int input = 0;
    while (input != 27 || input != '\n')
    {
        input = wgetch(com_win->win);
    }

    noecho();
    keypad(com_win->win, false);
}

void table_operate(TableWin *tab_win)
{
    keypad(tab_win->win, true);
    int input = 0;

    // moving curses around
    while (input != 27 && input != '\n')
    {
        input = wgetch(tab_win->win);
        switch (input)
        {
        case KEY_UP:
            if (tab_win->row > 0)
            {
                tab_win->row += -1;
            }
            break;
        case KEY_DOWN:
            if (tab_win->row < tab_win->max_row - 1)
            {
                tab_win->row += 1;
            }
            break;
        case KEY_LEFT:
            if (tab_win->col > 0)
            {
                tab_win->col += -1;
            }
            break;
        case KEY_RIGHT:
            if (tab_win->col < tab_win->max_col - 1)
            {
                tab_win->col += -1;
            }
            break;
        default:
            break;
        }
    }

    // enroll data
    if (input == '\n')
    {
        
        table_operate(tab_win);
        return;
    }
    else
    {
        return;
    }
}

bool show_message_box(int max_y, int max_x, char *str)
{
    int const width = 30;
    int length = strlen(str);
    int lines = length / width + 1;              // how many lines to be printed
    char *output = (char *)malloc(sizeof(char) * (lines * (width + 1)));
    if (length > width)
    {
        lines = length / width + 1;
        for (int i = 0; i < lines; i++)
        {
            for (int j = 0; j < width; j++)
            {
                output[i * (width + 1) + j] = str[i * width + j];
                if (str[i * width + j] == '\0')
                {
                    break;
                }
            }
            output[(i + 1) * width + 1 - 1] = '\0';
        }
    }
    int x = 0;
    info_bar_wprint(oper_bar, "OK", "Comfirm", &x);
    info_bar_wprint(oper_bar, "Left/Right", "Switch", &x);
    WINDOW *msg_box = newwin(lines + 4, width + 6, (max_y - lines - 3) / 2, (max_x - 22) / 2);
    bool selected = true;   // the selected option, true = OK, false = cancel
    box(msg_box, 0, 0);

    for (int i = 0; i < lines; i++)
    {
        mvwprintw(msg_box, i + 1, 3, "%s", output + (width + 1) * i);
    }
    
    x = width - 14;
    buttom(msg_box, lines + 2, &x, "Cancel");
    highlight_buttom(msg_box, lines + 2, &x, "OK");
    refresh();
    wrefresh(msg_box);
    
    keypad(msg_box, true);
    noecho();
    int input = wgetch(msg_box);
    refresh();

    while (input != '\n')
    {
        if (input == KEY_LEFT)
        {   
            selected = false;
            x = width - 14;
            highlight_buttom(msg_box, lines + 2, &x, "Cancel");
            buttom(msg_box, lines + 2, &x, "OK");
        }
        else if (input == KEY_RIGHT)
        {
            selected = true;
            x = width - 14;
            buttom(msg_box, lines + 2, &x, "Cancel");
            highlight_buttom(msg_box, lines + 2, &x, "OK");
        }
        wrefresh(msg_box);
        input = wgetch(msg_box);
    }

    keypad(msg_box, false);
    free(output);
    delwin(msg_box);
    wclear(oper_bar);
    refresh();
    return selected;
}

void show_table_win(TableWin *tab_win, int highlight)
{
    if(highlight)
    {
        wattr_set(tab_win->win, A_NORMAL, cyan_color, NULL);
        box(tab_win->win, 0, 0);
        wattr_set(tab_win->win, A_NORMAL, -1, NULL);
    }
    else
    {
        box(tab_win->win, 0, 0);
    }
    wrefresh(tab_win->win);
}
void show_cow_win(CowWin *cow_win, int highlight)
{
    if(highlight)
    {
        wattr_set(cow_win->win, A_NORMAL, cyan_color, NULL);
        box(cow_win->win, 0, 0);
        wattr_set(cow_win->win, A_NORMAL, -1, NULL);
    }
    else
    {
        box(cow_win->win, 0, 0);
    }
    wrefresh(cow_win->win);
}
void show_command_win(CommandWin *com_win, int highlight)
{
    if(highlight)
    {
        wattr_set(com_win->win, A_NORMAL, cyan_color, NULL);
        box(com_win->win, 0, 0);
        wattr_set(com_win->win, A_NORMAL, -1, NULL);
    }
    else
    {
        box(com_win->win, 0, 0);
    }
    wrefresh(com_win->win);
}

void main_oper(MainWin *main_win)
{

}


int show_input_box(int max_y, int max_x, char *info, FIELDTYPE *type)
{   
    int length = strlen(info);

    const int height = 5;

    curs_set(1);
    WINDOW *win = newwin(height, length + 5, (max_y - height) / 2, (max_x - length - 5) / 2);
    box(win, 0, 0);
    FIELD *input[2];
    input[0] = new_field(1, 17, 0, 0, 0, 0);
    input[1] = new_field(1, 7, 2, 0, 0, 0);
    input[2] = NULL;

    set_field_buffer(input[0], 0, info);
    set_field_buffer(input[1], 0, "");
    
    set_field_opts(input[0], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(input[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);

    set_field_back(input[1], A_UNDERLINE);
    keypad(win, true);
    noecho();
    noraw();
    cbreak();

    if (type == TYPE_NUMERIC)
    {
        set_field_type(input[1], type, 1, 0, INTMAX_MAX); // to be filled
    }

    FORM *form = new_form(input);
    set_form_win(form, win);
    set_form_sub(form, derwin(win, height - 2, length + 2, 1, 1));
    post_form(form);

    refresh();
    wrefresh(win);

    int _input = getch();
    int result = 0;

    form_driver(form, REQ_NEXT_FIELD);
    while (true)
    {
        noraw();
        noecho();
        cbreak();
        if (_input == '\n')
        {
            if (field_buffer(input[1], 0) == "invalid!")
            {
                form_driver(form, REQ_DEL_LINE);
            }
            int i = 0;
            char *str = trim_whitespaces(field_buffer(input[1], 0));
            int is_num = 1;
            for (i = 0; str[i]; i++)
            {
                if (!isdigit(str[i]))
                {
                    is_num = 0;
                    break;
                }
            }
            if (is_num && i)
            {
                printf("the i = %d", i);
                break;
            }
            else
            {
                set_field_buffer(input[1], 0, "invalid!");
            }
        }
        driver(_input, form, input);
        wrefresh(win);
        _input = getch();
    }

    unpost_form(form);
    free_form(form);
    for (int i = 0; i < 2; i++)
    {
        free_field(input[i]);
    }
    delwin(win);

}

