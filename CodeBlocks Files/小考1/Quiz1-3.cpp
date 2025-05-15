#include <stdio.h>
int main()
{
    int n;
    while (true)
    {

        scanf("%d",&n);
        if (n == 0)
        {
            break;
        }
        while(n>9)
        {
            int sum=0;
            while(n>=1)
            {
                sum+=(n%10);
                n/=10;
            }
            n=sum;
        }

        printf("%d\n",n);
    }

}



