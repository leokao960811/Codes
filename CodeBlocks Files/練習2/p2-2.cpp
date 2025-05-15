#include <stdio.h>
int main()
{
    int r,n;
    int input;

    while (scanf("%d %d", &n, &r) != EOF)
    {
        int diver[n] {0};
        int flag=0;

        for (int i=0; i<r; i+=1)
        {
            scanf("%d",&input);
            diver[input-1]=1;
        }

        for (int i=0; i<n; i+=1)
        {
            if(diver[i]==0)
            {
                printf("%d ",i+1);
                flag=1;
            }
        }

        if (flag==0)
        {
            printf("*");
        }

        printf("\n");

    }

    return 0;
}
