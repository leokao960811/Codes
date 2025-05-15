#include <stdio.h>

int sum(const int *x, int sz)
{
    int sum=0;
    for (int i=0; i<sz; i+=1)
    {
        sum+=x[i];
    }
    return sum;
}

float average(const int *x, int sz)
{
    return (float(sum(x,sz))/sz);
}

void print(const int *x, int sz)
{
    for (int i=0; i<sz; i+=1)
    {
        printf("%d ",x[i]);
    }
}

void reset(int *x, int sz)
{
   for (int i=0; i<sz; i+=1)
    {
        x[i]=0;
    }
}


int max_pos(const int *x, int sz)
{
    int pos=0;
    for (int i=1;i<sz;i+=1)
    {
        if(x[i]>x[pos])
        {
            pos=i;
        }
    }
    return pos;
}

int maxnum(const int *x, int sz)
{
    return x[max_pos(x,sz)];
}
