#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>
#include <form.h>
#include "wins.h"
#include "controls.h"
#include "interface.h"
#include "operation.h"

#define MIN_X 100
#define MIN_Y 40

#define COMMAND_WIN 0
#define TABLE_WIN 1
#define COW_WIN 2

const char word_main_guide[] = "Welcom to HIT system, press 'h' for help";
const char word_command_guide[] = "This is input box, you can input command here";
const char word_cow_guide[] = "This is my box, see the guide below";
const char word_nostudy[] = "Refuse over competition and enjoy a happy life!";
const char word_study[] = "Just kidding! I will study even harder";
const char word_fortune1[] = "Aim for the moon. If you miss, you may hit a star";
const char word_fortune2[] = "You can't assume that all conditions will remain stable";
const char word_fortune3[] = "Nostalgia is living life in the past lane";
const char word_fortune4[] = "It is better to have loved and lost than just to have lost";
const char word_love_hit[] = "I love HIT!!!";

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
    flush_box_win(oper_bar);
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

void cow_say(WINDOW *win, const char* word, char eye)
{
    flush_box_win(win);
    int x, y;
    y = getmaxy(win) - 1;
    int width = getmaxx(win) - 2;
    // getyx(win, y, x);
    y -= 1;
    x = 1;

    mvwprintw(win, y--, 1, "                ||     ||");
    mvwprintw(win, y--, 1, "                ||--ww- |");
    mvwprintw(win, y--, 1, "            (__)\\       )\\/\\");
    mvwprintw(win, y, 1, "         \\  (");
    x += 13;
    mvwprintw(win, y, x, "%c%c", eye, eye);
    x += 2;
    mvwprintw(win, y--, x, ")\\_______");
    x = 1;
    mvwprintw(win, y--, 1, "        \\   ^__^");
    mvwprintw(win, y--, 1,  " --------------------------");

    int const output_width = 26;
    int length = strlen(word);
    int lines = length / output_width + 1;              // how many lines to be printed
    char *output = (char *)malloc(sizeof(char) * (lines * (output_width + 1)) + 1);
    if (length > output_width)
    {
        lines = length / output_width + 1;
        for (int i = 0; i < lines; i++)
        {
            int to_end = 0;
            for (int j = 0; j < output_width; j++)
            {
                output[i * (output_width + 1) + j] = word[i * output_width + j];
                if (word[i * output_width + j] == '\0')
                {
                    to_end = 1;
                    break;
                }
            }
            if (to_end == 1)
            {
                break;
            }
            output[(i + 1) * (output_width + 1) - 1] = '\0';

        }
        mvwprintw(win, y--, 1,  "|%-26s|", output + output_width + 1);
        mvwprintw(win, y--, 1,  "|                          |");
        mvwprintw(win, y--, 1,  "|%-26s|", output);
    
    }
    else
    {
        strcpy(output, word);
        mvwprintw(win, y--, 1, "<%-26s>", output);
    }
    mvwprintw(win, y--, 1,  " --------------------------");

    free(output);
    refresh();
    wrefresh(win);
}

CommandWin *new_command_win(int height, int width, int start_y, int start_x)
{
    WINDOW *command_win = newwin(height, width, start_y, start_x);
    CommandWin *res = (CommandWin *)malloc(sizeof(CommandWin));
    res->buffer_size = 19;
    res->win = command_win;
    res->input_num = 0;
    res->input = (char *)malloc(sizeof(char) * res->buffer_size);
    return res;
}

CowWin *new_cow_win(int height, int width, int start_y, int start_x)
{
    WINDOW *cow_win = newwin(height, width, start_y, start_x);
    CowWin *res = (CowWin *)malloc(sizeof(CowWin));
    res->win = cow_win;
    res->word_id = MAIN_GUIDE;
    res->words[MAIN_GUIDE] = word_main_guide;
    res->words[COMMAND_GUIDE] = word_command_guide;
    res->words[COW_GUIDE] = word_cow_guide;
    res->words[NOSTUDY] = word_nostudy;
    res->words[STUDY] = word_study;
    res->words[FORTUNE1] = word_fortune1;
    res->words[FORTUNE2] = word_fortune2;
    res->words[FORTUNE3] = word_fortune3;
    res->words[FORTUNE4] = word_fortune4;
    res->words[LOVE_HIT] = word_love_hit;
    return res;
}

