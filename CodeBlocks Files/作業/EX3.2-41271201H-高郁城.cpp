#include <stdio.h>
int main()
{
    int n1,n2,op;
    printf("Advanced Calculator\n");
    printf("First and third numbers are operands, second number is the operator, with 1,2,3,4,5 as +,-,*,/,%% respectively.\n");
    printf("Input 0 0 0 to end the program.");
    while(true)
    {
        printf("\nYour Input...> ");
        scanf("%d%d%d",&n1,&op,&n2);
        if(n1==0 && op==0 && n2==0)
        {
            printf("\nThanks for using.");
            break;
        }
        else if(op==0 && (n1 !=0 || n2 !=0))
        {
            printf("\nInput 0 0 0 to end the program.");
            continue;
        }
        switch(op)
        {
        case 1:
            printf("\n%d + %d = %d",n1,n2,n1+n2);
            break;
        case 2:
            printf("\n%d - %d = %d",n1,n2,n1-n2);
            break;
        case 3:
            printf("\n%d * %d = %d",n1,n2,n1*n2);
            break;
        case 4:
            if(n2==0)
            {
                while(n2==0)
                {
                    printf("\nThe second operand can't be 0.\n");
                    printf("Insert the second number again...> ");
                    scanf("%d",&n2);
                }
            }
            printf("\n%d / %d = %d",n1,n2,n1/n2);
            break;

        case 5:
            if(n2==0)
            {
                while(n2==0)
                {
                    printf("\nThe second operand can't be 0.\n");
                    printf("Insert the second number again...> ");
                    scanf("%d",&n2);
                }
            }
            printf("\n%d %% %d = %d",n1,n2,n1%n2);
            break;




        default:
        {
            printf("\nInvalid operator. The operand should be 1~5.");
        }
        }
    }
}

