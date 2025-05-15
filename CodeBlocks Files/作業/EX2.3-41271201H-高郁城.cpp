#include <stdio.h>
int main()
{
    int n1,n2,op;
    printf("Advanced Calculator\n");
    printf("First and third numbers are operands, second number is the operator, with 1,2,3,4,5 as +,-,*,/,%% respectively.\n");
    printf("Your Input...> ");
    scanf("%d%d%d",&n1,&op,&n2);

    if(op==1)
    {
        printf("\n%d + %d = %d\n",n1,n2,n1+n2);
    }
    else if(op==2)
    {
        printf("\n%d - %d = %d\n",n1,n2,n1-n2);
    }
    else if(op==3)
    {
        printf("\n%d * %d = %d\n",n1,n2,n1*n2);
    }
    else if(op==4 || op==5)
    {
        if(n2==0)
        {
            printf("\nThe second operand can't be 0.\n");
            printf("Insert the second number again...> ");
            scanf("%d",&n2);
        }
        if(n2==0)
        {
            printf("\n...Are you kidding me?");
        }

        else
        {
            if(op==4)
            {
                printf("%d / %d = %d\n",n1,n2,n1/n2);
            }
            if(op==5)
            {
                printf("%d %% %d = %d\n",n1,n2,n1%n2);
            }
        }
    }
    else
    {
        printf("\nInvalid operator.");
    }

}
