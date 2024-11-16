#include <stdio.h>

int main()
{
    int num=0;
    scanf("%d",&num);
    while(scanf("%d", &num) != EOF)
    {

        int sum=0;

        for (int i=1;i<num;i+=1)
        {
            if(num%i==0)
            {
                sum+=i;
            }
        }

        if(sum==num)
        {
            printf("perfect\n");
        }
        else if(sum>num)
        {
            printf("abundant\n");
        }
        else
        {
            printf("deficient\n");
        }
    }

    return 0;
}
