#include <stdio.h>
#include <string.h>
#include <new.h>
#include "player.h"
#include "database.h"

// !!
bool Add(Database *db, Player *p)
{
    if(db->size>=db->capacity)
    {
        int newCapacity = (db->capacity == 0) ? 1 : db->capacity * 2;

        Player* newpl= new (std::nothrow) Player[newCapacity];

        if(newpl!= nullptr)
        {
            for (int i = 0; i < db->size; ++i)
            {
                newpl[i]=db->pl[i];
            }

            delete [] db->pl;
            db->pl=newpl;
            db->capacity=newCapacity;
        }
        else
        {
            return false;
        }
    }

    db->pl[db->size]= *p;
    db->size+=1;

    return true;
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

// !!
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

//copy(dest,origin)
bool Copy(Database *db2, const Database *db)
{
    delete[] db2->pl;

    db2->capacity = db->capacity;
    db2->size = db->size;
    db2->pl = new (std::nothrow) Player[db2->capacity];

    if(db2->pl!=nullptr)
    {
        for (int i = 0; i < db2->size; ++i)
        {
            db2->pl[i]=db->pl[i];
        }
        return true;
    }
    else
    {
        return false;
    }
}


void Close (Database *db)
{
    delete [] db->pl;
    db->pl=nullptr;
    db->size=0;

}

