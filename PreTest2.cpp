#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int n;
    scanf("%d", &n); fgetc(stdin);
    for (int i = 0; i < n; i++) {
            int sum=0;
        char card[21];
        scanf("%[^\n]", card); fgetc(stdin);
        for (int i = 0; i < 21; i++)
        {
            if(isdigit(card[i]))
            {
                if ((i%5==0) || (i%5==2))
                {
                    int num=(card[i]-'0')*2;
                    printf("%d ",num);
                    if (num>=10)
                    {
                        sum+=(num-9);
                    }
                    else
                    {
                        sum+=num;
                    }
                }
                else
                //else if ((i%5==0) || (i%5==2))
                {
                    sum+=(card[i]-'0');
                }
            }
        }
        if(sum%10==0) printf("YES");
        else printf("NO");
    }




    // Write an answer using printf(). DON'T FORGET THE TRAILING \n
    // To debug: fprintf(stderr, "Debug messages...\n");

    //printf("YES or NO\n");

    return 0;
}
