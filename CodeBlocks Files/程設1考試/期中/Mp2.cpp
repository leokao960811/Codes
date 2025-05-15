#include <stdio.h>
int main()
{
    int input=0;
    while (true)
    {
        int flag=0, n1=0, n2=0;
        int div=10, div2=1;
        int n=0;
        //int j=0;
        //int a[9] {0};
        scanf("%d", &input);
        if (input<0) break;

        while(input % div != input)
        {
            n+=1;
            div*=10;
        }
        //printf("%d \n", n);
        div=10;
        while(n>0)
        {


            for (int i=0; i<n; i++)
            {
                div2*=10;
            }

            //printf("%d %d\n",div, div2);

            n1=input/div2;
            if(n1>10)
            {
                while (n1>10)
                {
                    n1=n1%10;
                }
            }

            n2=input%div;
            if(n2>10)
            {
                while (n2>10)
                {
                    n2/=10;
                }
            }
            //printf("%d %d\n", n1, n2);

            if(n1!=n2)
            {
                flag=1;
                break;
            }

            div*=10;
            div2=1;
            n-=1;

        }

        if(flag==0)
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }

    return 0;
}