OutputWin *new_output_win(int height, int width, int start_y, int start_x)
{
    WINDOW *output_win = newwin(height, width, start_y, start_x);
    OutputWin *res = (OutputWin *)malloc(sizeof(OutputWin));
    res->win = output_win;
    return res;
}

TableWin *new_table_win(int height, int width, int start_y, int start_x, int sub_num, int stu_num)
{
    WINDOW *table_win = newwin(height, width, start_y, start_x);
    
    TableWin *res = (TableWin *)malloc(sizeof(TableWin));
    res->row = 0;
    res->col = 0;
    res->max_col = width - 3;
    res->max_row = height - 3;
    res->win = table_win;
    res->stu_num = stu_num;
    res->sub_num = sub_num;
    res->subject_name = (char **)malloc(sizeof(char *) * sub_num);
    res->stu = (student **)malloc(sizeof(student*) * stu_num);
    for (int i = 0; i < sub_num; i++)
    {
        res->subject_name[i] = (char *)malloc(sizeof(char) * 12);
    }
    for (int i = 0; i < stu_num; i++)
    {
        res->stu[i] = new_student(sub_num);
    }
    res->actual_num = 0;
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    for (int i = 0; i < sub_num; i++)
    {
        char buffer[60];
        sprintf(buffer, "please input subject name, (%d of %d)", i + 1, sub_num);
        show_input_str_box(max_y, max_x, buffer, res->subject_name[i]);
    }
    return res;
}

MainWin *new_main_win(int max_y, int max_x, int sub_num, int stu_num)
{
    MainWin *result = (MainWin *)malloc(sizeof(MainWin));
    result->command_win = new_command_win(3, max_x - 5, max_y - 5, 2);
    result->cow_win = new_cow_win(12, 30, max_y - 18, max_x - 33);
    result->table_win = new_table_win(max_y - 19, max_x - 5, 1, 2, sub_num, stu_num);
    result->output_win = new_output_win(12, max_x - 37, max_y - 18, 2);
    result->max_x = max_x;
    result->max_y = max_y;
    return result;
}

void show_main_win(MainWin *main_win)
{
    cow_say(main_win->cow_win->win, main_win->cow_win->words[MAIN_GUIDE], 'o');
    switch (main_win->select_win)
    {
    case COMMAND_WIN:
        show_command_win(main_win->command_win, 1);
        show_table_win(main_win->table_win, 0);
        show_cow_win(main_win->cow_win, 0);
        break;
    case TABLE_WIN:
        show_command_win(main_win->command_win, 0);
        show_table_win(main_win->table_win, 1);
        show_cow_win(main_win->cow_win, 0);
        break;
    case COW_WIN:
        show_command_win(main_win->command_win, 0);
        show_table_win(main_win->table_win, 0);
        show_cow_win(main_win->cow_win, 1);
        break;
    default:
        show_command_win(main_win->command_win, 0);
        show_table_win(main_win->table_win, 0);
        show_cow_win(main_win->cow_win, 0);
        break;
    }
    show_output_win(main_win->output_win);
    refresh();
}

