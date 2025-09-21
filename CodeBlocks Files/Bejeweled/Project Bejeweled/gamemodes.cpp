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
#include "poker.h"


void Classic(Gem board[][8], Move input, const int r, const int c, const int mode, int *score, int *scoreflag, int *matchflag)
{
    BoardInit(board, r, c, input);

    while (possibleMoveExists(board))
    {
        printf("\nScore: %d\n", *score);
        printf("Input Column(A-H), Row(1,8), Direction(U, D, L, R): ");
        scanf(" %c %d  %c", &input.col, &input.row, &input.dir);

        Swap(board, input, matchflag);
        BoardDisplay(board, r, c);
        // If no match is detected and no Hypercube was involved, revert move.
        if ((*matchflag) != 3 && !detectAndMarkMatches(board, input))
        {
            BoardDisplay(board, r, c);
            Sleep(250);
            Swap(board, input, matchflag); // revert move
        }
        else
        {
            *scoreflag=1;

            if((*matchflag)==3)
            {
                BoardCyclePT(board, r, c, mode, score, scoreflag);
            }

            while (detectAndMarkMatches(board, input))
            {
                BoardDisplay(board, r, c);
                Sleep(250);
                BoardCyclePT(board, r, c, mode, score, scoreflag);
            }
        }
        BoardDisplay(board, r, c);
        Sleep(250);

        if ((*matchflag) > 0 && (*matchflag) != 3)
        {
            if ((*matchflag) == 1)
                printf("Move not recognized.\n");
            else
                printf("Invalid move.\n");
        }
    }
    printf("No moves left.\n");
    printf("Final Score: %d", *score);


}

void Endless(Gem board[][8], Move input, const int r, const int c, const int mode, int *score, int *scoreflag, int *matchflag)
{
    BoardInit(board, r, c, input);

    while (possibleMoveExists(board))
    {
        printf("\nScore: %d\n", *score);
        printf("Input Column(A-H), Row(1,8), Direction(U, D, L, R): ");
        scanf(" %c %d  %c", &input.col, &input.row, &input.dir);

        Swap(board, input, matchflag);
        BoardDisplay(board, r, c);
        // If no match is detected and no Hypercube was involved, revert move.
        if ((*matchflag) != 3 && !detectAndMarkMatches(board, input))
        {
            BoardDisplay(board, r, c);
            Sleep(250);
            Swap(board, input, matchflag); // revert move
        }
        else
        {
            *scoreflag=1;

            if((*matchflag)==3)
            {
                BoardCyclePT(board, r, c, mode, score, scoreflag);
            }

            while (detectAndMarkMatches(board, input))
            {
                BoardDisplay(board, r, c);
                Sleep(250);
                BoardCyclePT(board, r, c, mode, score, scoreflag);
            }
        }
        BoardDisplay(board, r, c);
        Sleep(250);

        if ((*matchflag) > 0 && (*matchflag) != 3)
        {
            if ((*matchflag) == 1)
                printf("Move not recognized.\n");
            else
                printf("Invalid move.\n");
        }
    }

    //printf("No moves left.\n");
    //printf("Final Score: %d", score);
}

