#include <stdio.h>
#include <stdlib.h>
#include "Monster.h"

Monster GenerateMonster(int i)
{
    Monster newM; //建立新的怪
    newM.id=i;
    newM.att=rand()%10+1;
    newM.def=rand()%10+1;

    return newM;
}


void Output(Monster m)
{
    printf("Monster %d : att: %d def: %d\n",
            m.id, m.att, m.def);
}
