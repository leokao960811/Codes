#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "Card.h"
#include "GameBoard.h"

int main()
{

    srand(time(NULL));
    GameBoard board;

    int nr=0, nc=0;
    printf("Input row and columns for the board: \n");
    scanf("%d%d", &nr, &nc);
    while (!Create(&board, nr, nc))
    {
        printf("Input row and columns for the board: \n");
        scanf("%d%d", &nr, &nc);
    }
    system("cls");

    Initialize(&board);

    Position pos1, pos2;

    int t=0;

    while(!isEmpty(&board))
    {
        t+=1;
        Print(&board);

        printf("Input 2 positions of cards:\n");
        scanf("%d %d %d %d",&pos1.r, &pos1.c, &pos2.r, &pos2.c);
        system("cls");

        if((pos1.r==pos2.r) && (pos1.c==pos2.c))
        {
            Print(&board);
            printf("Same Location.\n");

        }

        else if((pos1.r>board.rownum-1) || (pos2.r>board.rownum-1) || (pos1.c>board.colnum-1) || (pos2.c>board.colnum-1))
        {
            Print(&board);
            printf("Out of range.\n");

        }

        else
        {
            FlipUp(GetCard(&board, pos1));
            FlipUp(GetCard(&board, pos2));
            Print(&board);
            Sleep(500);

            if(isMatched(*GetCard(&board, pos1), *GetCard(&board, pos2)))
            {
                RemoveCard(&board,GetCard(&board, pos1));
                RemoveCard(&board,GetCard(&board, pos2));
            }
            else
            {
                FlipDown(GetCard(&board, pos1));
                FlipDown(GetCard(&board, pos2));
                Sleep(500);
            }
        }
        system("cls");
    }

    printf("Congratulations! You took %d rounds to finish the game.", t);
    Close(&board);
    return 0;
}
