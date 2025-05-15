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
// ��X�Ҧ��Ǫ�
// ----------------------------------------------
void Output(const MonsterTeam *team)
{
    for (int i=0; i<team->size; i+=1)
    {
        Output(team->monsters[i]);
    }
}
// ----------------------------------------------
// �^�ǩǪ���O�`�M
// ----------------------------------------------
int Power(Monster m) { return m.att + m.def; }

// ----------------------------------------------
// FindWeakestMonster()
//
// �^�ǳ̮z�]��O�M�̧C�^�Ǫ������ޭȡC
// �̦��h��@���A�^�ǳ̤p�����ޭȡC
// �Y�L�Ǫ��A�^�� -1�C
// ----------------------------------------------

// �ݧ���
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
// �R�������w���ޭȪ��Ǫ��C
// �Y���ޭȿ��~�A�^�� false�F�_�h�A�^�� true�C
// ----------------------------------------------

// �ݧ���
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
