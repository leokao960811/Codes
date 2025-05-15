#ifndef CARD_H
#define CARD_H

struct Card
{
    // A scoped enumeration
    enum struct State{FaceDown, FaceUp, Removed};

    int value=-1;
    // Scoped enumeration, use '::' to specify the scope
    State state = State::FaceDown;
};

void RandInit(Card *c);
void Print(Card c);
bool FlipUp(Card *c);
bool FlipDown(Card *c);
bool isRemoved(Card c);
bool Remove(Card *c);
bool isMatched(Card c1, Card c2);

#endif
