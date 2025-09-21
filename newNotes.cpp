#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <new> // for nothrow

//using namespace std; // if you want to just write nothrow instead of std::nothrow, but not recommended!

struct T
{
    int value=10;
    int test;
};

int main()
{

//  Objects allocated with new are default-initalized.

//  T *p = new T;
//  printf("%d",p->value);
    int *p =new (std::nothrow) int{4}; //single value
    printf("%d\n",*p);
    delete p;

//  arrays can be initalized with {}.
    int *q =new (std::nothrow) int [5]{1,6,4};
    for(int i=0;i<5;i+=1)
    {
        printf("%d ",*(q+i));
    }
    delete [] q; //delete arrays with [] q;

    printf("\n\n");

    T *r = new (std::nothrow) T[3]{};
    delete [] r;

//  Allocating a 2D array with new - 1
    int (*matrix)[5] = new (std::nothrow) int[3][5];

    for(int i=0;i<3;i+=1)
    {
        for(int j=0;j<5;j+=1)
        {
            matrix[i][j]=i*j;
        }
    }

    for(int i=0;i<3;i+=1)
    {
        for(int j=0;j<5;j+=1)
        {
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }

    delete [] matrix;

    printf("\n");

//  Allocating a 2D array with new - 2
    int **matrix2 = new (std::nothrow) int *[5];
    for(int i=0;i<5;i+=1)
    {
        matrix2[i] = new (std::nothrow) int [3];
    }

    for(int i=0;i<5;i+=1)
    {
        for(int j=0;j<3;j+=1)
        {
            matrix2[i][j] = i*j;
        }
    }

    for(int i=0;i<5;i+=1)
    {
        for(int j=0;j<3;j+=1)
        {
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");
    }

    for(int i=0; i<5; i+=1)
    {
        delete [] matrix2[i];
    }

    delete [] matrix2;

//  Dealing with failed allocation
    int *s = new (std::nothrow) int{};
    if(s==nullptr) {printf("\nNot enough memory!\n");}



    return 0;
}
