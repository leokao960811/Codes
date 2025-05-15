#include <stdio.h>
int main()
{
    int n1,n2;
    printf("Insert 2 numbers, results of 5 arithmetic functions will be shown...> ");
    scanf("%d%d",&n1,&n2);

    if(n2==0)
    {
        printf("\nThe second operand can't be 0.\n");
        printf("Insert the second number again...> ");
        scanf("%d",&n2);
    }

    if(n2==0)
    {
        printf("\nPlease stop...\n");
    }

    if(n2!=0)
    {
        printf("\n%d + %d = %d\n",n1,n2,n1+n2);
        printf("%d - %d = %d\n",n1,n2,n1-n2);
        printf("%d * %d = %d\n",n1,n2,n1*n2);
        printf("%d / %d = %d\n",n1,n2,n1/n2);
        printf("%d %% %d = %d\n",n1,n2,n1%n2);
    }
}

