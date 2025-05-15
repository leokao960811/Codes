#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"


bool AddCourse(Student *stu, const char course[])
{
    if((stu->sz)>=30){return false;}
    else
    {
        strcpy(stu->courses[stu->sz], course);
        stu->sz+=1;

        return true;
    }
}

Student* AddStudent(University *univ, const char stu_id[])
{
    if((univ->sz)>=100) {return nullptr;}

    Student s;
    strcpy(s.id, stu_id);
    univ->stu[univ->sz]=s;
    univ->sz+=1;

    return univ->stu;

}

Student* FindStudent(University *univ, const char stu_id[])
{
    for(int i=0; i<(univ->sz); i+=1)
    {
        if(strcmp(stu_id, univ->stu[i].id)==0)
           {
                return &univ->stu[i];
           }
    }
    return nullptr;
}

