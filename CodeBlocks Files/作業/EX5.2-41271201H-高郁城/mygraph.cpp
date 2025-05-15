#include <stdio.h>

void DrawLine(int len)
{
    for (int i=0; i<len; i+=1)
    {
        printf("*");
    }
    printf("\n");
}

void DrawRectangle(int row, int col)
{
    for (int i=0; i<col; i+=1)
    {
        DrawLine(row);
    }
}

void DrawSquare(int len)
{
    DrawRectangle(len, len);
}