void command_operate(CommandWin *com_win, MainWin *main_win)
{
    int oper_x = 0;
    wclear(oper_bar);
    info_bar_wprint(oper_bar, "Esc", "Quit", &oper_x);
    echo();
    noraw();
    cbreak();
    keypad(com_win->win, true);
    curs_set(1);
    flush_box_win(com_win->win);
    wrefresh(com_win->win);
    mvwprintw(com_win->win, 1, 1, "Input[%d] ", com_win->input_num++);
    int input;
    int command_number = 0; // 输入的编码
    while ((input = wgetch(com_win->win)) != 27)
    {
        flush_box_win(main_win->output_win->win);
        wrefresh(com_win->win);
        if (input != '\n')
        {
            if (isdigit(input))
            {
                command_number = command_number * 10 + input - '0';
            }
            else
            {
                command_number = 0;
            }
        }
        else
        {
            switch(command_number)
            {
            case RECORD_INFO:
                if (main_win->table_win->actual_num == main_win->table_win->stu_num)
                {
                    show_message_box_without_select(getmaxy(stdscr), getmaxx(stdscr), "The student number reached the maximum");
                }
                else
                {
                    student *new_stu = main_win->table_win->stu[main_win->table_win->actual_num++];
                    new_stu->id = show_numeric_input_box(getmaxy(stdscr), getmaxx(stdscr), "Input student id", TYPE_INTEGER);
                    show_input_str_box(getmaxy(stdscr), getmaxx(stdscr), "Input student name", new_stu->name);
                    for (int i = 0; i < sub_num; i++)
                    {
                        char input_sub_buffer[32];
                        sprintf(input_sub_buffer, "Input student subject[%d]", i + 1);
                        new_stu->sub[i] = show_numeric_input_box(getmaxy(stdscr), getmaxx(stdscr), input_sub_buffer, TYPE_INTEGER);
                    }
                }
                show_table_win(main_win->table_win, 0);
                break;
            case CALC_TOTAL_SUB:
                // 计算总分
                int calc_sub_num = show_numeric_input_box(getmaxy(stdscr), getmaxx(stdscr), "Target subject No.(from 0 begin)", TYPE_INTEGER);
                if (calc_sub_num >= sub_num || calc_sub_num < 0)
                {
                    show_info(main_win->output_win, "Error Input!                      ");
                }
                else
                {
                    char buffer[100];
                    int sub_total = count_sum_sub(main_win->table_win->stu, main_win->table_win->stu_num, calc_sub_num);
                    sprintf(buffer, "Total score: %d, averg: %.2lf                                ", sub_total, (double) (sub_total / main_win->table_win->stu_num));
                    show_info(main_win->output_win, buffer);
                }
                break;
            case CALC_TOTAL_STU:
                int stu_num_temp = main_win->table_win->actual_num;
                int *own_total = count_sum_stu(main_win->table_win->stu, stu_num_temp);
                char *_buffer = (char *)malloc(sizeof(char) * 20 * (stu_num_temp + 1));

                for (int i = 0; i < stu_num_temp; i++)
                {
                    int _ptr = i * 20;
                    sprintf(_buffer + i * 20, "%s: %d", main_win->table_win->stu[i]->name, own_total[i]);
                    while (_buffer[_ptr++]);
                    for (int j = _ptr - 1; j < (i + 1) * 20; j++)
                    {
                        _buffer[j] = ' ';
                    }
                }
                int stu_total = 0;
                for (int i = 0 ; i < stu_num_temp; i++)
                {
                    stu_total += own_total[i];
                }
                sprintf(_buffer + stu_num_temp * 20, "averg: %.2lf   ", (double)stu_total / stu_num_temp);
                show_info(main_win->output_win, _buffer);
                free(_buffer);
                free(own_total);
                // hero: offsetx 256, offsety: 80, use DHCamera
                break;
            case SORT_TOTAL_DSD:
                insertion_sort(main_win->table_win->stu, main_win->table_win->actual_num, compare_by_total, 0);
                show_table_win(main_win->table_win, 0);
                show_info(main_win->output_win, "Sort done!                    ");
                break;
            case SORT_TOTAL_ASD:
                insertion_sort(main_win->table_win->stu, main_win->table_win->actual_num, compare_by_total, 1);
                show_table_win(main_win->table_win, 0);
                show_info(main_win->output_win, "Sort done!                    ");
                break;
            case SORT_ID_ASD:
                insertion_sort(main_win->table_win->stu, main_win->table_win->actual_num, compare_by_id, 1);
                show_table_win(main_win->table_win, 0);
                show_info(main_win->output_win, "Sort done!                    ");
                break;
            case SORT_NAME_ASD:
                insertion_sort(main_win->table_win->stu, main_win->table_win->actual_num, compare_by_name, 1);
                show_table_win(main_win->table_win, 0);
                show_info(main_win->output_win, "Sort done!                    ");
                break;
            case SEARCH_ID:
                int id_target = show_numeric_input_box(getmaxy(stdscr), getmaxx(stdscr), "Input ID", TYPE_INTEGER);
                int id_result = search_by_id(main_win->table_win->stu, main_win->table_win->actual_num, id_target);
                if (id_result == -1)
                {
                    show_info(main_win->output_win, "Not Found...");
                    cow_say(main_win->cow_win->win, "No such student!", 'x');
                }
                else
                {
                    char stu_res[100];
                    student_to_string(main_win->table_win->stu[id_result], stu_res);
                    show_info(main_win->output_win, stu_res);
                }
                break;
            case SEARCH_NAME:
                char name_target[13];
                show_input_str_box(main_win->max_y, main_win->max_x, "Input name", name_target);
                int name_result = search_by_name(main_win->table_win->stu, main_win->table_win->stu_num, name_target);
                if (name_result == -1)
                {
                    show_info(main_win->output_win, "Not Found...");
                    cow_say(main_win->cow_win->win, "No such student!", 'x');
                }
                else
                {
                    char stu_res[100];
                    student_to_string(main_win->table_win->stu[name_result], stu_res);
                    show_info(main_win->output_win, stu_res);
                }
                break;
            case STATISTIC_:
                int **list = sort_and_list(main_win->table_win->stu, main_win->table_win->stu_num);
                break;
            case LIST_RECORD:
                show_message_box_without_select(getmaxy(stdscr), getmaxx(stdscr) ,"For the list is always shown above, I did not implement this single overlaped function.");
                break;
            case WRITE_FILE:
                char write_buffer[13];
                show_input_str_box(getmaxy(stdscr), getmaxx(stdscr), "Input file name:( < 12 chars)", write_buffer);
                to_file(main_win->table_win->stu, main_win->table_win->actual_num, write_buffer);
                show_info(main_win->output_win, "Write Done!");
                break;
            case READ_FILE:
                char buffer[13];
                show_info(main_win->output_win, "Reading file...                    ");
                show_input_str_box(getmaxy(stdscr), getmaxx(stdscr), "Input file name:( < 12 chars)", buffer);
                from_file(buffer, main_win);
                show_table_win(main_win->table_win, 0);
                break;
            default:
                show_info(main_win->output_win, "invalid command!                    ");
                break;
            }
            break;
        } 
    }
    wclear(com_win->win);
    curs_set(0);
    noecho();
    keypad(com_win->win, false);
}

