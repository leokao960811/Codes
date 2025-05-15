#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Card.h"

void RandInit(Card *c)
{
    int randvalue=rand()%13+1;
    c->value=randvalue;
    c->state=Card::State::FaceDown;
}

void Print(Card c)
{
    if(c.state==Card::State::Removed)
    {
        printf(" ");
    }
    else if(c.state==Card::State::FaceUp)
    {
        switch (c.value)
        {
        case 1:
            printf("A");
            break;
        case 11:
            printf("J");
            break;
        case 12:
            printf("Q");
            break;
        case 13:
            printf("K");
            break;
        default:
            printf("%d",c.value);
            break;
        }
    }
    else
    {
        printf("#");
    }
}

bool FlipUp(Card *c)
{
    if(c->state==Card::State::Removed || c->state==Card::State::FaceUp)
    {
        return false;
    }
    else
    {
        c->state=Card::State::FaceUp;
        return true;
    }
}

bool FlipDown(Card *c)
{
    if(c->state==Card::State::Removed || c->state==Card::State::FaceDown)
    {
        return false;
    }
    else
    {
        c->state=Card::State::FaceDown;
        return true;
    }

}

bool isRemoved(Card c)
{
    if(c.state==Card::State::Removed)
    {
        return true;
    }

    return false;
}

bool Remove(Card *c)
{
    if(c->state==Card::State::Removed)
    {
        return false;
    }
    else
    {
        c->state=Card::State::Removed;
        return true;
    }

}

bool isMatched(Card c1, Card c2)
{
    if(c1.value==c2.value)
    {
        return true;
    }

    return false;
}
