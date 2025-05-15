#include <stdio.h>
#include <stdlib.h>
#include <new> // for nothrow

struct DynaIntArray
{
    int size = 0;
    int *data = nullptr;
};

bool Create(DynaIntArray *arr, int size)
{
    arr->data=new (std::nothrow) int [size] {};

    if(arr->data)
    {
        arr->size=size;
        return true;
    }
    else return false;
}

void Print(DynaIntArray *arr)
{
    for(int i=0; i<arr->size; i+=1)
    {
        printf("%d ",arr->data[i]);
    }
}

void Destroy(DynaIntArray *arr)
{
    delete [] arr->data;
    arr->data=nullptr;
    arr->size=0;
}

bool Copy(DynaIntArray *arr2, const DynaIntArray *arr)
{
    int *temp = new (std::nothrow) int [arr->size]{};

    if(temp)
    {
        for(int i=0; i<arr->size; i+=1)
        {
            temp[i]=arr->data[i];
        }


        arr2->size=arr->size;
        //Delete after copying is done.
        delete [] arr2->data;
        arr2->data = temp;

        return true;
    }
    else
    {
        return false;
    }
}


int main()
{
    DynaIntArray arr;
    int n=5;
    Create(&arr, n);
    for (int i=0; i<arr.size; i+=1)
    {
        arr.data[i] = i*10;
    }
    printf("Line 1: ");
    Print(&arr);
    printf("\n");

    DynaIntArray arr2;

    Copy(&arr2, &arr);

    printf("Line 2: ");
    Print(&arr2);

    //Causes the data pointer to point to the same place
    //Therefore, changes arr as well!
//    arr2=arr;
//    arr2.data[0]=9999;
//    Print(&arr);

    Destroy(&arr);
    Destroy(&arr2);

    return 0;
}

