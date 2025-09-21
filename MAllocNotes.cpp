#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

int main()
{

    if(true)
    {
        int size=0;
        printf("How many integers?...> ");
        scanf("%d",&size);

        int *data = (int*) malloc(sizeof(int)*size);
        //malloc returns void* type!

        //Change (int*) to the data type you wish to read
        //The size here refers to bytes!

        //The allocated data should be manually freed.


        if (data==nullptr) return 0;

        for (int i=0; i<size; i+=1)
        {
            data[i]= rand()%10;
        }

        for (int i=0; i<size; i+=1)
        {
            printf("%d ",data[i]);
        }

        //This is where the memory should be deallocated.
        //A good practice is to set the pointer to null, since the pointer's value can't be changed through free().

        free(data);
        data = nullptr;

        if(data) //This code is run if (data!=nullptr)!
        {
            for (int i=0; i<size; i+=1)
            {
                printf("%d ",data[i]);
            }
        }

        //Extra note: An unsuccessful fopen (i.e. file pointer == nullptr) can't be fclosed,
        //while an unsuccessful allocation can still be freed.
    }

    //Leaves block, memory should already be deallocated.
    //Otherwise, it causes a memory leak.

    return 0;
}
