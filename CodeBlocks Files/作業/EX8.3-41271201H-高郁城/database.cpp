#include <stdio.h>
#include <string.h>
#include "player.h"
#include "database.h"

bool Add(Database *db, Player p)
{

    if((db->size)>=1000)
    {
        return false;
    }
    else
    {
        db->pl[db->size]=p;
        db->size+=1;
        return true;
    }

}

void Output(const Database *db)
{
    if (db->size==0)
    {
        printf("\nDatabase is empty.\n\n");
    }
    else
    {
        printf("There are %d records: \n",db->size);
        for (int i=0; i<db->size; i+=1)
        {
            Output(db->pl[i]);
            printf("\n");
        }
        printf("\n");
    }
}

int Search(const Database *db, const char name[])
{
    int index=-1;
    for (int i=0; i<db->size; i+=1)
        {
            if(strcmp(db->pl[i].name, name) == 0)
            {
                index=i;
            }
        }
    return index;
}


bool Remove(Database *db, int ind)
{
    if(ind>=db->size || ind<0)
    {
        return false;
    }


    for (int i=ind; i<db->size-1; i+=1)
    {
        db->pl[i] = db->pl[i+1];

    }

    db->size-=1;

    return true;
}
