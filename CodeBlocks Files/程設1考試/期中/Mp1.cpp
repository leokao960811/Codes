#include <stdio.h>
int main()
{
    int a;
    scanf("%d", &a);

    for (int t=1; t<=a; t+=2)
    {
        for (int i=1; i<=t; i+=2)
        {
            for (int j=0; j<(a-i); j+=2)
            {
                printf(" ");
            }
            for(int k=0; k<i; k+=1)
            {
                printf("%d",i);
            }

            if(i<=a-2)
            {
                printf("\n");
            }
        }
    }
    return 0;
}