// 时间不够了, 这些就放弃好了:(
// void table_operate(TableWin *tab_win)
// {
//     keypad(tab_win->win, true);
//     int input = 0;

//     // moving curses around
//     while (input != 27 && input != '\n')
//     {
//         input = wgetch(tab_win->win);
//         switch (input)
//         {
//         case KEY_UP:
//             if (tab_win->row > 0)
//             {
//                 tab_win->row += -1;
//             }
//             break;
//         case KEY_DOWN:
//             if (tab_win->row < tab_win->max_row - 1)
//             {
//                 tab_win->row += 1;
//             }
//             break;
//         case KEY_LEFT:
//             if (tab_win->col > 0)
//             {
//                 tab_win->col += -1;
//             }
//             break;
//         case KEY_RIGHT:
//             if (tab_win->col < tab_win->max_col - 1)
//             {
//                 tab_win->col += -1;
//             }
//             break;
//         default:
//             break;
//         }
//         wrefresh(tab_win->win);
//     }

//     // enroll data
//     if (input == '\n')
//     {
        
//         table_operate(tab_win);
//         return;
//     }
//     else
//     {
//         return;
//     }
// }

void show_output_win(OutputWin *output_win)
{
    wattr_set(output_win->win, A_NORMAL, cyan_color, NULL);
    box(output_win->win, 0, 0);
    wattr_set(output_win->win, A_NORMAL, -1, NULL);

    wrefresh(output_win->win);
}

