#include <stdio.h>
#include "MonstTeam.h"

bool AddMonster(MonsterTeam *team, Monster m)
{
    if (team->size >= MaxNumMonsters)
        return false;

    team->monsters[team->size] = m;
    team->size += 1;
    return true;
}
// ----------------------------------------------
// 輸出所有怪物
// ----------------------------------------------
void Output(const MonsterTeam *team)
{
    for (int i=0; i<team->size; i+=1)
    {
        Output(team->monsters[i]);
    }
}
// ----------------------------------------------
// 回傳怪物能力總和
// ----------------------------------------------
int Power(Monster m) { return m.att + m.def; }

// ----------------------------------------------
// FindWeakestMonster()
//
// 回傳最弱（能力和最低）怪物的索引值。
// 最有多於一隻，回傳最小的索引值。
// 若無怪物，回傳 -1。
// ----------------------------------------------

// 待完成
int FindWeakestMonster(const MonsterTeam *team)
{
    int weakest = 0, wval=Power(team->monsters[0]);

    if(!team->size) return -1;
    for(int i=1; i < team->size; i+=1)
    {

        int val=Power(team->monsters[i]);
        if (val < wval)
        {
            weakest=i;
            wval=val;
        }

    }

    return weakest;
}


// ----------------------------------------------
// Remove()
//
// 刪除掉指定索引值的怪物。
// 若索引值錯誤，回傳 false；否則，回傳 true。
// ----------------------------------------------

// 待完成
bool Remove(MonsterTeam *team, int ind)
{
    if(ind>=team->size || ind<0)
    {
        return false;
    }


    for (int i=ind; i<team->size-1; i+=1)
    {
        team->monsters[i] = team->monsters[i+1];

    }

    team->size -=1;

    return true;
}
