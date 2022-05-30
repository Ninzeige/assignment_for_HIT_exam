#ifndef HIT_STU_H_
#define HIT_STU_H_
#include "subject.h"

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
int sort_student(student *stu, int num, int OPERATOR);

int str_to_int(char *input, int length, int *result);

#endif /* HIT_STU_H_ */