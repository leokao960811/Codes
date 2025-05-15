#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <new> // for nothrow
#include "Card.h"
#include "GameBoard.h"

bool Create(GameBoard *board, int nr, int nc)
{
    if(nr*nc%2!=0) return false;

    board->rownum = board->colnum = 0;

    board->cards=new (std::nothrow) Card *[nr];
    if(board->cards==nullptr) return false;

    for(int r=0;r<nr;r+=1)
    {
        board->cards[r]=new (std::nothrow) Card [nc];
        if(board->cards[r]==nullptr)
        {
            //Delete the rows first, then the column pointers
            for(int rd=0;rd<r;rd+=1)
            {
                delete [] board->cards[rd];
            }
            delete [] board->cards;
            board->cards=nullptr;

            return false;
        }
    }

    board->rownum=nr;
    board->colnum=nc;

    board->cardnum=nr*nc;

    return true;
}

void Close (GameBoard *board)
{
    for(int rd=0;rd<(board->rownum);rd+=1)
    {
        delete [] board->cards[rd];
    }

    delete [] board->cards;
}

void Initialize(GameBoard *board)
{
    int num=0;
    Card temp;
    for(int r=0;r<board->rownum;r+=1)
    {
        for(int c=0;c<board->colnum;c+=1)
        {
            if(!(num%2))    RandInit(&temp);
            board->cards[r][c]=temp;
            num+=1;
        }
    }

    for(int r=0;r<board->rownum;r+=1)
    {
        for(int c=0;c<board->colnum;c+=1)
        {
            int rcol=rand()%board->colnum;
            int rrow=rand()%board->rownum;

            Card temp=board->cards[rrow][rcol];
            board->cards[rrow][rcol]=board->cards[r][c];
            board->cards[r][c]=temp;

        }
    }

}


void Print(const GameBoard *board)
{
    printf("  ");
    for(int c=0;c<board->colnum;c+=1)
    {
        printf("%d ",c);
    }
    printf("\n");

    for(int r=0;r<board->rownum;r+=1)
    {
        printf("%d ",r);
        for(int c=0;c<board->colnum;c+=1)
        {
            Print(board->cards[r][c]);
            printf(" ");
        }
        printf("\n");
    }
}

Card *GetCard(GameBoard *board, Position pos)
{
    if (pos.c<0 || pos.c>board->colnum || pos.r<0 || pos.r>board->rownum)
    {
        return nullptr;
    }

    return &board->cards[pos.r][pos.c];
}

bool RemoveCard(GameBoard *board, Card *card)
{
    if(Remove(card) && board->cardnum)
    {
        board->cardnum-=1;
        return true;
    }
    return false;
}

bool isEmpty(const GameBoard *board)
{
    if(!board->cardnum) return true;

    return false;
}
