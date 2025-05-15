#ifndef MONSTER_H
#define MONSTER_H

struct Monster
{
    int id = 0;
    int att = 0,
        def = 0;
};

Monster GenerateMonster(int i);
void Output(Monster m);
#endif
