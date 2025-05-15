#ifndef MONSTTEAM_H
#define MONSTTEAM_H
#include "Monster.h"

constexpr int MaxNumMonsters = 5;

struct MonsterTeam
{
    Monster monsters[MaxNumMonsters];
    int size = 0;
};

bool AddMonster(MonsterTeam *team, Monster m);
void Output(const MonsterTeam *team);
int Power(Monster m);
int FindWeakestMonster(const MonsterTeam *team);
bool Remove(MonsterTeam *team, int ind);

#endif
