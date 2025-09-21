#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <windows.h>
#include <ctype.h>

#include "Structs.h"
#include "board.h"
#include "specialgems.h"
#include "detection.h"
#include "destruction.h"
#include "gamemodes.h"

int main()
{
    srand(time(NULL));
    Gem board[8][8] = {};
    Move input;
    const int c = 8, r = 8;
    int matchflag = 0;

    int score = 0;
    int scoreflag = 0;

    char modeinput = ' ';

    printf("Welcome to C++jeweled\n"
           "Choose a Gamemode:\n\n"
           "1) Classic: Play until no moves are possible.\n"
           "2) Endless: Endless matching to your leisure.\n"
           "3) Stratamax: Match gems, save moves, and go for a high score.\n"
           "4) Poker: Make poker hands by matching gems.\n"
           "...> ");
    scanf(" %c", &modeinput);

    while((modeinput-'0'<0) || (modeinput-'0'>4))
    {
        system("cls");
        printf("Welcome to C++jeweled\n"
               "Choose a Gamemode:\n\n"
               "1) Classic: Play until no moves are possible.\n"
               "2) Endless: Endless matching to your leisure.\n"
               "3) Stratamax: Match gems, save moves, and go for a high score.\n"
               "4) Poker: Make poker hands by matching gems.\n"
               "Input not recognized.\n"
               "...> ");
        scanf(" %c", &modeinput);
    }

    if(modeinput-'0'==1)
    {
        system("cls");
        Classic(board, input, r, c, modeinput-'0', &score, &scoreflag, &matchflag);
    }
    else if(modeinput-'0'==2)

    {
        system("cls");
        Endless(board, input, r, c, modeinput-'0', &score, &scoreflag, &matchflag);
    }
    else if(modeinput-'0'==3)
    {
        system("cls");
        Stratamax(board, input, r, c, modeinput-'0', &score, &scoreflag, &matchflag);
    }
    else if(modeinput-'0'==4)
    {
        system("cls");
        Poker(board, input, r, c, modeinput-'0', &score, &scoreflag, &matchflag);
    }

    return 0;
}

