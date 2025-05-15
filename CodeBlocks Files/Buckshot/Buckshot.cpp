#include <stdio.h>
#include <stdlib.h> // rand
#include <time.h>   // srand( time(NULL) ) 
//int load(){

//}
int main()
{
    srand( time(NULL) );
    int round = rand() % 7 + 2;
    int b=0, l=0, n=8;
    int gun[8];

    printf("%d\n", round);
    for (int i=0; i<round; i+=1)
    {
        gun[i] = rand()%2;
        if(gun[i]==0)
        {
            b += 1;
        }
        else
        {
            l += 1;
        }
    }
    //printf("Live: %d, Blank: %d\n",l,b);

    if(b==0)
    {
        n += 1;
        int pos = rand() % round;
        // shift elements forward
        for (int i = round - 1; i >= pos; i--)
            gun[i] = gun[i - 1];

        // insert x at pos
        gun[pos - 1] = 0;
        b += 1;
        l -= 1;
    }
    else if(l==0)
    {
        n += 1;
        int pos = rand() % round;
        // shift elements forward
        for (int i = round - 1; i >= pos; i--)
            gun[i] = gun[i - 1];

        // insert x at pos
        gun[pos - 1] = 1;
        b -= 1;
        l += 1;
    }

    for (int i=0; i<round; i+=1)
    {
        printf("%d ",gun[i]);
    }
    printf("\nLive: %d, Blank: %d",l,b);

    return 0;
}

