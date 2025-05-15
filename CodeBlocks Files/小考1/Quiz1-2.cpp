#include <stdio.h>
int main()
{
    int x,y,times;
    while (true)
    {
        scanf("%d",&times);
        if (times == 0)
        {
            break;
        }
        scanf("%d%d",&x,&y);
        int num=0;
        while(num<times)
        {
            int posx,posy;
            scanf("%d%d",&posx,&posy);
            if ((posx==x) || (posy==y))
            {
                printf("divisa\n");
            }
            else if ((posx>x) && (posy>y))
            {
                printf("NE\n");
            }
            else if ((posx<x) && (posy>y))
            {
                printf("NO\n");
            }
            else if ((posx>x) && (posy<y))
            {
                printf("SE\n");
            }
            else if ((posx<x) && (posy<y))
            {
                printf("SO\n");
            }

            num+=1;
        }
    }
    return 0;
}