bool show_message_box(int max_y, int max_x, char *str)
{
    wclear(oper_bar);
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
            output[(i + 1) * (width + 1) - 1] = '\0';
        }
    }
    else
    {
        strcpy(output, str);
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
    refresh();
    wclear(msg_box);
    keypad(msg_box, false);
    free(output);
    delwin(msg_box);
    wclear(oper_bar);
    return selected;
}

void show_message_box_without_select(int max_y, int max_x, char *str)
{
    wclear(oper_bar);
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
            output[(i + 1) * (width + 1) - 1] = '\0';
        }
    }
    else
    {
        strcpy(output, str);
    }
    int x = 0;
    
    info_bar_wprint(oper_bar, "OK", "Comfirm", &x);
    WINDOW *msg_box = newwin(lines + 4, width + 6, (max_y - lines - 3) / 2, (max_x - 22) / 2);
    bool selected = true;   // the selected option, true = OK, false = cancel
    box(msg_box, 0, 0);

    for (int i = 0; i < lines; i++)
    {
        mvwprintw(msg_box, i + 1, 3, "%s", output + (width + 1) * i);
    }
    
    x = width - 12;
    highlight_buttom(msg_box, lines + 2, &x, "OK");
    refresh();
    wrefresh(msg_box);
    
    keypad(msg_box, true);
    noecho();
    int input = wgetch(msg_box);
    refresh();

    while (input != '\n')
    {
        input = wgetch(msg_box);
    }
    refresh();
    wclear(msg_box);
    keypad(msg_box, false);
    free(output);
    delwin(msg_box);
    wclear(oper_bar);
    return;
}


void show_table_win(TableWin *tab_win, int highlight)
{
    int sub_num = tab_win->sub_num;
    if(highlight)
    {
        wattr_set(tab_win->win, A_NORMAL, blue_color, NULL);
        box(tab_win->win, 0, 0);
        wattr_set(tab_win->win, A_NORMAL, -1, NULL);
    }
    else
    {
        wattr_set(tab_win->win, A_NORMAL, cyan_color, NULL);
        box(tab_win->win, 0, 0);
        wattr_set(tab_win->win, A_NORMAL, cyan_color, NULL);
    }
    // print header
    mvwprintw(tab_win->win, 1, 1, "        ID        Name");
    int x_position = 20;
    for (int i = 0; i < sub_num; i++)
    {
        wprintw(tab_win->win, "%12s", tab_win->subject_name[i]);
    }
    for (int i = 0; i < tab_win->actual_num; i++)
    {
        if (i & 1)
        {
            wattr_set(tab_win->win, A_NORMAL, blue_color, NULL);
        }
        else
        {
            wattr_set(tab_win->win, A_NORMAL, green_color, NULL);
        }
        mvwprintw(tab_win->win, i + 2, 1, "%10d%10s", tab_win->stu[i]->id, tab_win->stu[i]->name);
        for (int j = 0; j < sub_num; j++)
        {
            wprintw(tab_win->win, "%12d", tab_win->stu[i]->sub[j]);
        }
    }
    wattr_set(tab_win->win, A_NORMAL, -1, NULL);
    wrefresh(tab_win->win);
}
void show_cow_win(CowWin *cow_win, int highlight)
{
    if(highlight)
    {
        wattr_set(cow_win->win, A_NORMAL, blue_color, NULL);
        box(cow_win->win, 0, 0);
        wattr_set(cow_win->win, A_NORMAL, -1, NULL);
    }
    else
    {
        wattr_set(cow_win->win, A_NORMAL, cyan_color, NULL);
        box(cow_win->win, 0, 0);
        wattr_set(cow_win->win, A_NORMAL, -1, NULL);
    }
    wrefresh(cow_win->win);
}
void show_command_win(CommandWin *com_win, int highlight)
{
    if(highlight)
    {
        wattr_set(com_win->win, A_NORMAL, blue_color, NULL);
        box(com_win->win, 0, 0);
        wattr_set(com_win->win, A_NORMAL, -1, NULL);
    }
    else
    {        
        wattr_set(com_win->win, A_NORMAL, cyan_color, NULL);
        box(com_win->win, 0, 0);
        wattr_set(com_win->win, A_NORMAL, -1, NULL);
    }
    wrefresh(com_win->win);
}

