#include <stdio.h>
int main()
{
    int x=0, y=0, mx, my;
    int fx=0, fy=0;

    while(true)
    {
        fx=0, fy=0;
        scanf("%d%d", &mx, &my);
        if (mx==0 && my==0)
        {
            printf("%d %d",x,y);
            break;
        }
        if ((x+mx)>0 && (y+my)>0)
        {
            for (int i=1; i<=(x+mx); i+=1)
            {
                if((x+mx)%i == 0 && (x+mx)/i == i)
                {
                    fx=1;
                }
            }

            for (int i=1; i<=(y+my); i+=1)
            {
                if((y+my)%i == 0 && (y+my)/i == i)
                {
                    fy=1;
                }
            }
        }

        if(fx==1 && fy==1)
        {
            continue;
        }
        else
        {
            x+=mx;
            y+=my;
            //printf("%d %d\n", x,y);
        }

    }
    return 0;
}
