#include <stdio.h>
int main()
{
    int i=0,n=0;
    int a[4000]= {0};
    int cnt=0;

    while(scanf("%d", &cnt) == 1)
    {
        int flag=0;
        int record[4000]= {0};
        for (int i=0; i<cnt; i+=1)
        {
            scanf("%d", &a[i]);
        }

        for(int i=1; i<cnt; i+=1)
        {
            int diff=(a[i]-a[i-1]);
            if (diff<0) diff=-diff;
            record[diff]=1;
        }

        for(int i=1; i<cnt; i+=1)
        {
            if (record[i]==0)
            {
                flag=1;
                break;
            }
        }

        if(flag==0) printf("Jolly\n");
        else printf("Not jolly\n");

    }
}
