#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void PassByValue(int v)
{
    printf("variable v is %d.\n",v);
    v=0;
}

void PassByReference(int &r)
{
    printf("variable r is %d.\n",r);
    r=0;
}

struct BigData
{
    int arr[1000]={0,1,2};
};


void Print(int v) {printf("%d",v);}

void Print(const int *a, int size)
{
    for(int i=0;i<size;i+=1)
    {
        Print(a[i]); //a+i
    }
}

void Print(const BigData &d) {Print(d.arr, 1000);}


void Increase(int &v) {v+=1;}

void Increase(int *a,int size)
{
    for(int i=0;i<size;i+=1) {Increase(a[i]);}
}

void Increase(BigData &d){Increase(d.arr,1000);}



int main()
{
//The uses of '&'
    int x=8, y=7;

    int z=x&y; // uses AND operator on x and y
    int &r=x; //sets a reference for x

    printf("%d %d %d %d\n", x, y, z, r);

    if(&r==&x) //checks r and x's address
    {
        puts("r and x refers to the same variable's address.\n");
    }

//Difference between passing by value and reference
    int num = 10;
    printf("num = %d.\n", num);

    PassByValue(num);
    printf("num = %d.\n", num);

    PassByReference(num);
    printf("num = %d.\n", num);

//Different sizes
    int a;
    int *p = &a;
    int &b=a;

    if(sizeof(a)!=sizeof(p)) {puts("\nDifferent sizes.");}
    if(&a==&b) {puts("Same.\n");}

//References are merely aliases
    int f=10, g=20;
    int *p2=&f;
    int &r2=f;

    *p2=77;
    printf("f = %d, g = %d.\n", f, g);

    r2=88;
    printf("f = %d, g = %d.\n", f, g);

    p2=&g;
    *p2=99;
    printf("f = %d, g = %d.\n", f, g);

    r2=g;
    printf("f = %d, g = %d.\n", f, g);

    r2=100;
    printf("f = %d, g = %d.\n", f, g);

// References as arguments
    BigData data;
    Increase(data);
    Print(data);

    return 0;
}
