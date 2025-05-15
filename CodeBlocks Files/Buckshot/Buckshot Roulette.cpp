#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void load(int *gun, int *b, int *l, int *rounds) //load function
//int *a = &x = a points to x
{

    *rounds = rand() % 7 + 2; //2~8 rounds
    *b = 0; //Blanks
    *l = 0; //Lives

    for (int i = 0; i < *rounds; i++) //shell loading
    {
        gun[i] = rand() % 2;
        if (gun[i] == 0)
        {
            (*b)++;
        }
        else
        {
            (*l)++;
        }
    }

    //at least one blank, one live
    if (*b == 0)
    {
        int pos = rand() % (*rounds);
        for (int i = *rounds - 1; i >= pos; i--)
        {
            gun[i] = gun[i - 1];
        }
        gun[pos - 1] = 0; //set blank at pos
        (*b)++;
        (*l)--;
    }
    else if (*l == 0)
    {
        int pos = rand() % (*rounds);
        for (int i = *rounds - 1; i >= pos; i--)
        {
            gun[i] = gun[i - 1];
        }
        gun[pos - 1] = 1; //set live at pos
        (*l)++;
        (*b)--;
    }
}

void itemload(int *itemp1, int *itemp2, int *item, int *itempool)
{
    int countp1=0;
    for(int i=0; i<8; i+=1)
    {
        if(itemp1[i]==0 && countp1<(*item))
        {
            itemp1[i]=rand() % (*itempool) + 1;
            countp1+=1;
        }
        else
        {
            continue;
        }
    }
    int countp2=0;
    for(int i =0; i<8; i+=1)
    {
        if(itemp2[i]==0 && countp2<(*item))
        {
            itemp2[i]=rand() % (*itempool) + 1;
            countp2+=1;
        }
        else
        {
            continue;
        }
    }
}

void selfshotresults(int *player, int *gun, int *shell, int *b, int *l, int *turn, int *cuffflag, int *sawflag, int *invertflag)
{
    if(gun[(*shell)]==0)
    {
        if((*sawflag)==1)
        {
            printf("P%d is safe, and the gun remains sawed.\n\n", (*turn+1));
        }
        else
        {
            printf("P%d shoots himself and is safe.\n\n", (*turn+1));
        }

        if((*invertflag==1))
        {
            (*l)-=1;
            (*invertflag)=0;
        }
        else
        {
            (*b)-=1;
        }
        (*shell)+=1;

        if((*turn) == 0)
        {
            (*turn)=0;
        }
        else
        {
            (*turn=1);
        }


    }
    else
    {
        if((*sawflag)==1)
        {
            printf("P%d regrets his decision to saw the barrel.\n\n", (*turn+1));
            (*player)= (*player)>2 ? (*player)-2:0;
            (*sawflag)=0;
        }
        else
        {
            printf("P%d shoots himself and takes a hit.\n\n", (*turn+1));
            (*player)-=1;
        }

        if((*invertflag==1))
        {
            (*b)-=1;
            (*invertflag)=0;
        }
        else
        {
            (*l)-=1;
        }
        (*shell)+=1;

        if((*cuffflag)==-1)
        {
            (*cuffflag)=0;
        }
        if((*turn) == 0)
        {
            (*turn)=1;
        }
        else
        {
            (*turn=0);
        }
    }
}

void oppshotresults(int *player, int *opp, int *gun, int *shell, int *b, int *l, int *turn, int *cuffflag, int *sawflag, int *invertflag)
{
    if(gun[(*shell)]==0)
    {
        if((*sawflag)==1)
        {
            printf("P%d's attempt at more damage failed.\n\n", (*turn+1));
            (*sawflag)=0;
        }
        else
        {
            printf("P%d shoots opponent and it's a blank.\n\n", (*turn+1));
        }

        if((*invertflag==1))
        {
            (*l)-=1;
            (*invertflag)=0;
        }
        else
        {
            (*b)-=1;
        }
        (*shell)+=1;

        if((*cuffflag)==-1)
        {
            (*cuffflag)=0;
        }
        if((*turn) == 0)
        {
            (*turn)=1;
        }
        else
        {
            (*turn=0);
        }
    }
    else
    {
        if((*sawflag)==1)
        {
            printf("P%d hits the opponent with double damage.\n\n", (*turn+1));
            (*opp)= (*opp)>2 ? (*opp)-2:0;
            (*sawflag)=0;
        }
        else
        {
            printf("P%d shoots opponent and it's a live.\n\n", (*turn+1));
            (*opp)-=1;
        }

        if((*invertflag==1))
        {
            (*b)-=1;
            (*invertflag)=0;
        }
        else
        {
            (*l)-=1;
        }
        (*shell)+=1;

        if((*cuffflag)==-1)
        {
            (*cuffflag)=0;
        }
        if((*turn) == 0)
        {
            (*turn)=1;
        }
        else
        {
            (*turn=0);
        }
    }

}

