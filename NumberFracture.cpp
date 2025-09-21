#include <stdio.h>

int main()
{

    int a;
    int length=0;
    int num=1;
    int digit_list[10000]={0};

    scanf("%d",&a);

    while(a>0)
    {
        int digit=a%10;
        digit_list[length]=digit;
        a-=digit;
        a/=10;

        length+=1;
    }

    for(int i=length-1;i>=0;i-=1)
    {
        printf("%d ",digit_list[i]);
        //printf("%c",(digit_list[i]+'0'));
    }


    printf("\n%d", length);





    return 0;
}

