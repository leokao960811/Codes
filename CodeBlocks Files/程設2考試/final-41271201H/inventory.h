#ifndef INVENTORY_H
#define INVENTORY_H

struct ItemInfo
{
    char name[30]={};
    int order_time=0;
    int qty=0;
    int sold=0;
};

struct Inventory
{
    ItemInfo items[20]={};
    int size=0;
};

bool Read(FILE *fp, ItemInfo *item);

ItemInfo *GetItemInfo(Inventory *inv, const char name[]);

#endif // EVENT_H
