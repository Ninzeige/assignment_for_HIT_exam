#ifndef HIT_STU_H_
#define HIT_STU_H_
#include "subject.h"

typedef struct 
{
    int id;         // 学号
    char* name;     // 姓名
    subject *sub;   // 成绩
    int *is_valid;  // 学生的信息是否无误, 若有误则不参与计算
}student;

int is_stu_valid(student *stu);
int sort_student(student *stu, int num, int OPERATOR);

#endif /* HIT_STU_H_ */