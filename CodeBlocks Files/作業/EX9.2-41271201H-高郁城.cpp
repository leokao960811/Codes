#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

bool Encrypt(const char outfname[],const char infname[], int offset)
{
    FILE *infp = fopen(infname, "r"),
    *outfp = fopen(outfname, "w");

    if (infp == nullptr)
    {
        printf("Target File not found.");
        return false;
    }
//    else if (outfp==nullptr)
//    {
//        printf("Destination file not found.");
//        return false;
//    }

    while (!feof(infp))
    {
        char c='\0';
        while (fscanf(infp, "%c", &c)==1)
        {
          fprintf(outfp, "%c", c+offset);
        }
    }

    fclose(infp);
    fclose(outfp);

    return true;
}

void PrintUsage()
{
    printf("Usage:\n\n"
           "TextEditor -c src.txt dest.txt => copies src.txt to dest.txt\n"
           "TextEditor -e src.txt dest.txt => encrypts src.txt to dest.txt\n"
           "TextEditor -d src.txt dest.txt => decrypts src.txt to dest.txt\n");
}

int main(int argc, char *argv[])
{
    if(argc != 4) {PrintUsage(); return 0;}

    if(strcmp(argv[1],"-c") == 0)
    {
        if(Encrypt(argv[3], argv[2], 0))
        {
            printf("%s is copied to %s.\n", argv[2], argv[3]);
        }
    }
    else if(strcmp(argv[1], "-d") == 0)
    {
        if(Encrypt(argv[3], argv[2], -2))
        {
            printf("%s is decrypted to %s.\n", argv[2], argv[3]);
        }
    }
    else if(strcmp(argv[1], "-e") == 0)
    {
        if(Encrypt(argv[3], argv[2], 2))
        {
            printf("%s is encrypted to %s.\n", argv[2], argv[3]);
        }
    }
    else
    {
        PrintUsage();
    }
}
