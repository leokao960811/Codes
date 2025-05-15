#include <stdio.h>
int main()
{
    int times,num=0;
    scanf("%d",&times);
    while(num<times)
    {
        int a,b,sum=0;
        scanf("%d",&a);
        scanf("%d",&b);
        for(int i=a; i<=b; i+=1)
        {
            if(i%2==1)
            {
                sum+=i;
            }
        }
        printf("Case %d: %d\n",num+1,sum);
        num+=1;
    }
    return 0;
}
