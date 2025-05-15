#include <stdio.h>
int main()
{
    int times=0;
    int z,i,m,l;
    while (true)
    {

        int n=0;

        scanf("%d%d%d%d",&z, &i, &m, &l);
        if(z==0 && i==0 && m==0 && l==0) break;

        int num_list[m] {0};
        int flag=0;

        while(flag==0)
        {
            int num = ((z * l) + i) % m;
            if(num_list[num]==1)
            {
                flag=1;
            }
            else
            {
                num_list[num]=1;
            }
            l=num;
            n+=1;
        }

        //for(int i=0;i<m;i++)
        //{
            //printf("%d ",num_list[i]);
        //}

        //printf("\n");

        printf("Case %d: %d\n",times+1, n-1);
        times+=1;
    }

    return 0;
}
