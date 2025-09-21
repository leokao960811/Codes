#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <new>
#include "event.h"

bool ReadSellEvents(FILE *fp, Event *ev)
{
    if(fp==nullptr)
    {
        printf("Event File not read.");
        return false;
    }
    else
    {
        char item[30]= {};
        int time=0, qty=0;
        if(fscanf(fp,"%d %s %d", &time, item,&qty)==3)
        {
            strcpy(ev->item,item);
            ev->time=time;
            ev->qty=qty;
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool Insert(EventQueue *evq, const Event &ev)
{
    if(evq->size>=evq->capacity)
    {
        int newCapacity = (evq->capacity==0) ? 1 : evq->capacity*2;
        Event* newevq = new (std::nothrow) Event[newCapacity];

        if(newevq!=nullptr)
        {
            for(int i=0; i<evq->size; i+=1)
            {
                newevq[i]=evq->events[i];
            }

            delete [] evq->events;
            evq->events=newevq;
            evq->capacity=newCapacity;
        }
        else
        {
            return false;
        }
    }

    int index=0;

    if(evq->size>0)
    {
        for(int i=0; i<evq->size; i+=1)
        {
            if(ev.time > evq->events[i].time)
            {
                index=i+1;
            }
        }

        for(int i=evq->size; i>index; i-=1)
        {
            evq->events[i]=evq->events[i-1];
        }
    }

    evq->events[index]=ev;
    evq->size+=1;
    return true;
}

bool Pop(EventQueue *evq)
{
    if(evq->size<0)
    {
        return false;
    }

    for(int i=0; i<evq->size-1; i+=1)
    {

        evq->events[i]=evq->events[i+1];
    }
    evq->size-=1;
    return true;
}

const Event *Top(const EventQueue *evq)
{
    if(evq->size==0) return nullptr;
    else
    {
        return &evq->events[0];
    }
}

void Destroy(EventQueue *evq)
{
    delete [] evq->events;
    evq->events=nullptr;
    evq->size=0;
}
