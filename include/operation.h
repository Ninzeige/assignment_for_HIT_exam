#ifndef HIT_OPT_H_
#define HIT_OPT_H_
#include "wins.h"

/* ----- 排序操作 ----- */
// 按照总成绩升序
#define ORDERD_BY_TOTAL_ASD 0
// 按照总成绩降序
#define ORDERD_BY_TOTAL_DSD 1
// 按照学号升序
#define ORDERD_BY_ID_ASD 2
// 按照姓名升序
#define ORDERED_BY_NAME_ASD 3

/* ----- 菜单操作 ----- */
// 录入信息(操作1)
#define RECORD_INFO 1
// 计算每门课程总分/平均分(操作2)
#define CALC_TOTAL_SUB 2
// 计算学生总/平均分
#define CALC_TOTAL_STU 3
// 按照从高到低, 总分
#define SORT_TOTAL_DSD 4
// 按照从低到高, 总分
#define SORT_TOTAL_ASD 5
// 按照学号从小到大
#define SORT_ID_ASD 6
// 按照姓名的字典顺序排成绩表
#define SORT_NAME_ASD 7
// 按照学号查询学生排名及考试成绩
#define SEARCH_ID 8
// 按照姓名查询学生姓名及考试成绩
#define SEARCH_NAME 9
// 统计成绩
#define STATISTIC_ 10
// 列出记录
#define LIST_RECORD 11
// 写到文件中
#define WRITE_FILE 12
// 读取文件
#define READ_FILE 13

void operate(int oper_code, TableWin *table);
void to_file(student **stu, int length, char *path);
void from_file(char *path, MainWin *main_win);

#endif /* HIT_OPT_H_ */