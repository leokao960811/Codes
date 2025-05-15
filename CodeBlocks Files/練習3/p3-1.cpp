#include <stdio.h>
#include <string.h>
int main()
{
    int T = 0;
    scanf("%d", &T);
    for (int t=1; t<=T; t+=1)
    {
        char dummy;
        int n = 0, flag = 0;
        scanf(" %c %c %d", &dummy, &dummy, &n);
        long long int matrix[100][100] = {};

        for (int i=0; i<n; i+=1)
        {
            for (int j=0; j<n; j+=1)
            {
                scanf("%lld", &matrix[i][j]);
                if(matrix[i][j]<0)
                {
                    flag=1;
                }
            }
        }

        for (int i=0; i<n && (!flag); i+=1)
        {
            for (int j=0;j<n;j+=1)
            {
                if(matrix[i][j] != matrix[n-i-1][n-j-1])
                //Ex. N=3, [0][0] and [2][2],
                //N=5, [0][1] and [4][3],
                {
                    flag=1;
                    break;
                }
            }
        }

        if(flag==0) printf("Test #%d: Symmetric.\n", t);
        else printf("Test #%d: Non-symmetric.\n", t);
    }
}
