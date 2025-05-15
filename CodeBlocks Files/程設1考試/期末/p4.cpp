#include <stdio.h>

int min_pos(const int arr[], int sz)
{
    int min = 0;
    for (int i=1; i<sz; i+=1)
    {
        if (arr[i] < arr[min]) min = i;
    }

    return min;
}

void swap(int *p, int *q)
{
    int temp=*p;
    *p = *q;
    *q = temp;
}

void sort(int arr[], int sz)
{
    for (int i=0; i<sz; i+=1)
    {
        int p = min_pos(arr+i,sz-i); //Hardest part of this one.

        swap(arr+i, arr+i+p);
    }
}

int main()
{
    int n=0;
    scanf("%d", &n);
    int arr[10]={0};

    for (int i=0; i<n;i+=1)
    {
        scanf("%d", &arr[i]);
    }

    sort(arr,n);

    for (int i=0; i<n;i+=1)
    {
        printf("%d ", arr[i]);
    }
}

