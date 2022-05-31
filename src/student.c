#include "student.h"
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 12


void try_converse(student *stu)
{
    // read id
    str_to_int(stu->_input[0], MAX_LENGTH, &stu->id);
    if (!stu->_is_valid) { return; }
    strcpy(stu->name, stu->_input[1]);


}

/**
 * @brief try parse str into int
 * 
 * @param input input string
 * @param length the length of the str
 * @param result the result int
 * @return int is success
 */
int str_to_int(char *input, int length, int *result)
{
    *result = 0;
    for (int i = 0; i < length; i++)
    {
        if (input[i])
        {
            if (input[i] >= '0' && input[i] <= '9')
            {
                *result = *result * 10 + input[i] - '0';
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 1;
        }
    }
    return 1;
}

student *new_student(int sub_num)
{
    student *res = (student *)malloc(sizeof(student));
    res->id = 0;
    res->name = (char *)malloc(sizeof(char) * MAX_LENGTH);
    res->sub = (int *)malloc(sizeof(int) * sub_num);
    res->_sub_num = sub_num;
    res->_input = (char **)malloc(sizeof(char *) * (2 + sub_num));
    for (int i = 0; i < sub_num + 2; i++)
    {
        res->_input[i] = (char *)malloc(sizeof(char) * MAX_LENGTH);
    }
    res->_is_valid = 0;

    return res;
}

void delete_student(student *stu)
{
    free(stu->sub);
    for (int i = 0; i < stu->_sub_num + 2; i++)
    {
        free(stu->_input);
    }
    free(stu);
    return;
}