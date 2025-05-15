#include <stdio.h>
int main()
{
    int win_num[6] = {0};
    int num;

    printf("Invoice Checker\n\n");
    printf("Please input six winning numbers (<=999)...>\n");
    for (int i=0; i<6; i++)
    {
        scanf("%d",&win_num[i]);
    }

    printf("\nNow, please input your numbers(<=999), -1 to exit...>\n");
    while (true)
    {
        scanf("%d",&num);
        if(num<0) break;
        for (int i=0; i<6; i++)
        {
            if(num==win_num[i])
            {
                printf("Congratulations!\n");
            }
        }
    }
    printf("Thanks for using.");

    return 0;
}
