#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>


int main()
{

    FILE *infp = fopen("message.txt", "r");
    char ans[100000]={};

    if(infp!= nullptr)
    {
        int ind=0;
        int characters=0;


        int size=0;
        fscanf(infp, "%d\n", &size);
        // '/n' can interfere with fgets!
        //This method only works with pure newlines.

        //Another way to deal with this is to
        //set a dummy string to store the line:
        //fgets(dummy, 100, infp)

        //malloc returns void* type!
        //(int*) is to change type
        //The size here refers to bytes!
        //Should be manually recycled.
        char *data = (char*) malloc(sizeof(char)*(size+1));
        fgets(data, size+1, infp); //Remember to +1!

        //printf("%d",size);
        //printf("%s", data);

        while (fscanf(infp, "%d", &ind)==1)
        {
            ans[characters]=data[ind];
            characters+=1;
        }

        //This is where the memory should be deallocated.
        free(data);
        data = nullptr;
    }

    //Leaves block, memory should already be deallocated.
    //Otherwise, it causes a memory leak.

    printf("%s",ans);
    fclose(infp);
    return 0;
}
