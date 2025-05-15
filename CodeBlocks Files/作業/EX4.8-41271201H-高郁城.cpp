#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void showHealth(int *monster, int times, int *playerHP)
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
        printf(" <%d>\n",monster[i]);
    }
    printf("\n");

    printf("Player HP: ");
    for(int i=0; i<(*playerHP); i+=1)
    {
        printf("*");
    }
    printf(" <%d>\n", *playerHP);
}

void monsterAction(int *monster, int num, int *HP)
{
    for(int i=0; i<num; i+=1)
    {
        int healFlag=0;
        if (monster[i]<=0) continue;
        else
        {
            for(int k=0; k<num; k+=1)
            {
                if(monster[k]<=3 && monster[k]>0 && healFlag==0)
                {
                    printf("Monster %d heals Monster %d for 1HP.\n", i+1, k+1);
                    monster[k]+=1;
                    healFlag=1;
                }
            }
        }

        if(healFlag==0)
        {
            int damage=rand()%10;
            if(damage==0)
            {
                printf("CRIT! Monster %d hits you for 3HP.\n", i+1);
                (*HP)-=3;
            }
            else
            {
                printf("Monster %d hits you for 1HP.\n", i+1);
                (*HP)-=1;
            }
        }
    }
}

int main()
{
    // ---------- Initialization ---------
    constexpr int NumMonsters = 5;
    int playerHP=30;
    int monster[NumMonsters] = {};

    int singleatk=7, allatk=2;

    for (int i=0; i<NumMonsters; i+=1)
    {
        monster[i] = 10;
    }

    srand( time(NULL) );
    // ---------- Game starts ---------
    int die = 0;

    while(die < NumMonsters && playerHP > 0)
    {
        // ---------- Show game state ---------
        system("cls");
        printf("***Monster Hunting Game***\n\n");

        showHealth(monster, NumMonsters, &playerHP);

        int choice = 0;
        printf("It's your turn: (1)Single Strike <%dP> (2)Group Sweep <%dP> ...> ", singleatk, allatk);
        scanf("%d", &choice);

        if(choice == 1)
        {
            printf("Which one to attack? (1~5)...> ");
            scanf("%d", &choice);
            if(choice > NumMonsters || choice <= 0 || monster[choice-1]<=0)
            {
                while(choice > NumMonsters || choice <= 0 || monster[choice-1]<=0)
                {
                    printf("\nMonster not chosen!\n");
                    printf("Insert your target again...> ");
                    scanf("%d",&choice);
                }
            }

            int chance=rand()%5;
            if (chance==0)
            {
                printf("You missed the attack on Monster %d.\n",choice);
            }
            else
            {
                monster[choice-1] = monster[choice-1] > singleatk ? monster[choice-1]-singleatk : 0;
                printf("Monster %d was hit by %d HP.\n\n", choice, singleatk);
            }
        }
        else
        {
            for (int i=0; i<NumMonsters; i+=1)
            {
                monster[i] = monster[i]>allatk?monster[i]-allatk:0;
            }
            printf("All monsters got hit by %dHP.\n\n", allatk);
        }

        monsterAction(monster, NumMonsters, &playerHP);

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
    if(playerHP<=0)
    {
        printf("\nYou're DEAD. Game Over.\n");
    }
    else
    {
        system("cls");
        printf("***Monster Hunting Game***\n\n");
        showHealth(monster, NumMonsters, &playerHP);
        printf("\nVictory! EXP: none\n");
    }

    system("pause");

    return 0;
}
