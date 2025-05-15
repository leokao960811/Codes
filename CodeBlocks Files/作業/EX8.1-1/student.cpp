#include <stdio.h>
#include "student.h"

bool Input(Student *s)
{
    scanf("%d", &s->id);
    if((s->id)<=0)
    {
        return false;
    }
    else
    {
        scanf("%s%lf", &s->name, &s->score);
        return true;
    }
}

void Output(Student s)
{
    printf("ID: %d "
           "Name: %s "
           "Score: %.2lf "
           , s.id, s.name, s.score);
    printf("\n");

}
