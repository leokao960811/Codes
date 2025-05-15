#include <stdio.h>
#include <stdlib.h>
#include "Monster.h"
#include "MonstTeam.h"

int main()
{
    srand( 3 );
    MonsterTeam monster_team;

    // 輸入有幾隻怪物
    int n = 0;
    scanf("%d", &n);

    // 怪物數不可超過上限
    n = (n<=MaxNumMonsters ? n : MaxNumMonsters);
    for (int i=1; i<=n; i+=1)
    {
        // 新增一隻怪物
        AddMonster(&monster_team, GenerateMonster(i));
    }

    // 輸出所有怪物
    Output(&monster_team);
    putchar('\n');

    // 消滅最弱怪物
    Remove(&monster_team,
           FindWeakestMonster(&monster_team));

    // 輸出所有怪物
    Output(&monster_team);
}
