---
layout: post
title: 算法：教授分组
author: qoyooo
tags: [算法, C++, 分组]
date: 2022-11-10 22:28 +0800
---
 * 周教授讲授计算机算法课程，班上一共有72个学生。每一周，周教授都安排这些学生见一次面。
 * 有些周，周教授将72名学生分为每组8人，另外一些周，周教授将72名学生分为每组9人。
 * 只要两个学生被分在同一组，就算见一次面。周教授分组的原则是，在整个授课过程中，任意两
 * 个学生必须见一次面，且仅见一次面。问，周教授的课程需要安排多少周？周教授需要如何将这
 * 些学生分组？
 * 

``` c++
/* 
 * 周教授讲授计算机算法课程，班上一共有72个学生。每一周，周教授都安排这些学生见一次面。
 * 有些周，周教授将72名学生分为每组8人，另外一些周，周教授将72名学生分为每组9人。
 * 只要两个学生被分在同一组，就算见一次面。周教授分组的原则是，在整个授课过程中，任意两
 * 个学生必须见一次面，且仅见一次面。问，周教授的课程需要安排多少周？周教授需要如何将这
 * 些学生分组？
 * 
 */

#include <stdio.h>
#include <assert.h>
#include <time.h>

const int STUDENT_NUM     = 72;
const int INIT_GROUP_NUM  = 8;
const int INIT_GROUP_SIZE = 9;
const int GROUP_NUM       = 9;
const int GROUP_SIZE      = 8;   

// 见面情况
int meeted[STUDENT_NUM][STUDENT_NUM] = {0};
void init_meeted()
{
    for (int i = 0; i < STUDENT_NUM; i++) {
        meeted[i][i] = 1;
    }
}
void print_meeted()
{
    printf("Meeted:\n");
    for (int i = 0; i < STUDENT_NUM; i++) {
        for (int k = 0; k < STUDENT_NUM; k++)
            printf("%2d", meeted[i][k]);
        printf("\n");
    }
}
bool solved()
{
    for (int i = 0; i < STUDENT_NUM; i++) {
        for (int k = 0; k < STUDENT_NUM; k++)
            if (!meeted[i][k]) return false;
    }
    return true;
}

/*  原始分组方案
    Group[0]:   0   1   2   3   4   5   6   7   8
    Group[1]:   9  10  11  12  13  14  15  16  17
    Group[2]:  18  19  20  21  22  23  24  25  26
    Group[3]:  27  28  29  30  31  32  33  34  35
    Group[4]:  36  37  38  39  40  41  42  43  44
    Group[5]:  45  46  47  48  49  50  51  52  53
    Group[6]:  54  55  56  57  58  59  60  61  62
    Group[7]:  63  64  65  66  67  68  69  70  71
*/
int origin[INIT_GROUP_NUM][INIT_GROUP_SIZE] = {0};
void generate_origin()
{
    int num = 0;
    for (int i = 0; i < INIT_GROUP_NUM; i++)
        for (int k = 0; k < INIT_GROUP_SIZE; k++)
            origin[i][k] = num++;
}
void refresh_origin()
{
    for (int i = 0; i < INIT_GROUP_NUM; i++)
        for (int k = 0; k < INIT_GROUP_SIZE - 1; k++)
            for (int m = k + 1; m < INIT_GROUP_SIZE; m++) {
                meeted[origin[i][k]][origin[i][m]] = 1;
                meeted[origin[i][m]][origin[i][k]] = 1;
            }
}
void print_origin()
{
    printf("Origin:\n");
    for (int i = 0; i < INIT_GROUP_NUM; i++) {
        printf("Group[%d]:", i);
        for (int k = 0; k < INIT_GROUP_SIZE; k++)
            printf("%4d", origin[i][k]);
        printf("\n");
    }
}

// 解决方案
int solution[30][GROUP_NUM][GROUP_SIZE] = {0};

void print_group(int week, int id)
{
    printf("Group[%d]:", id);
    for (int i = 0; i < GROUP_SIZE; i++)
        printf("%4d", solution[week][id][i]);
    printf("\n");
}
void print_week(int week)
{
    printf("Week %d\n", week + 1);
    for (int i = 0; i < GROUP_NUM; i++)
        print_group(week, i);
}

void next_week(int week);

void divide_group(const int week, const int group, const int member, int *inteam)
{
    // 如果本组已满
    if (member >= GROUP_SIZE) {
        divide_group(week, group + 1, 0, inteam);
        return;
    }
    // 如果全部分组完成
    if (group >= GROUP_NUM) {
        print_week(week);
        next_week(week + 1);
        return;
    }
    // 如果找到解
    if (solved()|| week == 9) {
        printf("FOUND!!!\n");
        return;
    }
    for (int i = 0; i < INIT_GROUP_SIZE; i++) {
        // 从origin的第member组中取第i位成员
        int stud1 = origin[member][i];
        // 如要 stud1 已经分组，则继续找下一位成员
        if (inteam[stud1]==1) continue;
        // 判断 stud1 是否与当周的第group组其他成员是否遇到过
        bool meet = false;
        for (int k = 0; k < member; k++) {
            int stud2 = solution[week][group][k];
            if (meeted[stud1][stud2]) meet = true;
        }
        if (!meet) {
            // 
            inteam[stud1] = 1;
            for (int k = 0; k < member; k++) {
                int stud2 = solution[week][group][k];
                meeted[stud1][stud2] = 1;
                meeted[stud2][stud1] = 1;
            }
            solution[week][group][member] = stud1;
            // 尝试本组的下一位成员
            divide_group(week, group, member + 1, inteam);
            // 回溯时，还原现场
            inteam[stud1] = 0;
            for (int k = 0; k < member; k++) {
                int stud2 = solution[week][group][k];
                meeted[stud1][stud2] = 0;
                meeted[stud2][stud1] = 0;
            }
            solution[week][group][member] = 0;
        }
    }
}

void next_week(int week)
{
    // 记录本周学员是否已经分组  in_team[i] = 1 表示学员i已经分组
    int in_team[STUDENT_NUM] = {0};
    // printf("Next Week %d\n", week);
    divide_group(week, 0, 0 , in_team);
}

int main()
{

    init_meeted();

    // 生成原始分组
    generate_origin();
    refresh_origin();
    print_origin();

    // 尝试下一周分组
    next_week(0);

}
```