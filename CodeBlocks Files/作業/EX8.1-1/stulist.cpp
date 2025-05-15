#include <stdio.h>
#include "stulist.h"

bool AddStudent(List *list, Student s)
{
    if((list->size)>=10)
    {
        return false;
    }
    else
    {
        list->stu[list->size]=s;
        list->size+=1;
        return true;
    }
}

void Output(const List *list)
{
    for (int i=0; i< list->size; i+=1)
    {
        Output(list->stu[i]);
    }
}
