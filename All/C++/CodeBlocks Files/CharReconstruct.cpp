#include <stdio.h>
#include <string.h>

int main()
{
    char str[100] = {};

    int sum=0;

    printf("Please input a string...> ");
    scanf("%s",str);
    printf("Your input is %s.\n", str);

    for (int i = 0; i<strlen(str); i+=1)
    {
        if(str[i]-'0'<0 || str[i]-'0'>9)
        {
            printf("Input isn't a full number.\n");
            break;
        }
        else
        {
            sum = sum*10 + (str[i]-'0');
        }
    }

    printf("The number of the inputted string is %d.\n",sum);

    printf("The length of your input is %d.\n",strlen(str));




}
