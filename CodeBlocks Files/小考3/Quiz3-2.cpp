#include <stdio.h>
#include <string.h>
int main()
{

    int cnt=0,n=0;


    scanf("%d", &cnt);

    while(n<cnt)
    {
        int left=0,right=0;
        char str[9]= {};
        scanf("%s",str);

        for(int i=0; i<3; i+=1)
        {
            int power=1;
            for (int j=2; j>i; j-=1)
            {
                power*=26;
            }
            left+=(str[i]-'A')*power;
        }

        for (int i = 4; i<8; i+=1)
        {
            int power=1;
            for (int j=7; j>i; j-=1)
            {
                power*=10;
            }
            right += (str[i]-'0')*power;
        }

        //printf("%d %d", left, right);
        int sum=left-right;
        if (sum<0) sum=-sum;

        if (sum<100) printf("nice");
        else printf("not nice");

        if(n<cnt) printf("\n");
        n+=1;

    }



}
