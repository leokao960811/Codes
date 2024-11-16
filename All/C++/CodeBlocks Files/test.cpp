#include <stdio.h>
int main()
{
    int tries=1;
    int z,i,m,l;

    while (true)
    {
        int n=0;

        scanf("%d%d%d%d",&z, &i, &m, &l);
        if(z==0 && i==0 && m==0 && l==0) break;

        int num_list[m] {0};

        int num = ((z * l) + i) % m;
        while(num_list[num]==0)
        {
            num_list[num]=1;
            num = ((z * num) + i) % m;
            n+=1;
        }

        printf("Case %d: %d\n",tries, n);
        tries+=1;
    }

    return 0;
}
