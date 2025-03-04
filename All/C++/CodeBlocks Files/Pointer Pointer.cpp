#include <stdio.h>

int * min_element(int arr[], int DataSize)
{
    int *min=arr; //指到arr[0]

    for(int i=1; i<DataSize; i+=1)
    {
        if (*min>arr[i]) min=&arr[i]; //轉成arr[i]位置
    }

    return min;
}

//const ver.
const int * min_element(const int arr[], int DataSize)
{
    const int *min=arr; //指向arr[0]

    for(int i=1; i<DataSize; i+=1)
    {
        if (*min>arr[i]) min=&arr[i]; //轉成arr[i]位置
    }

    return min;
}

void min_max_element(int **pmin, int **pmax, int arr[], int DataSize)
{
    *pmin=*pmax=arr; //指向arr[0]

    for(int i=1; i<DataSize; i+=1)
    {
        if (**pmin < arr[i]) *pmin = &arr[i];
        else if (**pmax < arr[i]) *pmax = &arr[i];
    }

}

int main()
{
    constexpr int DataSize = 5;
    int arr[DataSize] = {};

    for (int i=0; i<DataSize; i+=1)
    {
        scanf("%d", &arr[i]);
    }

    printf("min: %d\n", *min_element(arr, DataSize));

    int *min = nullptr, *max = nullptr;
    min_max_element(&min, &max, arr, DataSize);
    printf("min: %d, max: %d\n", *min, *max);

    //*min = 0;
    //*max = 100;

    for (int i=0; i<DataSize; i+=1)
    {
        printf("%d ", arr[i]);
    }
}
