#include <stdio.h>
int main()
{
    int t=0, n=0, lind=0, l=0;
    int times=0;
    int a[10] {0};
    int winner[10] {0};

    scanf("%d%d", &t, &n);
    while(times<t)
    {
        for (int i=0; i<n; i+=1)
        {
            scanf("%d",&a[i]);
        }

        l=a[0];
        for (int i=1; i<n; i+=1)
        {
            if (a[i]>l)
            {
                l=a[i];
            }
        }

        for (int i=0; i<n; i+=1)
        {
            if (l==a[i])
            {
                winner[i]+=1;
            }
        }
        times+=1;
    }

    l=winner[0];
      for (int i=1; i<n; i+=1)
    {
        if (winner[i]>l)
        {
            l=winner[i];
        }
    }

    for (int i=0; i<n; i+=1)
    {
        if (l==winner[i])
        {
            printf("%d ", i+1);
        }
    }

    return 0;
}

