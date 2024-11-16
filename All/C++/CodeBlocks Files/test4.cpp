#include <stdio.h>
int main()
{
    int w,h,n;
    int x1,x2,y1,y2;
    while (true)
    {
        scanf("%d %d %d", &w, &h, &n);

        if(w==0 && h==0 && n==0) break;
        else
        {

            int board[500][500]= {0};

            for(int i=0; i<n; i+=1)
            {
                scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

                int minX = (x1<x2? x1:x2)-1;
                int maxX = (x1>x2? x1:x2)-1;
                int minY = (y1<y2? y1:y2)-1;
                int maxY = (y1>y2? y1:y2)-1;

                printf("%d %d %d %d\n", minX, minY, maxX, maxY);

                for(int i=minY; i<=maxY; i+=1)
                {
                    for(int j=minX; j<=maxX; j+=1)
                    {
                        board[j][i]=1;
                    }
                }
            }

            int spot=0;
            for(int i=0; i<w; i+=1)
            {
                for(int j=0; j<h; j+=1)
                {
                    if(board[i][j]==0)
                    {
                        spot+=1;
                    }
                }
            }

            if(spot==0)
            {
                printf("There is no empty spots.\n");
            }
            else if(spot==1)
            {
                printf("There is one empty spot.\n");
            }
            else
            {
                printf("There are %d empty spots.\n",spot);
            }

        }
    }

    return 0;
}
