#include <stdio.h>
#include "mychar.h"

int main()
{
    char a;

    printf("Input a character: ");
    a = getchar();
    if(isalpha2(a))
    {
        printf("%c is in the alphabet.\n", a);
        if(isupper2(a))
        {
            printf("%c is uppercase.\n", a);
            printf("It's lowercase form is %c.\n", tolower2(a));
        }
        else if(islower2(a))
        {
            printf("%c is lowercase.\n", a);
            printf("It's uppercase form is %c.\n", toupper2(a));
        }
    }
    else if (isdigit2(a)) printf("%c is a digit.\n", a);
    else printf("%c is unidentifiable.\n", a);



    return 0;
}
