#include <stdio.h>
#include <string.h>
int main()
{
    constexpr int MaxSize = 100;
    int r = 0, c = 0, t = 1;
    while (scanf("%d%d", &r, &c)==2 && r && c)
    {
        char board[MaxSize+2][MaxSize+2] = {};
        char result[MaxSize+2][MaxSize+2] = {};
        for (int i=1; i<=r; i+=1)
        {
            scanf("%s", &board[i][1]);
        }

        if (t > 1) printf("\n");
        printf("Field #%d:\n",t);
        for (int i=1; i<=r; i+=1)
        {
            for (int j=1; j<=c; j+=1)
            {
                int count=0;
                if(board[i][j]=='*') result[i][j]='*';
                else
                {
                    if(board[i-1][j-1]=='*') count+=1;
                    if(board[i-1][j]=='*') count+=1;
                    if(board[i-1][j+1]=='*') count+=1;
                    if(board[i][j-1]=='*') count+=1;
                    if(board[i][j+1]=='*') count+=1;
                    if(board[i+1][j-1]=='*') count+=1;
                    if(board[i+1][j]=='*') count+=1;
                    if(board[i+1][j+1]=='*') count+=1;
                    result[i][j] = '0' + count;
                }
                printf("%c",result[i][j]);
            }
            printf("\n");
        }
        t+=1;
    }
}
