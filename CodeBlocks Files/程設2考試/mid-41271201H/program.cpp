#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "program.h"

bool AddCourse(Program *prog, const char course[])
{
    if((prog->sz)>=10){return false;}
    else
    {
        strcpy(prog->courses[(prog->sz)], course);
        prog->sz+=1;

        return true;
    }
}

void Print(const Program *prog)
{
    printf("%s -- %d courses:\n", prog->name, prog->sz);
    for(int i=0; i<prog->sz; i+=1)
    {
        printf("%s\n",prog->courses[i]);
    }
    printf("\n");

}

Program* AddProgram(ProgramList *lst, const char prog_name[])
{
    if((lst->sz)>=10) {return nullptr;}

    Program p;
    strcpy(p.name, prog_name);
    lst->programs[lst->sz]=p;
    lst->sz+=1;

    return &lst->programs[lst->sz - 1];
}

