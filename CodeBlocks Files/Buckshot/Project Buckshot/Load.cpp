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
