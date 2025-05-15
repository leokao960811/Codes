#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selfshotresults(int *player, int *gun, int *shell, int *b, int *l, int *turn, int *cuffflag, bool *sawflag, bool *invertflag)
{
    if(gun[(*shell)]==0)
    {
        if((*sawflag)==true)
        {
            printf("P%d is safe, and the gun remains sawed.\n\n", (*turn+1));
        }
        else
        {
            printf("P%d shoots himself and is safe.\n\n", (*turn+1));
        }

        if((*invertflag==true))
        {
            (*l)-=1;
            (*invertflag)=false;
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
        if((*sawflag)==true)
        {
            printf("P%d regrets his decision to saw the barrel. P%d -2HP\n\n", (*turn+1), (*turn+1));
            (*player)= (*player)>2 ? (*player)-2:0;
            (*sawflag)=0;
        }
        else
        {
            printf("P%d shoots himself and takes a hit. P%d -1HP\n\n", (*turn+1), (*turn+1));
            (*player)-=1;
        }

        if((*invertflag==true))
        {
            (*b)-=1;
            (*invertflag)=false;
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

void oppshotresults(int *player, int *opp, int *gun, int *shell, int *b, int *l, int *turn, int *cuffflag, bool *sawflag, bool *invertflag)
{
    if(gun[(*shell)]==0)
    {
        if((*sawflag)==true)
        {
            printf("P%d's attempt at more damage failed.\n\n", (*turn+1));
            (*sawflag)=false;
        }
        else
        {
            printf("P%d shoots opponent and it's a blank.\n\n", (*turn+1));
        }

        if((*invertflag==true))
        {
            (*l)-=1;
            (*invertflag)=false;
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
        if((*sawflag)==true)
        {
            printf("P%d hits the opponent with double damage. P%d -2HP\n\n", (*turn+1), ((*turn)+1)==1 ? 2:1);
            (*opp)= (*opp)>2 ? (*opp)-2:0;
            (*sawflag)=false;
        }
        else
        {
            printf("P%d shoots opponent and it's a live. P%d -1HP\n\n", (*turn+1), ((*turn)+1)==1 ? 2:1);
            (*opp)-=1;
        }

        if((*invertflag==true))
        {
            (*b)-=1;
            (*invertflag)=false;
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

void itemuse(int *turn, int *item, int *item2, int *iteminput, int *player, int *maxHP, int *gun, int *rounds, int *b, int *l, int *shell, int *cuffflag, bool *sawflag, bool *invertflag, bool *adreflag)
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
        (*adreflag)=true;

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

        printf("\n\nChoose which itemslot to steal (1~8)...> ");
        scanf("%d", &stealinput);
        if(stealinput<=0)
        {
            while(stealinput<=0)
            {
                printf("Item not chosen.\n");
                printf("Choose which itemslot to steal (1~8)...> ");
                scanf("%d", &stealinput);
            }
        }

        if(item2[stealinput-1]==9)
        {
            while(item2[stealinput-1]==9)
            {
                printf("You can't steal adrenaline.\n");
                printf("Choose which itemslot to steal (1~8)...> ");
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
            (*sawflag)=true;
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

            (*invertflag)=true;
            printf("The current shell's type is inverted.\n\n");
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
        printf("6: Expired Medicine, 50%% chance to heal 2 HP or deal 1 damage.\n");
        printf("7: Inverter, Inverts the type of the current shell.\n");
        printf("8: Burner Phone, Reveals one random shell except the next one in the shotgun.\n");
        printf("9: Adrenaline, Steal one item from opponent and use it immediately.\n\n");
    }
    else
    {
        printf("\n");
    }
}
