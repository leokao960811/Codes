#include <stdio.h>
int main()
{
    int n,num=0;
    int board[5][5] {0};
    int call[75] {0};

    scanf("%d",&n);
    while(num<n)
    {
        int bingocalls=0;
        int mark[5][5] {0};
        int flag=0;
        for (int i=0; i<5; i+=1)
        {
            for(int j=0; j<5; j+=1)
            {
                if(i==2 && j==2)
                {
                    continue;
                }
                else scanf("%d", &board[i][j]);

            }
        }

        mark[2][2]=1;

        for (int k=0; k<75; k+=1)
        {
            scanf("%d",&call[k]);
            for (int i=0; i<5; i+=1)
            {
                for(int j=0; j<5; j+=1)
                {
                    if(board[i][j]==call[k])
                    {
                        mark[i][j]=1;
                    }

                    if(mark[i][0]==1 && mark[i][1]==1 && mark[i][2]==1 && mark[i][3]==1 && mark[i][4]==1 && flag==0)
                    {
                        flag=1;
                        bingocalls=k+1;
                    }
                    if(mark[0][j]==1 && mark[1][j]==1 && mark[2][j]==1 && mark[3][j]==1 && mark[4][j]==1 && flag==0)
                    {
                        flag=1;
                        bingocalls=k+1;
                    }
                    if(mark[0][0]==1 && mark[1][1]==1 && mark[2][2]==1 && mark[3][3]==1 && mark[4][4]==1 && flag==0)
                    {
                        flag=1;
                        bingocalls=k+1;
                    }
                    if(mark[4][0]==1 && mark[3][1]==1 && mark[2][2]==1 && mark[1][3]==1 && mark[0][4]==1 && flag==0)
                    {
                        flag=1;
                        bingocalls=k+1;
                    }
                }
            }
        }

        printf("BINGO after %d numbers announced\n",bingocalls);
        num+=1;
    }

    return 0;
}
