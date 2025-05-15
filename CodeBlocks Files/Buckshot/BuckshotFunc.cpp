#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void load(int *gun, int *b, int *l, int *rounds) //Load function
//int *a = &x = a points to x
{

    *rounds = rand() % 7 + 2; //2~8 rounds
    *b = 0; //Blanks
    *l = 0; //Lives

    for (int i = 0; i < *rounds; i++) //Shell Loading
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

    //At least one blank, one live
    if (*b == 0)
    {
        int pos = rand() % (*rounds);
        for (int i = *rounds - 1; i >= pos; i--)
        {
            gun[i] = gun[i - 1];
        }
        gun[pos - 1] = 0; //Blank at pos
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
        gun[pos - 1] = 1; //Live at pos
        (*l)++;
        (*b)--;
    }
}

int main()
{
    int rounds;
    int b, l;
    int gun[8];
    srand( time(NULL) );



    for (int i=0; i<20; i++)
    {

        load(gun, &b, &l, &rounds); // Call function

        // Print results
        printf("Number of rounds: %d\n", rounds);
        for (int i = 0; i < rounds; i++)
        {
            printf("%d ", gun[i]);
        }
        printf("\nLive: %d, Blank: %d\n", l, b);

        if(i<19)
        {

            printf("\n");
        }



    }
    return 0;
}
