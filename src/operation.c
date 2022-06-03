#include "operation.h"
#include <stdlib.h>
#include "wins.h"

void operate(int oper_code, TableWin *table);
void to_file(student **stu, int length, char *path)
{
    FILE *f = fopen(path, "w");
    if (f == NULL)
    {
        int y, x;
        getmaxyx(stdscr, y, x);
        show_message_box_without_select(y, x, "Write file failed!");
        return;
    }
    int stu_num = length;
    int sub_num = stu[0]->_sub_num;

    fprintf(f, "%d %d\n", stu_num, sub_num);
    for (int i = 0; i < stu_num; i++)
    {
        fprintf(f, "%d %s", stu[i]->id, stu[i]->name);
        for (int j = 0; j < sub_num; j++)
        {
            fprintf(f, " %d", stu[i]->sub[j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
    return;
}
void from_file(char *path, MainWin *main_win)
{
    FILE *f = fopen(path, "r");
    if (f == NULL)
    {
        show_message_box_without_select(main_win->max_y, main_win->max_x, "Read file failed!");
        return;
    }
    int _stu_num, _sub_num;
    int ret = 0;
    ret = fscanf(f, "%d %d", &_stu_num, &_sub_num);
    student **stu = (student **)malloc(sizeof(student *) * _stu_num);
    for (int i = 0; i < _stu_num; i++)
    {
        stu[i] = new_student(_sub_num);
        ret = fscanf(f, "%d %s", &stu[i]->id, stu[i]->name);
        for (int j = 0; j < _sub_num; j++)
        {
            if (ret == EOF)
            {
                for (int k = 0; k < _stu_num; k++)
                {
                    delete_student(stu[k]);
                }
                return;
            }
            ret = fscanf(f, "%d", &stu[i]->sub[j]);
        }
    }
    fclose(f);
    free(main_win->table_win->stu);
    show_info(main_win->output_win, "Read file done.");
    main_win->table_win->stu_num = _stu_num;
    main_win->table_win->actual_num = _stu_num;
    main_win->table_win->sub_num = _sub_num;
    main_win->table_win->stu = stu;
    return;
}

student* read_from_input(CommandWin *com_win, OutputWin *output_win)
{
    flush_box_win(com_win->win);
    flush_box_win(output_win->win);

    show_info(output_win ,"Please Input Studnet ID:");
}

