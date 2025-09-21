#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <new>
#include "inventory.h"

bool Read(FILE *fp, ItemInfo *item)
{
    if(fp==nullptr)
    {
        printf("Inventory File not read.");
        return false;
    }
    else
    {
        char name[30]= {};
        int order_time=0, qty=0, sold=0;
        if(fscanf(fp,"%s %d %d %d",name,&order_time,&qty,&sold)==4)
        {
            strcpy(item->name, name);
            item->order_time=order_time;
            item->qty=qty;
            item->sold=sold;
            return true;
        }
        else
        {
            return false;
        }
    }

}

ItemInfo *GetItemInfo(Inventory *inv, const char name[])
{
    for(int i=0; i<inv->size; i+=1)
    {
        if(strcmp(name, inv->items[i].name)==0)
        {
            //printf("Item Found.\n");
            return &inv->items[i];
        }

    }

    //printf("Item not found. Adding...\n");
    ItemInfo *add={};
    add->order_time=0;
    add->qty=0;
    add->sold=0;
    strcpy(add->name, name);

    inv->items[inv->size]=*add;
    inv->size+=1;

    return &inv->items[inv->size-1];

}
