#ifndef HIT_STU_H_
#define HIT_STU_H_
#include "subject.h"
// enum OPERATOR{GRADE_DOWN,GDADE_UP,ID_UP,NAME_UP};
#define GRADE_DOWN 0
#define GRADE_UP 1
#define ID_UP 2
#define NAME_UP 3

extern int stu_num;
extern int sub_num;

typedef struct
{
    int id;             // 学号
    char* name;         // 姓名
    int *sub;       // 成绩
    char **_input;       // input info
    int _sub_num;        // number of sub
    int _is_valid;      // 学生的信息是否无误, 若有误则不参与计算
}student;

student *new_student(int sub_num);
void delete_student(student *stu);
void try_converse(student *stu);
int is_stu_valid(student *stu);
int str_to_int(char *input, int length, int *result);


void insertion_sort(student **stu, int num, int (*comperator)(student *lhs, student *rhs), int is_asd);
int compare_by_name(student *lhs, student *rhs);
int compare_by_total(student *lhs, student *rhs);
int compare_by_id(student *lhs, student *rhs);
int compare_by_sub(student *lhs, student *rhs, int sub);

void student_to_string(student *stu, char *dst);
int sort_student(student **stu, int num, int OPERATOR);
int count_sum_sub(student **stu, int num, int subname);
int* count_sum_stu(student **stu,int num);
int search_by_id(student** stu,int num,int id);
int search_by_name(student** stu,int num,char* name);
int** sort_and_list(student** stu,int num);
#endif /* HIT_STU_H_ */