void Stratamax(Gem board[][8], Move input, const int r, const int c, const int mode, int *score, int *scoreflag, int *matchflag)
{
    int moves=30;
    int banked=0;
    int multi=1;

    BoardInit(board, r, c, input);

    //Main game loop.
    while (moves>0 || banked>0)
    {
        printf("\nScore: %d\n", *score);
        printf("Moves left: %d, Banked Moves: %d, Multiplier: x%d\n", moves, banked, multi);
        printf("Input Column(A-H), Row(1,8), Direction(U, D, L, R): ");
        scanf(" %c %d  %c", &input.col, &input.row, &input.dir);
        Swap(board, input, matchflag);
        BoardDisplay(board, r, c);
        // If no match is detected and no Hypercube was involved, revert move.
        if ((*matchflag) != 3 && !detectAndMarkMatches(board, input))
        {
            BoardDisplay(board, r, c);
            Sleep(250);
            Swap(board, input, matchflag); // revert move
        }
        else
        {
            (*scoreflag)=1;

            if((*matchflag)==3)
            {
                BoardCycleLT(board, r, c, mode, score, scoreflag, moves, multi, &banked);
            }

            while (detectAndMarkMatches(board, input))
            {
                BoardDisplay(board, r, c);
                Sleep(250);
                BoardCycleLT(board, r, c, mode, score, scoreflag, moves, multi, &banked);
            }
            moves-=1;
        }
        BoardDisplay(board, r, c);
        Sleep(250);

        if ((*matchflag) > 0 && (*matchflag) != 3)
        {
            if ((*matchflag) == 1)
                printf("Move not recognized.\n");
            else
                printf("Invalid move.\n");
        }

        if(moves==0)
        {
            moves=banked;
            banked=0;
            multi+=1;

            for (int r=0; r<NUM_ROWS; r+=1)
            {
                for(int c=0; c<NUM_COLS; c+=1)
                {
                    if(board[r][c].type>4)
                    {
                        board[r][c].type-=4;
                    }
                }
            }
            BoardDisplay(board, r, c);
        }
    }

    while(hasSpecial(board,r,c) || detectAndMarkMatches(board, input))
    {
        for (int i = 0; i < NUM_ROWS; i++) //h,i
        {
            for (int j = 0; j < NUM_COLS; j++) //v,j
            {
                if (board[i][j].type == 1)
                    explodeFlame(board, i, j);
                if (board[i][j].type == 2)
                    explodeLightning(board, i, j);
                if (board[i][j].type == 3)
                    triggerHypercube(board, i, j, board[i-1][j].color);
                if (board[i][j].type == 4)
                    explodeSupernova(board, i, j);
            }
        }
        BoardDisplay(board,r,c);
        BoardCycleLT(board, r, c, mode, score, scoreflag, moves, multi, &banked);

    }

    BoardDisplay(board,r,c);
    printf("No moves left.\n");
    printf("Final Score: %d", *score);

}

