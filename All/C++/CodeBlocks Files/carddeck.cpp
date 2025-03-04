#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void shuffle(int *a, int sz)
{
    for (int i=0; i<sz; i+=1)
    {
        int r = rand()%sz;

        int temp=a[i];
        a[i]=a[r];
        a[r]=temp;
    }

}

char define(int a)
{
    char suit=' ';
    int s = a/13;

    //printf("%d", s);

    if(a%13==0) s-=1;

    if (s==0) suit='S';
    if (s==1) suit='H';
    if (s==2) suit='D';
    if (s==3) suit='C';
    return suit;
}


int main()
{
    srand( time(NULL) );


    int sz=52;
    int a[sz];

    for(int i=0; i<sz; i+=1)
    {
        a[i]=i+1;
    }

    shuffle(a,sz);

    for (int i=0; i<5; i+=1)
    {
        printf("%d ",a[i]);
        if (i==4) printf("\n");
    }

    for (int i=0; i<5; i+=1)
    {
        int num=a[i]%13;
        char face=' ';

        if(num%13>10 || num%13<2)
        {
            if (num==0) face='K';
            if (num==1) face='A';
            if (num==11) face='J';
            if (num==12) face='Q';

            printf("%c%c ", face, define(a[i]));
        }
        else printf("%d%c ", num, define(a[i]));

    }


}
