#ifndef PROGRAM_H
#define PROGRAM_H

constexpr int ProgMaxCourses = 10;
constexpr int MaxPrograms = 10;

struct Program
{
    char name[30]={};
    char courses[ProgMaxCourses][30]={};
    int sz=0;
};

struct ProgramList
{
    Program programs[MaxPrograms];
    int sz=0;
};

bool AddCourse(Program *prog, const char course[]);
void Print(const Program *prog);

Program* AddProgram(ProgramList *lst, const char prog_name[]);

#endif
