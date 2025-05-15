#include <stdio.h>
#include <string.h>

int main()
{
    int sz=0;
    char board[10][10] = {};

    scanf("%d", &sz);

    for (int i=0; i<sz; i+=1)
    {
        scanf("%s", &board[i][0]);
    }

    char res[10][10] = {' '};
    for (int i=0; i<sz; i+=1)
    {
        for(int j=0; j<sz; j+=1)
        {
            if( board[i][j]-'0'>0 && board[i][j]-'0'<10)
            {
                res[i][j]=board[i][j];
                int range=(board[i][j]-'0');
                for(int pi=1; pi<=range; pi+=1)
                {
                    if(i+pi>sz || board[i+pi][j]=='X') break;
                    else board[i+pi][j]='O';
                }
                for(int pi=1; pi<=range; pi+=1)
                {
                    if(i-pi<0 || board[i-pi][j]=='X') break;
                    else board[i-pi][j]='O';
                }

                for(int pj=1; pj<=range; pj+=1)
                {
                    if(j+pj>sz || board[i][j+pj]=='X') break;
                    else board[i][j+pj]='O';
                }
                for(int pj=1; pj<=range; pj+=1)
                {
                    if(j-pj<0 || board[i][j-pj]=='X') break;
                    else board[i][j-pj]='O';
                }
            }
            else if(board[i][j]=='X') board[i][j]='X';

        }
    }

    for(int i=0; i<sz; i+=1)
    {
        for(int j=0; j<sz; j+=1)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

