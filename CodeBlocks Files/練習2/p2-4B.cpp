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


        for (int k=0; k<75; k+=1)
        {
            scanf("%d",&call[k]);
            for (int i=0; i<5; i+=1)
            {
                for(int j=0; j<5; j+=1)
                {
                    if(board[i][j]==call[k])
                    {
                        board[i][j]=0;
                    }

                    if(board[i][0]==0 && board[i][1]==0 && board[i][2]==0 && board[i][3]==0 && board[i][4]==0 && flag==0)
                    {
                        flag=1;
                        bingocalls=k+1;
                    }
                    if(board[0][j]==0 && board[1][j]==0 && board[2][j]==0 && board[3][j]==0 && board[4][j]==0 && flag==0)
                    {
                        flag=1;
                        bingocalls=k+1;
                    }
                    if(board[0][0]==0 && board[1][1]==0 && board[2][2]==0 && board[3][3]==0 && board[4][4]==0 && flag==0)
                    {
                        flag=1;
                        bingocalls=k+1;
                    }
                    if(board[4][0]==0 && board[3][1]==0 && board[2][2]==0 && board[1][3]==0 && board[0][4]==0 && flag==0)
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
