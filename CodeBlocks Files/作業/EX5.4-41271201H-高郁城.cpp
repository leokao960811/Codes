#include <stdio.h>
#include <stdlib.h>

void showHealth(int *monster, int times)
{
    for(int i=0; i<times; i+=1)
    {
        printf("Monster %d: ",i+1);
        if(monster[i]==0)
        {
            printf("--DEAD--");
        }
        else
        {
            for (int k=0; k<monster[i]; k+=1)
            {
                    printf("*");
            }
        }
        printf("\n");
    }
    printf("\n");
}


int main()
{
    // ---------- Initialization ---------
    constexpr int NumMonsters = 5;
    //int HP=10;
    int monster[NumMonsters] = {};
    for (int i=0; i<NumMonsters; i+=1)
    {
        monster[i] = 10;
    }

    // ---------- Game starts ---------
    int die = 0;

    while(die < NumMonsters)
    {
        // ---------- Show game state ---------
        system("cls");
        printf("***Monster Hunting Game***\n\n");

        showHealth(monster, NumMonsters);

        int choice = 0;
        printf("It's your turn :(1)Agidyne(Single) <7P> (2)Maragi(Group) <2P>\n");
        scanf("%d", &choice);

        if(choice == 1)
        {
            printf("Which one to attack? (1~5)\n");
            scanf("%d", &choice);
            monster[choice-1] = monster[choice-1]>7?monster[choice-1]-7:0;
            printf("Monster %d was hit by 7 HP.\n",choice);

        }
        else
        {
            for (int i=0; i<NumMonsters; i+=1)
            {
                monster[i] = monster[i]>2?monster[i]-2:0;
            }
            printf("All monsters got hit by 2HP.\n");
        }

        die = 0;
        for(int i=0; i<NumMonsters; i+=1)
        {
            if(monster[i]<=0)
            {
                die+=1;
            }
        }

        system("pause");

    }

    // ---------- Game ends ---------
    printf("\nVictory! EXP: none\n");
    system("pause");

    return 0;
}
