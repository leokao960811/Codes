#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

bool IsOdd(int v)
{
    return (v%2==1);
}

bool IsPrime(int v)
{
    if (v < 2)
    {
        return false;
    }
    for (int i = 2; i*i <= v; ++i)
    {
        if (v % i == 0)
        {
            return false;
        }
    }

    return true;
}

int Square(int v)
{
    return v*v;
}

int UniformRand(int lb, int ub)
{
    return rand() % (ub - lb + 1) + lb;
} // [lb, ub]

double EuclideanDistance(int x1, int y1, int x2, int y2)
{
    return (sqrt(Square((x2-x1)) + Square((y2-y1))));
}
