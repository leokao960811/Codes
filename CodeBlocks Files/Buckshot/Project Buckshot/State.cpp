#include <stdio.h>

void printstate(int *turn, int *p1, int *p2, char *counter, int *shell, int *itempool, int *l, int *b, bool *sawflag, bool *invertflag)
{
    printf("P1: %d HP, P2: %d HP\n", *p1, *p2);

        if((*counter=='Y' || *counter=='y') || *shell==0)
        {
            if(*itempool==5)
            {
                printf("%d lives, %d blanks, Gun sawed = %d\n", *l, *b, *sawflag);
            }
            else
            {
                printf("%d lives, %d blanks, Gun sawed = %d, Shell inverted = %d\n", *l, *b, *sawflag, *invertflag);
            }

        }
        else
        {
            if(*itempool==5)
            {
                printf("%d shells left, Gun sawed = %d\n", (*l+*b), *sawflag);
            }
            else
            {
                printf("%d shells left, Gun sawed = %d, Shell inverted = %d\n", (*l+*b), *sawflag, *invertflag);
            }
        }

        printf("P%d's turn.\n", *turn+1);
}

void TableState(const int *itemp1, const int *itemp2)
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
}