void itemuse(int *turn, int *item, int *item2, int *iteminput, int *player, int *maxHP, int *gun, int *rounds, int *b, int *l, int *shell, int *cuffflag, int *sawflag, int *invertflag, int *adreflag)
{

    int chance = rand() % 2;

    int burner=0;
    if((*shell+1)<(*rounds))
    {
        burner = rand() % ((*rounds)-((*shell)+1)) + 1;
    }
    else
    {
        burner=0;
    }


    if(item[*iteminput-1]==9)
    {
        int stealinput=0;

        printf("P%d used Adrenaline.\n", *turn+1);
        item[*iteminput-1]=0;
        (*adreflag)=1;

        printf("\nYour Items:\n");
        for (int i=0; i<8; i++)
        {
            printf("%d ", item[i]);
        }
        printf("\nOpponent's Items:\n");
        for (int i=0; i<8; i++)
        {
            printf("%d ", item2[i]);
        }

        printf("\n\nChoose which item to steal (1~8)...> ");
        scanf("%d", &stealinput);
        if(stealinput<=0)
        {
            while(stealinput<=0)
            {
                printf("Item not chosen.\n");
                printf("Choose which item to steal (1~8)...> ");
                scanf("%d", &stealinput);
            }
        }

        if(item2[stealinput-1]==9)
        {
            while(item2[stealinput-1]==9)
            {
                printf("You can't steal adrenaline.\n");
                printf("Choose which item to steal (1~8)...> ");
                scanf("%d", &stealinput);
            }
        }
        system("cls");
        itemuse(turn, item2, item, &stealinput, player, maxHP, gun, rounds, b, l, shell, cuffflag, sawflag, invertflag, adreflag);
    }
    else
    {
        switch(item[(*iteminput-1)])
        {
        case 0:
            printf("It's an empty slot, P%d.\n\n", *turn+1);
            break;

        case 1:
            printf("P%d used Beer.\n", *turn+1);
            if(gun[(*shell)]==1)
            {
                printf("The discarded shell is live.\n\n");
                (*l)-=1;
            }
            else
            {
                printf("The discarded shell is blank.\n\n");
                (*b)-=1;
            }
            (*shell)+=1;
            item[*iteminput-1]=0;
            break;

        case 2:
            printf("Used Cigar.\n");
            if((*player)<(*maxHP))
            {
                printf("P%d has calmed their nerves. +1HP\n\n", *turn+1);
                (*player)+=1;
            }
            else
            {
                printf("P%d has calmed their nerves, but to no avail.\n\n", *turn+1);
            }
            item[(*iteminput-1)]=0;
            break;

        case 3:
            printf("P%d used Handsaw.\n", *turn+1);
            printf("Next shot deals 2 damage if it's a live.\n\n");
            (*sawflag)=1;
            item[(*iteminput)-1]=0;
            break;

        case 4:
            if((*cuffflag)==0)
            {
                printf("P%d used Handcuffs.\n", *turn+1);
                printf("Opponent skips the next turn.\n\n");
                if(*turn==0)
                {
                    (*cuffflag)=2;
                }
                else
                {
                    (*cuffflag)=1;
                }
                item[(*iteminput)-1]=0;
            }
            else if((*cuffflag)==-1 || (*cuffflag)==1)
            {
                printf("Handcuffs were used last turn.\n\n");
            }
            break;

        case 5:
            printf("P%d used Magnifying glass.\n", *turn+1);
            if(gun[*shell]==1)
            {
                printf("The current shell is live.\n\n");
            }
            else
            {
                printf("The current shell is blank.\n\n");
            }
            item[(*iteminput)-1]=0;
            break;

        case 6: //Med
            if(chance==0)
            {
                printf("P%d used Expired medicine and drops to the floor. -1HP\n\n", *turn+1);
                (*player)-=1;
            }
            else
            {
                if((*player)==(*maxHP))
                {
                    printf("P%d used Expired medicine, but to no avail.\n\n", *turn+1);
                }
                else if(((*player)+2)>=(*maxHP))
                {
                    printf("P%d used Expired medicine and heals to full health. +%dHP\n\n", *turn+1, ((*player)+2)>6 ? 1:2);
                    (*player)=(*maxHP);
                }
                else
                {
                    printf("P%d used Expired medicine and got lucky. +2HP\n\n", *turn+1);
                    (*player)+=2;
                }
            }
            item[(*iteminput)-1]=0;
            break;

        case 7: //Inv
            printf("P%d used Inverter.\n", *turn+1);
            if(gun[(*shell)]==1)
            {
                gun[(*shell)]=0;
            }
            else
            {
                gun[(*shell)]=1;
            }

            (*invertflag)=1;
            printf("The current shell's type is inverted.\n\n", *turn+1);
            item[(*iteminput)-1]=0;
            break;

        case 8: //Burner
            printf("P%d used Burner phone.\n", *turn+1);

            if(burner==0)
            {
                printf("Unfortunately, it showed a static screen.\n");
                printf("You probably already know what shell it is though.\n\n");
            }
            else if(gun[burner]==1)
            {
                printf("Shell #%d currently in shotgun is live.\n\n", burner+1);
            }
            else if(gun[burner]==0)
            {
                printf("Shell #%d currently in shotgun is blank.\n\n", burner+1);
            }
            item[(*iteminput)-1]=0;
            break;


        default:
            printf("Item not found.\n\n");
            break;
        }
    }
}

