#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <new> // for nothrow

//using namespace std; // if you want to just write nothrow instead of std::nothrow


bool Add (int **data, int *size, int val)
{
    //Add new array, data2
    int *data2 = new (std::nothrow) int[*size+1]{};

    if(data2!=nullptr)
    {
        //Copy the old data array
        for(int i=0; i<(*size); i+=1)
        {
            data2[i]=(*data)[i];
        }

        //Add the new value into data2
        data2[*size]=val;

        //Don't forget to delete!
        delete [] (*data);
        (*data) = data2;
        *size+=1;

        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    int *data = nullptr;
    int size=0, val=0;
    bool full = false;
    printf("Please input scores, -1 to end...> ");
    scanf("%d", &val);

    while(!full && val != -1)
    {
        if(!Add(&data,&size, val))
        {
            full=true;
        }

//        //Add new array, data2
//        int *data2 = new (std::nothrow) int[size+1]{};
//        if(data2==nullptr) {full=true;}
//        else
//        {
//            //Copy the old data array
//            for(int i=0; i<size; i+=1)
//            {
//                data2[i]=data[i];
//            }
//
//            //Add the new value into data2
//            data2[size]=val;
//            size+=1
//
//            //Don't forget to delete!
//            delete [] data;
//            data = data2;

            printf("Please input scores, -1 to end...> ");
            scanf("%d", &val);
 //       }
    }

    for (int i=0; i<size; i+=1)
    {
        printf("%d ", data[i]);
    }

    delete [] data;

    return 0;
}

