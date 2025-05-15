#include <stdio.h>
#include <stdlib.h>
#include "Monster.h"
#include "MonstTeam.h"

int main()
{
    srand( 3 );
    MonsterTeam monster_team;

    // ��J���X���Ǫ�
    int n = 0;
    scanf("%d", &n);

    // �Ǫ��Ƥ��i�W�L�W��
    n = (n<=MaxNumMonsters ? n : MaxNumMonsters);
    for (int i=1; i<=n; i+=1)
    {
        // �s�W�@���Ǫ�
        AddMonster(&monster_team, GenerateMonster(i));
    }

    // ��X�Ҧ��Ǫ�
    Output(&monster_team);
    putchar('\n');

    // �����̮z�Ǫ�
    Remove(&monster_team,
           FindWeakestMonster(&monster_team));

    // ��X�Ҧ��Ǫ�
    Output(&monster_team);
}
