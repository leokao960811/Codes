#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <new>
#include "inventory.h"
#include "event.h"

int main(int argc, char *argv[])
{
    if(argc!=3)
    {
        printf("Usage: InvFile SellFile");
        return 0;
    }

    FILE *invfp=fopen(argv[1],"r");
    FILE *envfp=fopen(argv[2],"r");

//    FILE *invfp=fopen("inventory.txt","r");
//    FILE *envfp=fopen("sellevents.txt","r");

    Inventory inv;

    ItemInfo item= {};
    while(Read(invfp, &item))
    {
        strcpy(inv.items[inv.size].name,item.name);
        inv.items[inv.size].order_time=item.order_time;
        inv.items[inv.size].qty=item.qty;
        inv.items[inv.size].sold=item.sold;
        //printf("%s %d %d %d\n", inv.items[inv.size].name, inv.items[inv.size].order_time, inv.items[inv.size].qty, inv.items[inv.size].sold);
        inv.size+=1;
    }

//
//    for(int i=0;i<inv.size;i+=1)
//    {
//
//    }

//    ItemInfo item;
//    Read(invfp, &item);
//
    EventQueue evq = {};
    Event ev = {};
    while(ReadSellEvents(envfp, &ev))
    {
        Insert(&evq, ev);
    }

    int waiting=0;
    while(evq.size>0)
    {
        if(Top(&evq)->type==EventType::PurchaseEvent)
        {
            GetItemInfo(&inv, Top(&evq)->item)->qty+=Top(&evq)->qty;
            printf("%d [SUPPLY] %s %d (Inv: %d)\n", Top(&evq)->time, Top(&evq)->item, Top(&evq)->qty, GetItemInfo(&inv, Top(&evq)->item)->qty);
        }
        else if(Top(&evq)->type==EventType::SellEvent)
        {

            if(GetItemInfo(&inv, Top(&evq)->item)->qty>=Top(&evq)->qty)
            {
                GetItemInfo(&inv, Top(&evq)->item)->qty-=Top(&evq)->qty;
                GetItemInfo(&inv, Top(&evq)->item)->sold+=Top(&evq)->qty;
                printf("%d [SELL] %s %d (Inv: %d)\n", Top(&evq)->time, Top(&evq)->item, Top(&evq)->qty, GetItemInfo(&inv, Top(&evq)->item)->qty);
            }
            else
            {
                waiting=Top(&evq)->qty;

                Event supply = {};
                supply.type=PurchaseEvent;
                strcpy(supply.item,Top(&evq)->item);
                supply.time=Top(&evq)->time + GetItemInfo(&inv, Top(&evq)->item)->order_time;
                supply.qty=waiting-GetItemInfo(&inv, Top(&evq)->item)->qty;
                Insert(&evq, supply);

                printf("%d [BUY] %s %d (Customer: %d, Inv: %d)\n", Top(&evq)->time, Top(&evq)->item, waiting-GetItemInfo(&inv, Top(&evq)->item)->qty, waiting, GetItemInfo(&inv, Top(&evq)->item)->qty);
            }
        }

        Pop(&evq);
    }


    printf("\nFinal State:\n");
    for(int i=0;i<inv.size;i+=1)
    {
        printf("%s | Inv: %d | Sold: %d\n", inv.items[i].name, inv.items[i].qty, inv.items[i].sold);
    }


    Destroy(&evq);

    fclose(invfp);
    fclose(envfp);

//    Inventory inv;
//
//    printf("%d ",GetItemInfo(&inv,"AAA")->qty);
//    GetItemInfo(&inv,"AAA")->qty+=100;
//    GetItemInfo(&inv,"AAA")->qty+=150;
//    printf("%d ",GetItemInfo(&inv,"AAA")->qty);

    return 0;
}