void itemlist(int *itempool)
{
    printf("1: Beer, Reveal and eject one shell.\n");
    printf("2: Cigar, Heal for 1 HP.\n");
    printf("3: Handsaw, Next live shell deals double damage.\n");
    printf("4: Handcuffs, Opponent skips a turn.\n");
    printf("5: Magnifying Glass, Reveals next shot.\n");

    if((*itempool)==9)
    {
        printf("6: Expired Medicine, 50% chance to heal 2 HP or deal 1 damage.\n");
        printf("7: Inverter, Inverts the type of the current shell.\n");
        printf("8: Burner Phone, Reveals one random shell except the next one in the shotgun.\n");
        printf("9: Adrenaline, Steal one item from opponent and use it immediately.\n\n");
    }
    else
    {
        printf("\n");
    }
}

int main()
{
    int rounds;
    int b, l;
    int gun[8]; //up to 8 rounds
    int itemp1[8] {0};
    int itemp2[8] {0};

    int input = 0;
    int iteminput = 0;

    int item;
    int itempool = 0;
    int maxHP;
    int p1, p2;

    int shell = 0; //shell counter
    int sawflag = 0; //sawed-off check
    int cuffflag = 0; //handcuff check
    int invertflag = 0; //invert check
    int adreflag = 0; //check for adrenaline used


    srand( time(NULL) );

    printf("Buckshot Roulette Recreation\n\n");

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

    printf("Choose your item pool(1: 5 items 2: 9 items)...> ");
    scanf("%d", &itempool);
    if(itempool<=0 || itempool>=3)
    {
        while(maxHP<=0)
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

    int turn = rand() % 2;

    load(gun, &b, &l, &rounds); //call load function

    itemload(itemp1, itemp2, &item, &itempool);

    printf("\n");
    itemlist(&itempool);

    while (p1 > 0 && p2 > 0)
    {
        printf("P1: %d HP, P2: %d HP\n", p1, p2);

        if(itempool==5)
        {
            printf("%d lives, %d blanks, Gun sawed = %d\n", l, b, sawflag);
        }
        else
        {
            printf("%d lives, %d blanks, Gun sawed = %d, Shell inverted = %d\n", l, b, sawflag, invertflag);
        }

        printf("P%d's turn.\n", turn+1);
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
                printf("\nYour Items:\n");
                for (int i=0; i<8; i++)
                {
                    printf("%d ", itemp1[i]);
                }
                printf("\nOpponent's Items:\n");
                for (int i=0; i<8; i++)
                {
                    printf("%d ", itemp2[i]);
                }

                printf("\n\nWhat is your move?\n");
                printf("0 to shoot self, 1 to shoot opponent, 2 to use items, 3 to check item list...> ");
                scanf("%d", &input);

                switch(input)
                {
                case 0:
                    system("cls");
                    //printf(" \e[1;1H\e[2J") also clears screen
                    selfshotresults(&p1, gun, &shell, &b, &l, &turn, &cuffflag, &sawflag, &invertflag);
                    break;

                case 1:
                    system("cls");
                    oppshotresults(&p1, &p2, gun, &shell, &b, &l, &turn, &cuffflag, &sawflag, &invertflag);
                    break;

                case 2:
                    printf("\nChoose an item to use (1~8), 0 to exit...> ");
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
                printf("\nYour Items:\n");
                for (int i=0; i<8; i++)
                {
                    printf("%d ", itemp2[i]);
                }
                printf("\nOpponent's Items:\n");
                for (int i=0; i<8; i++)
                {
                    printf("%d ", itemp1[i]);
                }

                printf("\n\nWhat is your move?\n");
                printf("0 to shoot self, 1 to shoot opponent, 2 to use items, 3 to check item list...> ");
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
                    printf("\nChoose an item to use (1~8), 0 to exit...> ");
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
