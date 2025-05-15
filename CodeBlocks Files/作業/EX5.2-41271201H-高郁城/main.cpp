#include "mygraph.h"
#include "mymath.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{

    srand( time(NULL) );
    int v = UniformRand(0, 100); // return a random value in [0, 100]

    if (IsOdd(v))
    {
        printf("%d is odd.\n", v);
    }
    else
    {
        printf("%d is even.\n", v);
    }

    if (IsPrime(v))
    {
        printf("%d is prime.\n", v);
    }
    else
    {
        printf("%d isn't prime.\n", v);
    }

    printf("Also, the Euclidean distance between (0, 0) and (1, 2) is %f.\n\n",
           EuclideanDistance(0, 0, 1, 2));


    printf("Here's a line of %d:\n",(v%10+1));
    DrawLine((v%10+1));
    printf("\n");

    printf("Here's a rectangle with width of %d and length of %d:\n", (v%10+1), v%15);
    DrawRectangle((v%10+1), v%15);
    printf("\n");

    printf("Here's a square with length of %d:\n", (v%10)+2);
    DrawSquare((v%10+2));

    return 0;
}
