#include <stdio.h>

int main()
{
    int hist[10] {0};
    int num;
    printf("Histogram\n");
    printf("Please input scores, -1 to stop and display the histogram...>\n");
    while (true)
    {
        scanf("%d", &num);
        if (num < 0) break;
        if (num == 0)
        {
            hist[0] += 1;
        }
        else if (num % 10 == 0)
        {
            hist[(num / 10) - 1] += 1;
        }
        else
        {
            hist[num / 10] += 1;
        }
    }

    printf("----------------");
    for (int i = 0 ; i < 10; i += 1)
    {
        if(i == 0)
        {
            printf("\n %d ~ %d  ", i, (i + 1) * 10);
        }
        else if(i == 9)
        {
            printf("\n%d ~ %d ", (i * 10) + 1, (i + 1) * 10);
        }
        else
        {
            printf("\n%d ~ %d  ", (i * 10) + 1, (i + 1) * 10);
        }
        for (int j = 0; j < hist[i]; j+=1)
        {
            printf("*");
        }
    }
    return 0;

}
