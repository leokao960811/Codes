#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "numeric.h"
int main()
{

    srand( time(NULL) );

    int sz= rand()% 6 + 5;

    int a[sz];


    reset(a,sz);
    printf("This is a array of %d numbers:\n",sz);
    print(a,sz);

    printf("\n\nLet's assign random values! \n");
    for(int i=0; i<sz;i+=1)
    {
        a[i]=rand()%100+1;
    }
    print(a,sz);


    printf("\n\nThe sum of all numbers is: %d\n",sum(a,sz));

    printf("The calculated average is: %f\n",average(a,sz));
    printf("The largest number is located at position %d,\n",max_pos(a,sz));
    printf("which is %d.\n",maxnum(a,sz));

    return 0;
}
