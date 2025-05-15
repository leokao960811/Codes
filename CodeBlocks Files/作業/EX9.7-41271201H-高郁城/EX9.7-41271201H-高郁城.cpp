#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

struct oldEntity
{
    char name[31]= {};
    char role=' ';
    int stats[4]= {};
};

struct newEntity
{
    char name[31]= {};
    char role=' ';
    int stats[4]= {};
    double luck = 0.;
};

int main()
{
    FILE *fold = fopen("old.sav","rb");
    FILE *fnew = fopen("new.sav","wb");

    double hack = 99.9;

    if(fold != nullptr)
    {
        oldEntity pold;
        newEntity pnew;

        while(fread(&pold, sizeof(pold), 1, fold)==1)
        {
            strcpy(pnew.name, pold.name);

            int namelen=strlen(pnew.name);
            pnew.name[namelen - 1]='*';

            pnew.role = pold.role;

            for(int i=0;i<4;i+=1)
            {
                pnew.stats[i]=pold.stats[i];
            }

            pnew.luck=99.9;

            if(fnew!=nullptr)
            {
                fwrite(&pnew, sizeof(pnew), 1, fnew);
            }

        }

    }
    fclose(fold);
    fclose(fnew);
}
