#ifndef EVENT_H
#define EVENT_H

enum EventType {SellEvent, PurchaseEvent};

struct Event
{
    EventType type = SellEvent;
    int time = 0;
    char item[30] = {};
    int qty=0;
};

struct EventQueue
{
    Event *events=nullptr;
    int size=0;
    int capacity=0;
};

bool ReadSellEvents(FILE *fp, Event *ev);

bool Insert(EventQueue *evq, const Event &ev);
bool Pop(EventQueue *evq);
const Event *Top(const EventQueue *evq);
void Destroy(EventQueue *evq);

#endif // EVENT_H
