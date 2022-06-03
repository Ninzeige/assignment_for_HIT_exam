#include "student.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_LENGTH 12

int stu_num = 0;
int sub_num = 0;

void try_converse(student *stu)
{
    // read id
    if (!str_to_int(stu->_input[0], MAX_LENGTH, &stu->id))
    {
        stu->_is_valid = 0;
    }
    for (int i = 0; i < stu->_sub_num; i++)
    {
        if (!str_to_int(stu->_input[i + 2], MAX_LENGTH, &stu->sub[i]))
        {
            stu->_is_valid = 0;
        }
    }
    if (!stu->_is_valid)
    {
        return;
    }
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

int compare_by_name(student *lhs, student *rhs)
{
    return strcmp(lhs->name, rhs->name);
}

int compare_by_total(student *lhs, student *rhs)
{
    int l_total = 0, r_total = 0;
    for (int i = 0; i < lhs->_sub_num; i++)
    {
        l_total += lhs->sub[i];
        r_total += rhs->sub[i];
    }
    if (l_total > r_total) { return 1; }
    else if (l_total == r_total) { return 0; }
    else { return -1; }
}
int compare_by_sub(student *lhs, student *rhs, int sub)
{
    if (lhs->sub[sub] > rhs->sub[sub]) { return 1; }
    else if (lhs->sub[sub] == rhs->sub[sub]) { return 0; }
    else { return -1; }
}

int compare_by_id(student *lhs, student *rhs)
{
    if (lhs->id > rhs->id) { return 1; }
    else if (lhs->id == rhs->id) { return 0; }
    else { return -1; }
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

int is_stu_valid(student *stu)
{
    int valid = 1;
    if (stu->id < 0)
    {
        valid = 0;
    }
    if (stu->name == NULL)
    {
        valid = 0;
    }
    for (int i = 0; i < stu->_sub_num; i++)
    {
        if (stu->sub[i] < 0)
        {
            valid = 0;
        }
    }
    return valid;
}

int count_sum_sub(student **stu, int num, int subname)
{
    int sum = 0;
    for (int i = 0; i < num; i++)
    {
        sum += (stu[i])->sub[subname];
    }
    return sum;
}

int *count_sum_stu(student **stu, int num)
{
    int sum = 0, *sum_list;
    sum_list = (int *)malloc(sizeof(int) * num);
    for (int i = 0; i < num; i++)
    {
        sum = 0;
        for (int j = 0; j < stu[i]->_sub_num; j++)
        {
            sum += (stu[i])->sub[j];
        }
        sum_list[i] = sum;
    }
    return sum_list;
}

/**
 * @brief 
 * 
 * @param comperator 1 = greater, 0 = equal, -1 = less
 */
void insertion_sort(student **stu, int num, int (*comperator)(student *lhs, student *rhs), int is_asd)
{
    for (int i = 1; i < num; i++)
    {
        int j = i;
        while (j > 0)
        {
            int compare_result = comperator(stu[j - 1], stu[j]);
            if (!is_asd)
            {
                compare_result = -compare_result;
            }
            if (compare_result > 0)
            {
                student *temp = stu[j - 1];
                stu[j - 1] = stu[j];
                stu[j] = temp;
                j--;
            }
            else
            {
                break;
            }
        }
    }
}



void  insertsort_char(student **stu, int num)
{
    for (int i = 1; i < num; i++)
    {
        student *temp = stu[i];
        for (int j = 0; j < i; i++)
        {
            if (strcmp(stu[j]->name, temp->name))
            {
                for (int k = i - 1; k >= j; k--)
                {
                    memcpy(stu[k + 1], stu[k], sizeof(student));
                }
                memcpy(stu[j], temp, sizeof(student));
                break;
            }
        }
    }
}
int search_by_id(student **stu, int num, int id)
{
    insertion_sort(stu, num, compare_by_id, 1);
    int left = 0;
    int right = num - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (stu[mid]->id < id)
        {
            left = mid + 1;
        }
        else if (stu[mid]->id > id)
        {
            right = mid - 1;
        }
        else
        {
            return mid;
        }
    }
    if (left > right)
        return -1;
}

int search_by_name(student **stu, int num, char *name)
{
    insertion_sort(stu, num, compare_by_name, 1);
    int left = 0;
    int right = num - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (strcmp(stu[mid]->name, name) < 0)
        {
            left = mid + 1;
        }
        else if (strcmp(stu[mid]->name, name) > 0)
        {
            right = mid - 1;
        }
        else
        {
            return mid;
        }
    }
    if (left > right)
        return -1;
}

int **sort_and_list(student **stu, int num)
{
    int a = stu[0]->_sub_num, sum;
    int *great, *good, *medium, *pass, *fail;
    great = (int *)malloc(sizeof(int) * a);
    good = (int *)malloc(sizeof(int) * a);
    medium = (int *)malloc(sizeof(int) * a);
    pass = (int *)malloc(sizeof(int) * a);
    fail = (int *)malloc(sizeof(int) * a);
    memset(great, 0, sizeof(int) * a);
    memset(good, 0, sizeof(int) * a);
    memset(medium, 0, sizeof(int) * a);
    memset(pass, 0, sizeof(int) * a);
    memset(fail, 0, sizeof(int) * a);
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < num; j++)
        {
            if (stu[j]->sub[i] >= 90)
            {
                great[i] += stu[j]->sub[i];
                break;
            }
            if (stu[j]->sub[i] >= 80)
            {
                good[i] += stu[j]->sub[i];
                break;
            }
            if (stu[j]->sub[i] >= 70)
            {
                medium[i] += stu[j]->sub[i];
                break;
            }
            if (stu[j]->sub[i] >= 60)
            {
                pass[i] += stu[j]->sub[i];
                break;
            }
            else
            {
                fail[i] += stu[j]->sub[i];
                break;
            }
        }
    }
    int **list = (int **)malloc(sizeof(int *) * 5);
    int *dst_list[] = {great, good, medium, pass, fail};
    memcpy(list, dst_list, sizeof(int *) * 5);
    return list;
}

/**
 * @brief print struct student
 * 
 * @param stu student
 * @param dst the str to accept the info, assumed to be 100 byte long
 */
void student_to_string(student *stu, char *dst)
{
    const int max_length = 100;
    sprintf(dst, "ID: %d, Name: %s", stu->id, stu->name);
    int _ptr = 0;
    while (dst[_ptr++] && _ptr < 100);
    for (int i = 0; i < stu->_sub_num; i++)
    {
        sprintf(dst + _ptr - 1, ", subject[%d]: %d", i + 1, stu->sub[i]);
        while (dst[_ptr++] && _ptr < 100);
    }
    for (int i = 0; i < 20; i++)
    {
        if (_ptr < max_length)
        {
            dst[_ptr++ - 1] = ' ';
        }
    }
    dst[_ptr - 1] = 0;
    return;
}