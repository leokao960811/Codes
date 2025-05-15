#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int main()
{
    FILE *fp1 = fopen("test.txt", "r");

    //checks EOF, returns true when end of file.
    //Can get screwed by extra newlines.
    while (!feof(fp1))
    {
//        int n=0;
//        while (fscanf(fp1, "%d", &n)==1)
//        {
//          printf("%d",n);
//        }

        char c='\0';
        while (fscanf(fp1, "%c", &c)==1)
        {
          printf("%c",c+2);
        }
    }

    fclose(fp1);

    return 0;
}
