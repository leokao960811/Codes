#include <stdio.h>
int main()
{
    int n;
    int num=0;
    int form=0;
    int flag=0;
    int ordered[20]{0};

    scanf("%d",&n);
    while (num<n)
    {
        form=0;
        flag=0;
        int a[10] {0};
        for (int i=0; i<10; i+=1)
        {
            scanf("%d",&a[i]);
        }

        if(a[0]>a[1])
        {
            form=0;
        }
        else if (a[0]<a[1])
        {
            form=1;
        }

        for (int i=0; i<9; i+=1)
        {
            if(a[i]>a[i+1] && form == 0)
            {
                continue;
            }
            else if(a[i]<a[i+1] && form == 1)
            {
                continue;
            }
            else
            {
                flag=1;
                break;
            }
        }

        if(flag==0)
        {
            ordered[num]=1;
        }
        else
        {
            ordered[num]=0;
        }
        num+=1;
    }

    printf("Lumberjacks:\n");
    for (int i=0;i<n;i+=1)
    {
        if(ordered[i]==1)
        {
            printf("Ordered\n", form);
        }
        else
        {
            printf("Unordered\n", form);
        }
    }

    return 0;
}
