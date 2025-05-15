#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Load.h"
#include "Results.h"
#include "State.h"

int main()
{
    int rounds;
    int b, l;
    int gun[8]; //up to 8 rounds
    int itemp1[8];
    int itemp2[8];

    int input = 0;
    int iteminput = 0;

    int item;
    int itempool = 0;
    char counter;
    int maxHP;
    int p1, p2;

    int shell = 0; //shell counter
    bool sawflag = false; //sawed-off check
    int cuffflag = 0; //handcuff check
    bool invertflag = false; //invert check
    bool adreflag = false; //check for adrenaline used


    srand( time(NULL) );

    for(int i=0;i<8;i+=1)
    {
        itemp1[i]=0;
        itemp2[i]=0;
    }

    printf("Buckshot Roulette Recreation\n");
    printf("Original game by Mike Klubnika\n\n");

    //Initialize HP, item per player
    printf("Input players' starting/max HP...> ");
    scanf("%d", &maxHP);
    if(maxHP<=0)
    {
        while(maxHP<=0)
        {
            printf("HP must be greater than 0.\n");
            printf("Input players' starting/max HP...> ");
            scanf("%d", &maxHP);
        }

    }

    p1=maxHP;
    p2=maxHP;

    printf("Input players' items per turn...> ");
    scanf("%d", &item);
    if(item<0)
    {
        while(item<0)
        {
            printf("Items per turn must be equal or greater than 0.\n");
            printf("Input players' items per turn...> ");
            scanf("%d", &item);
        }

    }

    printf("Choose your item pool(1: 5 items 2: 9 items)...> ");
    scanf("%d", &itempool);
    if(itempool<=0 || itempool>=3)
    {
        while(itempool<=0)
        {
            printf("Input not recognized.\n");
            printf("Choose your item pool(1: 5 items 2: 9 items)...> ");
            scanf("%d", &itempool);
        }
    }

    if(itempool==1)
    {
        itempool=5;
    }
    else if(itempool==2)
    {
        itempool=9;
    }

    printf("Turn on auto shell counter?(y/n)...> ");
    scanf(" %c", &counter);
    if((counter != 'Y' && counter != 'y') && (counter != 'N' && counter != 'n'))
    {
        while((counter != 'Y' && counter != 'y') && (counter != 'N' && counter != 'n'))
        {
            printf("Input not recognized.\n");
            printf("Turn on auto shell counter?(y/n)...> ");
            scanf(" %c", &counter);
        }
    }

    int turn = rand() % 2;

    load(gun, &b, &l, &rounds); //call load function

    itemload(itemp1, itemp2, &item, &itempool);

    //printf("\n");
    system("cls");
    //printf(" \e[1;1H\e[2J") also clears screen
    itemlist(&itempool);

    while (p1 > 0 && p2 > 0)
    {
        printstate(&turn, &p1, &p2, &counter, &shell, &itempool, &l, &b, &sawflag, &invertflag);

        if (turn==0) //P1 turn
        {
            if (cuffflag==1)
            {
                printf("P%d is handcuffed.\n\n", turn+1);
                turn=1;
                cuffflag=-1;
            }
            else
            {
                TableState(itemp1, itemp2);
                scanf("%d", &input);

                switch(input)
                {
                case 0:
                    system("cls");

                    selfshotresults(&p1, gun, &shell, &b, &l, &turn, &cuffflag, &sawflag, &invertflag);
                    break;

                case 1:
                    system("cls");
                    oppshotresults(&p1, &p2, gun, &shell, &b, &l, &turn, &cuffflag, &sawflag, &invertflag);
                    break;

                case 2:
                    printf("\nChoose an itemslot to use (1~8), 0 to exit...> ");
                    scanf("%d", &iteminput);

                    if(iteminput<=0)
                    {
                        system("cls");
                        break;
                    }
                    else
                    {
                        system("cls");
                        itemuse(&turn, itemp1, itemp2, &iteminput, &p1, &maxHP, gun, &rounds, &b, &l, &shell, &cuffflag, &sawflag, &invertflag, &adreflag);
                    }
                    break;

                case 3:
                    system("cls");
                    itemlist(&itempool);
                    break;
                }
            }
        }
        else //P2 turn
        {
            if (cuffflag==2)
            {
                printf("P%d is handcuffed.\n\n", turn+1);
                turn=0;
                cuffflag=-1;
            }
            else
            {
                TableState(itemp2, itemp1);
                scanf("%d", &input);

                switch(input)
                {
                case 0:
                    system("cls");
                    selfshotresults(&p2, gun, &shell, &b, &l, &turn, &cuffflag, &sawflag, &invertflag);
                    break;

                case 1:
                    system("cls");
                    oppshotresults(&p2, &p1, gun, &shell, &b, &l, &turn, &cuffflag, &sawflag, &invertflag);
                    break;

                case 2:
                    printf("\nChoose an itemslot to use (1~8), 0 to exit...> ");
                    scanf("%d", &iteminput);

                    if(iteminput<=0)
                    {
                        system("cls");
                        break;
                    }
                    else
                    {
                        system("cls");
                        itemuse(&turn, itemp2, itemp1, &iteminput, &p2, &maxHP, gun, &rounds, &b, &l, &shell, &cuffflag, &sawflag, &invertflag, &adreflag);
                    }
                    break;

                case 3:
                    system("cls");
                    itemlist(&itempool);
                    break;
                }
            }
        }

        if(shell==rounds)
        {
            if(p1>0 && p2>0)
            {
                printf("Gun reloading...\n");
                for (int i = 0; i < shell; i++)
                {

                    gun[i] = '\0';
                }

                load(gun, &b, &l, &rounds);
                shell=0;

                printf("Adding items...\n\n");
                itemload(itemp1, itemp2, &item, &itempool);

                //if(cuffflag>0)
                //{
                    //printf("Removing Handcuffs...\n\n");
                    //cuffflag=0;
                //}
            }
        }
    }

    printf("P1: %d HP, P2: %d HP\n", p1, p2);
    if(p1>0)
    {
        printf("P1 wins.");
    }
    else if (p2>0)
    {
        printf("P2 wins.");
    }

    printf("\n\nPress Enter to close the program.\n");
    while(getchar() != '\n'); // get rid of all remaining inputs
    getchar(); // wait for one key

    return 0;
}

