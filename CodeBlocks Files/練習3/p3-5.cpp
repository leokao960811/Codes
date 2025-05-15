#include <stdio.h>
#include <string.h>
int main()
{
    constexpr int MaxNameLen = 12;
    int n = 0, t = 0;
    while (scanf("%d", &n) == 1)
    {
        char group[10][MaxNameLen+1] = {};
        int balance[10] = {};
        for (int i=0; i<n; i+=1)
        {
            scanf("%s", group[i]);
        }

        for (int i=0; i<n; i+=1)
        {
            char giver[MaxNameLen+1] = {}, taker[MaxNameLen+1] = {};

            int paid = 0, num_takers = 0;
            scanf("%s %d %d", giver, &paid, &num_takers);

            int got = num_takers>0?paid/num_takers:0;

            paid = got*num_takers;

            for (int j=0; j<n; j+=1)
            {
                if (strcmp(group[j], giver) == 0)
                {
                    balance[j] -= paid;
                    break;
                }
            }

            for (int i=0; i<num_takers; i+=1)
            {
                scanf("%s", taker);
                for (int j=0; j<n; j+=1)
                {
                    if (strcmp(group[j], taker) == 0)
                    {
                        balance[j] += got;
                        break;
                    }
                }

            }
        }

        if (t > 0) printf("\n");
        t+=1;

        for (int i=0; i<n; i+=1)
        {
            printf("%s %d\n",group[i],balance[i]);
        }
    }
}
