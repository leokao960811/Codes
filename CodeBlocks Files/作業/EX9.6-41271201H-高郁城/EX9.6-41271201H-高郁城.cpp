#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

int main()
{


    int data[4]={};

    FILE *bin = fopen("save.bin", "rb");

    if(bin != nullptr)
    {
        //fwrite(&level, sizeof(level), 1, bin);
        //fwrite(perc, sizeof(perc[0]), 3, bin);
        fread(data, sizeof(data), 4, bin);
        printf("%d %d %d %d\n", data[0], data[1], data[2],data[3]);

    }

    fclose(bin);

    data[2]=10;

    FILE *change = fopen("save.bin", "wb");

    if(bin != nullptr)
    {
        fwrite(data, sizeof(data), 4, change);
        printf("%d %d %d %d\n", data[0], data[1], data[2],data[3]);
        fclose(change);
    }
    return 0;
}