void main_oper(MainWin *main_win)
{
    curs_set(0);
    show_main_win(main_win);
    int ch = '\n';
    while (true)
    {
        int oper_x = 0;
        info_bar_wprint(oper_bar, "Space", "Switch windows", &oper_x);
        info_bar_wprint(oper_bar, "Enter", "Select", &oper_x);
        info_bar_wprint(oper_bar, "Q/q/Esc/0", "Quit", &oper_x);
        if (ch == 27 || ch == 'q' || ch == 'Q' || ch == '0')
        {
            if (show_message_box(main_win->max_y, main_win->max_x, "Quit?"))
            {
                break;
            }
            clear();
        }
        switch (ch)
        {
        case ' ':
            main_win->select_win++;
            if (main_win->select_win > 2)
            {
                main_win->select_win = 0;
            }
            break;
        case '\n':
            switch (main_win->select_win)
            {
            case COMMAND_WIN:
                command_operate(main_win->command_win, main_win);
                break;
            case COW_WIN:
                cow_operate(main_win->cow_win);
                break;
            case TABLE_WIN:
                // table_operate(main_win->table_win);
                break;
            default:
                break;
            }
            break;
        case 'h':
            show_help_win(main_win->max_y, main_win->max_x);
            break;
        }
        refresh();
        show_main_win(main_win);
        ch = getch();
    }
}

void cow_operate(CowWin *cow_win)
{
    wclear(oper_bar);
    int oper_x = 0;
    info_bar_wprint(oper_bar, "S", "shut up", &oper_x);
    info_bar_wprint(oper_bar, "Space", "listen", &oper_x);
    info_bar_wprint(oper_bar, "Esc", "leave", &oper_x);

    int input;
    while ((input = getch()) != 27)
    {
        switch (input)
        {
        case 's':
        case 'S':
            cow_say(cow_win->win, "OK, I'll keep quiet", 'T');
            break;
        case ' ':
            listen_to_cow(cow_win);
            break;
        default:
            break;
        }
    }
    wrefresh(oper_bar);
}


