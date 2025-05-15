#ifndef GAMEBOARD_H
#define GAMEBOARD_H

struct GameBoard
{
    // static data members are shared by all objects,
    // constexpr static data members can be initialized directly
    // static constexpr int MaxSize=8;
    // Card cards[MaxSize][MaxSize]={};
    Card **cards = nullptr;
    int rownum=0, colnum=0;

    int cardnum=0;
};

struct Position
{
    int r=0, c=0;
};

bool Create(GameBoard *board, int nr, int nc);
void Close(GameBoard *gb);
void Initialize(GameBoard *board);
void Print(const GameBoard *board);

Card *GetCard(GameBoard *board, Position pos);
bool RemoveCard(GameBoard *board, Card *card);
bool isEmpty(const GameBoard *board);
#endif