void Poker(Gem board[][8], Move input, const int r, const int c, const int mode, int *score, int *scoreflag, int *matchflag)
{
    int skull=7;
    int lives=3;

    Gem hand[2][5] = {};
    int mvcnt=0;
    bool cascade = false;
    int gemcnt[8] = {};
    int handcount=0;

    int charge=0;
    int same_gem=0;
    bool FullHouse=false;
    bool TwoPair=false;

    int scores[2][7]= {{500,300,150,100,75,50,25},{1,1,1,1,1,1,1}};

    BoardInitPK(board, r, c, input, mode, hand, mvcnt, cascade);
    for(int i=0; i<5; i+=1)
    {
        for (int j=0; j<2; j+=1)
        {
            hand[j][i].color=' ';
            hand[j][i].type=' ';
        }
    }

    HandDisplay(hand,2,5);

//    board[0][0].color='1';
//    board[0][1].color='1';
//    board[1][2].color='1';
//    board[1][0].color='2';
//    board[1][1].color='2';
//    board[0][2].color='2';

    BoardDisplay(board, r, c);

    //Main game loop.
    while (lives>0)
    {
        for(int i=0; i<7; i+=1)
        {
            if(i>=skull)
            {
                scores[1][i]=0;
            }
        }

        printf("Hand List:\n"
               "Flush|4 of a Kind|Full House|3 of a Kind|Two Pair|Spectrum|Pair\n"
               " %d |    %d    |   %d    |    %d    |   %d   |   %d   | %d  \n",
               scores[0][0],
               skull<2? scores[1][1]:scores[0][1],
               skull<3? scores[1][2]:scores[0][2],
               skull<4? scores[1][3]:scores[0][3],
               skull<5? scores[1][4]:scores[0][4],
               skull<6? scores[1][5]:scores[0][5],
               skull<7? scores[1][6]:scores[0][6]);

        if(skull<7)
        {
            printf("Zero Eliminator Progess:\n"
                   "|");
            for(int i=0; i<500; i+=25)
            {
                if(i<charge)
                {
                    printf("#");
                }
                else
                {
                    printf(" ");
                }
            }
            printf("|\n");
        }

        printf("\nScore: %d, Lives: %d\n", *score, lives);
        //printf("%d\n", mvcnt);
        printf("Input Column(A-H), Row(1,8), Direction(U, D, L, R): ");
        scanf(" %c %d  %c", &input.col, &input.row, &input.dir);
        SwapPK(board, input, matchflag, mode, hand, mvcnt, cascade);
        BoardDisplay(board, r, c);
        HandDisplay(hand,2,5);

        cascade = false;

        // If no match is detected and no Hypercube was involved, revert move.
        if ((*matchflag) != 3 && !detectAndMarkMatchesPK(board, input, mode, hand, mvcnt, cascade))
        {
            BoardDisplay(board, r, c);
            Sleep(500);
            SwapPK(board, input, matchflag, mode, hand, mvcnt, cascade); // revert move
        }
        else
        {
            cascade=true;
            if((*matchflag)==3)
            {
                BoardCycle(board, r, c, mode);
            }

            while (detectAndMarkMatchesPK(board, input, mode, hand, mvcnt, cascade))
            {

                BoardDisplay(board, r, c);
                Sleep(500);
                BoardCycle(board, r, c, mode);
            }

            mvcnt+=1;

        }

        bool wild=false;

        if(mvcnt==5)
        {
            for(int i=0; i<2; i+=1)
            {
                for(int j=0; j<5; j+=1)
                {
                    if(hand[i][j].color=='H')
                    {
                        wild=true;
                    }
                    else if(isdigit(hand[i][j].color) && hand[i][j].color-'0'>0 && hand[i][j].color-'0'<8)
                    {
                        gemcnt[hand[i][j].color-'0']+=1;
                    }
                }
            }
        }

        if(wild==true)
        {
            int l_ind=1;
            for(int i=2; i<8; i+=1)
            {
                if(gemcnt[l_ind]<gemcnt[i])
                {
                    l_ind=i;
                }
            }
            gemcnt[l_ind]+=1;
        }

        for(int i=1; i<8; i+=1)
        {
            if(same_gem<gemcnt[i])
            {
                same_gem=gemcnt[i];
            }
        }

        BoardDisplay(board, r, c);
        Sleep(500);
        HandDisplay(hand,2,5);

        if ((*matchflag) > 0 && (*matchflag) != 3)
        {
            if ((*matchflag) == 1)
                printf("Move not recognized.\n");
            else
                printf("Invalid move.\n");
        }

        if(mvcnt==5)
        {
            int skullrand=randint(100);
            int bonus=0;

            for(int i=0; i<5; i+=1)
            {
                if(hand[0][i].type>0)
                {
                    if(hand[0][i].type==3)
                    {
                        continue;
                    }
                    else
                    {
                        switch (hand[0][i].type)
                        {
                        case 1:
                            bonus+=5;
                            break;
                        case 2:
                            bonus+=10;
                            break;
                        }
                    }
                }
                else if(hand[1][i].type>0)
                {
                    if(hand[1][i].type==3)
                    {
                        continue;
                    }
                    else
                    {
                        switch (hand[1][i].type)
                        {
                        case 1:
                            bonus+=5;
                            break;
                        case 2:
                            bonus+=10;
                            break;
                        }
                    }
                }
            }

            if(same_gem==5)
            {
                printf("Made Hand: Flush, Bonus: %d\n", bonus);
                (*score)+=scores[0][0]+bonus;
                if(skull<7)
                {
                    charge+=scores[0][0];
                }
            }
            else if(same_gem==4)
            {
                printf("Made Hand: 4 of a kind, Bonus: %d\n", bonus);
                if(scores[1][1]!=0)
                {
                    (*score)+=scores[0][1]+bonus;
                    if(skull<7)
                    {
                        charge+=scores[0][1];
                    }
                }
                else
                {
                    printf("Hand isn't allowed! -1HP\n");
                    lives-=1;
                }

                if(skullrand<10 || handcount>45)
                {
                    if(skull>0)
                    {
                        skull-=1;
                    }
                }

            }
            else if(same_gem==3)
            {
                int index=0;
                for(int i=1; i<8; i+=1)
                {
                    if (gemcnt[i]==3)
                    {
                        index=i;
                    }
                }

                for(int i=1; i<8; i+=1)
                {
                    if (gemcnt[i]>=2 && i!=index)
                        FullHouse=true;
                }

                if(FullHouse==true)
                {
                    printf("Made Hand: Full House, Bonus: %d\n", bonus);
                    if(scores[1][2]!=0)
                    {
                        (*score)+=scores[0][2]+bonus;
                        if(skull<7)
                        {
                            charge+=scores[0][2];
                        }
                    }
                    else
                    {
                        printf("Hand isn't allowed! -1HP\n");
                        lives-=1;
                    }

                    if(skullrand<20 || handcount>20)
                    {
                        if(skull>0)
                        {
                            skull-=1;
                        }
                    }
                }
                else
                {
                    printf("Made Hand: 3 of a kind, Bonus: %d\n", bonus);
                    if(scores[1][3]!=0)
                    {
                        (*score)+=scores[0][3]+bonus;
                        if(skull<7)
                        {
                            charge+=scores[0][3];
                        }
                    }
                    else
                    {
                        printf("Hand isn't allowed! -1HP\n");
                        lives-=1;
                    }

                    if(skullrand<25 || handcount>15)
                    {
                        if(skull>0)
                        {
                            skull-=1;
                        }
                    }
                }
            }
            else if(same_gem==2)
            {
                int index=0;
                for(int i=1; i<8; i+=1)
                {
                    if(gemcnt[i]==2)
                    {
                        index=i;
                    }
                }

                for(int i=1; i<8; i+=1)
                {
                    if(gemcnt[i]>=2 && i!=index)
                    {
                        TwoPair=true;
                    }
                }

                if(TwoPair==true)
                {
                    printf("Made Hand: 2 Pair, Bonus: %d\n", bonus);
                    if(scores[1][4]!=0)
                    {
                        (*score)+=scores[0][4]+bonus;
                        if(skull<7)
                        {
                            charge+=scores[0][4];
                        }
                    }
                    else
                    {
                        printf("Hand isn't allowed! -1HP\n");
                        lives-=1;
                    }

                    if(skullrand<30 || handcount>10)
                    {
                        if(skull>0)
                        {
                            skull-=1;
                        }
                    }
                }
                else
                {
                    printf("Made Hand: Pair, Bonus: %d\n", bonus);
                    if(scores[1][6]!=0)
                    {
                        (*score)+=scores[0][6]+bonus;
                        if(skull<7)
                        {
                            charge+=scores[0][6];
                        }
                    }
                    else
                    {
                        printf("Hand isn't allowed! -1HP\n");
                        lives-=1;
                    }

                    if(skullrand<50 || handcount>6)
                    {
                        if(skull>0)
                        {
                            skull-=1;
                        }
                    }
                }
            }
            else if(same_gem==1)
            {
                printf("Made Hand: Spectrum, Bonus: %d\n", bonus);
                if(scores[1][5]!=0)
                {
                    (*score)+=scores[0][5]+bonus;
                    if(skull<7)
                    {
                        charge+=scores[0][5];
                    }
                }
                else
                {
                    printf("Hand isn't allowed! -1HP\n");
                    lives-=1;
                }

                if(skullrand<45 || handcount>5)
                {
                    if(skull>0)
                    {
                        skull-=1;
                    }
                }
            }

            if(charge>=500)
            {
                skull+=1;
                charge=0;
            }

            handcount+=1;
            if(mvcnt>=5)
            {
                mvcnt=0;
                for(int i=0; i<5; i+=1)
                {
                    for (int j=0; j<2; j+=1)
                    {
                        hand[j][i].color=' ';
                        hand[j][i].type=' ';
                    }
                }

                for(int i=1; i<8; i+=1)
                {
                    gemcnt[i]=0;
                }

                same_gem=0;
                FullHouse=false;
                TwoPair=false;
            }
        }
    }

    BoardDisplay(board,r,c);

    printf("No lives left.\n");
    printf("Final Score: %d, Hands Made: %d", *score, handcount);
}