int show_numeric_input_box(int max_y, int max_x, char *info, FIELDTYPE *type)
{   
    wclear(oper_bar);
    int oper_x = 0;
    info_bar_wprint(oper_bar, "Enter", "Comfirm", &oper_x);
    int length = strlen(info) > 17 ? strlen(info) : 17;
    const int height = 5;
    int result;

    curs_set(1);
    WINDOW *win = newwin(height, length + 5, (max_y - height) / 2, (max_x - length - 5) / 2);
    box(win, 0, 0);
    FIELD *input[2];
    input[0] = new_field(1, length, 0, 0, 0, 0);
    input[1] = new_field(1, 8, 2, 4, 0, 0);
    input[2] = NULL;

    set_field_buffer(input[0], 0, info);
    set_field_buffer(input[1], 0, "");
    
    set_field_opts(input[0], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(input[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);

    set_field_back(input[1], A_UNDERLINE);
    keypad(stdscr, true);
    noecho();
    cbreak();

    FORM *form = new_form(input);
    set_form_win(form, win);
    set_form_sub(form, derwin(win, height - 2, length + 2, 1, 1));
    post_form(form);

    refresh();
    wrefresh(win);
    char buffer[200];

    int _input = getch();

    form_driver(form, REQ_NEXT_FIELD);
    while (true)
    {
        char *str_input = trim_whitespaces(field_buffer(input[1], 0));
        if (!strcmp(str_input, "invalid"))
        {
            form_driver(form, REQ_DEL_LINE);
            set_field_buffer(input[1], 0, "");
            wrefresh(win);
        }
        if (_input == '\n')
        {
            form_driver(form, REQ_NEXT_FIELD);
            form_driver(form, REQ_PREV_FIELD);
            char *str_input = trim_whitespaces(field_buffer(input[1], 0));
            int i = 0;
            int is_num = 1;
            for (i = 0; str_input[i]; i++)
            {
                if (str_input[i] < '0' || str_input[i] > '9')
                {
                    is_num = 0;
                    // break;
                }
            }
            if (is_num && i)
            {
                sscanf(str_input, "%d", &result);
                break;
            }
            else
            {
                set_field_buffer(input[1], 0, "invalid");
            }
        }
        driver(_input, form);
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
    return result;
}

void show_input_str_box(int max_y, int max_x, char *info, char *dest)
{
    wclear(oper_bar);
    int oper_x = 0;
    info_bar_wprint(oper_bar, "Enter", "Comfirm", &oper_x);
    int length = strlen(info) > 17 ? strlen(info) : 17;
    const int height = 5;
    int result;

    curs_set(1);
    WINDOW *win = newwin(height, length + 5, (max_y - height) / 2, (max_x - length - 5) / 2);
    box(win, 0, 0);
    FIELD *input[2];
    input[0] = new_field(1, length, 0, 0, 0, 0);
    input[1] = new_field(1, 12, 2, 4, 0, 0);
    input[2] = NULL;

    set_field_buffer(input[0], 0, info);
    set_field_buffer(input[1], 0, "");
    
    set_field_opts(input[0], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(input[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);

    set_field_back(input[1], A_UNDERLINE);
    keypad(stdscr, true);
    noecho();
    cbreak();

    FORM *form = new_form(input);
    set_form_win(form, win);
    set_form_sub(form, derwin(win, height - 2, length + 2, 1, 1));
    post_form(form);

    refresh();
    wrefresh(win);
    char buffer[200];

    int _input = getch();

    form_driver(form, REQ_NEXT_FIELD);
    while (true)
    {
        if (_input == '\n')
        {
            form_driver(form, REQ_NEXT_FIELD);
            form_driver(form, REQ_PREV_FIELD);
            char *str_input = trim_whitespaces(field_buffer(input[1], 0));
            memcpy(dest, str_input, sizeof(char) * 11);
            dest[11] = 0;
            break;
        }
        driver(_input, form);
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

// 清空带有边框的窗口
void flush_box_win(WINDOW *win)
{
    int width = win->_maxx - 2;
    int height = win->_maxy - 2;
    char *buffer = (char *)malloc(sizeof(char) * (width + 1));
    memset(buffer, ' ', sizeof(char) * width);
    buffer[width] = '\0';
    for (int i = 0; i < height - 2; i++)
    {
        mvwprintw(win, i + 1, 1, "%s", buffer);
    }
    refresh();
    wrefresh(win);
    free(buffer);
}

void show_info(OutputWin *output_win, char *str)
{
    wclear(oper_bar);
    int width = output_win->win->_maxx;
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
            output[(i + 1) * (width + 1) - 1] = '\0';
        }
    }
    else
    {
        strcpy(output, str);
    }

    for (int i = 0; i < lines; i++)
    {
        mvwprintw(output_win->win, i + 1, 3, "%s", output + (width + 1) * i);
    }
}

int read_input_numeric(CommandWin *com_win)
{
    
}

void listen_to_cow(CowWin *cow_win)
{
    flush_box_win(cow_win->win);
    if (cow_win->word_id >= FORTUNE1)
    {
        cow_win->word_id++;
        if (cow_win->word_id == TOTAL)
        {
            cow_win->word_id = FORTUNE1;
        }
    }
    else
    {
        cow_win->word_id = FORTUNE1;
    }
    switch (cow_win->word_id)
    {
    case STUDY:
        cow_say(cow_win->win, cow_win->words[cow_win->word_id], 'x');
        break;
    default:
        cow_say(cow_win->win, cow_win->words[cow_win->word_id], 'o');
        break;
    }
}

