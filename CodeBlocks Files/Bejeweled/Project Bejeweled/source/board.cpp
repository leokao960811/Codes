#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.h>
#include "Structs.h"
#include "detection.h"
#include "destruction.h"
#include "specialgems.h"
#include "board.h"

void Swap(Gem board[][8], Move mv, int *mflag)
{
    if ((toupper(mv.col) - 'A' > 7) || ((mv.row < 1) || (mv.row > 8)) ||
            ((toupper(mv.dir) != 'U') && (toupper(mv.dir) != 'D') &&
             (toupper(mv.dir) != 'L') && (toupper(mv.dir) != 'R')))
    {
        (*mflag) = 1;
        return;
    }
    else if ((toupper(mv.col) == 'A' && toupper(mv.dir) == 'L') ||
             (toupper(mv.col) == 'H' && toupper(mv.dir) == 'R') ||
             (mv.row == 1 && toupper(mv.dir) == 'U') ||
             (mv.row == 8 && toupper(mv.dir) == 'D'))
    {
        (*mflag) = 2;
        return;
    }
    else
    {
        int row0 = mv.row - 1;
        int col0 = toupper(mv.col) - 'A';
        int row1 = row0, col1 = col0;
        switch(toupper(mv.dir))
        {
        case 'U':
            row1 = row0 - 1;
            break;
        case 'D':
            row1 = row0 + 1;
            break;
        case 'L':
            col1 = col0 - 1;
            break;
        case 'R':
            col1 = col0 + 1;
            break;
        }
        // Perform swap.
        Gem temp = board[row0][col0];
        board[row0][col0] = board[row1][col1];
        board[row1][col1] = temp;


        // Check for wildcard involvement.
        bool wildcard0 = (board[row0][col0].type == 3);
        bool wildcard1 = (board[row1][col1].type == 3);
        if (wildcard0 || wildcard1)
        {
            if (wildcard0 && wildcard1)
            {
                for (int i = 0; i < NUM_ROWS; i++)
                    for (int j = 0; j < NUM_COLS; j++)
                        board[i][j].destroy = 2;
            }
            else
            {
                char targetColor = wildcard0 ? board[row1][col1].color : board[row0][col0].color;
                if (targetColor == 'H')
                    targetColor = 'H';
                if (wildcard0)
                    triggerHypercube(board, row0, col0, targetColor);
                else
                    triggerHypercube(board, row1, col1, targetColor);
            }
            *mflag = 3; // Flag indicating Hypercube swap triggered.
        }
        else
        {
            *mflag = 0;
        }
    }
}


int randint(int n)
{
    if ((n - 1) == RAND_MAX)
        return rand();
    else
    {
        long end = RAND_MAX / n;
        assert(end > 0L);
        end *= n;
        int r;
        while ((r = rand()) >= end);
        return r % n;
    }
}

void FillBoard(Gem board[][8], const int r, const int c)
{
    int checkc = 0;
    Gem temp = {};
    for (int i = c - 1; i >= 0; i--)
    {
        for (int j = 0; j < r; j++)
        {
            if (board[i][j].color == ' ')
            {
                checkc = i;
                while (checkc >= 0 && board[checkc][j].color == ' ')
                    checkc--;
                if (checkc < 0)
                {
                    board[i][j].color = (randint(7) + 1) + '0';
                    board[i][j].type = 0;
                    board[i][j].destroy = 0;
                }
                else
                {
                    temp = board[i][j];
                    board[i][j] = board[checkc][j];
                    board[checkc][j] = temp;
                }
            }
        }
    }
}

void FillBoardEndless(Gem board[][8], const int r, const int c)
{
    int checkc = 0;
    Gem temp = {};
    int dropboard[8][8]= {0};

    for (int i = c - 1; i >= 0; i--)
    {
        for (int j = 0; j < r; j++)
        {
            if (board[i][j].color == ' ')
            {
                checkc = i;
                while (checkc >= 0 && board[checkc][j].color == ' ')
                    checkc--;
                if (checkc < 0)
                {
                    dropboard[i][j]=1;
                    // Generate a random gem
                    char newColor = (randint(7) + 1) + '0';

                    // Ensure that it creates a match if necessary

                    // Place the adjusted gem
                    board[i][j].color = newColor;
                    board[i][j].type = 0;
                    board[i][j].destroy = 0;
                }
                else
                {
                    temp = board[i][j];
                    board[i][j] = board[checkc][j];
                    board[checkc][j] = temp;
                }


            }
        }
        ensureMatch(board, dropboard);
    }
}

void FillBoardLT(Gem board[][8], const int r, const int c, int multi)
{
    bool movedroped=false;
    int checkc = 0;
    int chance = 340;
    int typechance= 230;
    Gem temp = {};
    int dropboard[8][8]= {0};

    if(chance-(40*multi)<80)
    {
        chance=80;
    }
    else
    {
        chance-=(40*multi);
    }

    if(typechance-(30*multi)<20)
    {
        typechance=20;
    }
    else
    {
        typechance-=(30*multi);
    }


    for (int i = c - 1; i >= 0; i--)
    {
        for (int j = 0; j < r; j++)
        {
            if (board[i][j].color == ' ')
            {
                checkc = i;
                while (checkc >= 0 && board[checkc][j].color == ' ')
                    checkc--;
                if (checkc < 0)
                {
                    dropboard[i][j]=1;
                    // Generate a random gem
                    char newColor = (randint(7) + 1) + '0';
                    int rng=randint(1000);

                    // Place the adjusted gem
                    board[i][j].color = newColor;
                    if(rng<chance && movedroped==false)
                    {
                        if(rng<typechance)
                        {
                            board[i][j].type=6;
                            movedroped=true;
                        }
                        else
                        {
                            board[i][j].type=5;
                            movedroped=true;
                        }
                    }
                    else
                    {
                        board[i][j].type = 0;
                    }

                    board[i][j].destroy = 0;
                }
                else
                {
                    temp = board[i][j];
                    board[i][j] = board[checkc][j];
                    board[checkc][j] = temp;
                }


            }
        }
        ensureMatch(board, dropboard);
    }
}

void ensureMatch(Gem board[][8], int dropboard[][8])
{
    if (possibleMoveExists(board))
        return; // Early exit if a move already exists

    int tries = 0;
    while (tries < 100) // Avoid infinite loop
    {
        int Rrow = randint(8);
        int Rcol = randint(8);

        if (dropboard[Rrow][Rcol] != 1)
        {
            tries++;
            continue;
        }

        // Choose a color from a neighbor to try creating a potential match
        int colorOptions[4];
        int count = 0;

        // Gather neighbor colors
        if (Rrow > 0) colorOptions[count++] = board[Rrow - 1][Rcol].color;
        if (Rrow < 7) colorOptions[count++] = board[Rrow + 1][Rcol].color;
        if (Rcol > 0) colorOptions[count++] = board[Rrow][Rcol - 1].color;
        if (Rcol < 7) colorOptions[count++] = board[Rrow][Rcol + 1].color;

        for (int i = 0; i < count; i++)
        {
            int tryColor = colorOptions[i];
            board[Rrow][Rcol].color = tryColor;

            if (possibleMoveExists(board)) // See if this color enables a move
                return; // Success
        }

        tries++;
    }

    int flag=0;
    while (flag==0)
    {
        int Rcol=randint(8);
        int Rrow=randint(8);

        // Try adjusting the gem to match its neighbors
        if (dropboard[Rrow][Rcol]==1 && Rcol >= 2 && board[Rrow][Rcol - 1].color == board[Rrow][Rcol - 2].color)
        {
            board[Rrow][Rcol].color = board[Rrow][Rcol - 1].color; // Create a horizontal match
            flag=1;
        }
        else if (dropboard[Rrow][Rcol]==1 && Rrow >= 2 && board[Rrow - 1][Rcol].color == board[Rrow - 2][Rcol].color)
        {
            board[Rrow][Rcol].color = board[Rrow - 1][Rcol].color; // Create a vertical match
            flag=1;
        }
    }
}


void BoardDisplay(Gem board[][8], const int r, const int c)
{
    system("cls");
    printf("  ABCDEFGH\n");
    for (int i = 0; i < c; i++)
    {
        printf("%d ", i + 1);
        for (int j = 0; j < r; j++)
        {
            switch(board[i][j].type)
            {
            case 6:
                printf("\e[38;2;255;208;0m");
                break;
            case 5:
                printf("\e[38;2;190;160;0m");
                break;
            case 4:
                printf("\e[38;2;255;255;255m");
                break;
            case 3:
                board[i][j].color='H';
                printf("\e[38;2;80;80;80m");
                break;
            case 2:
                printf("\e[38;2;0;203;255m");
                break;
            case 1:
                printf("\e[38;2;255;173;0m");
                break;
            default:
                printf("\x1b[0m");
                break;
            }
            switch(board[i][j].color-'0')
            {
            case 1:
                printf("\x1b[41m");
                break;
            case 2:
                printf("\x1b[48;2;255;255;255m");
                break;
            case 3:
                printf("\x1b[42m");
                break;
            case 4:
                printf("\x1b[43m");
                break;
            case 5:
                printf("\x1b[45m");
                break;
            case 6:
                printf("\x1b[48;2;255;93;0m");
                break;
            case 7:
                printf("\x1b[44m");
                break;
            default:
                printf("\x1b[0m");
                break;
            }
            printf("%c", board[i][j].color);
            printf("\x1b[0m");
        }
        printf("\x1b[0m\n");
    }
}

void BoardInit(Gem board[][8], const int r, const int c, Move input)
{
    // Initialize board.
    for (int i = 0; i < c; i++)
    {
        for (int j = 0; j < r; j++)
        {
            board[i][j].color = (randint(7) + 1) + '0';
        }
    }

    while (detectAndMarkMatches(board, input))
    {
        destroyGems(board);
        FillBoardEndless(board, r, c);
    }

    for (int i = 0; i < c; i++)
    {
        for (int j = 0; j < r; j++)
        {
            if(board[i][j].type==3)
            {
                board[i][j].color=(randint(7) + 1) + '0';
            }
            board[i][j].type = 0;
        }
    }

    BoardDisplay(board, r, c);
}

void BoardCycle(Gem board[][8], const int r, const int c, const int mode)
{
    destroyGems(board);
    Sleep(250);
    BoardDisplay(board, r, c);
    Sleep(250);
    if(mode==1)
    {
        FillBoard(board, r, c);
    }
    else if (mode>1)
    {
        FillBoardEndless(board, r, c);
    }
    Sleep(250);
}

void BoardCyclePT(Gem board[][8], const int r, const int c, const int mode, int *score, int *scoreflag)
{
    destroyGemsPT(board, score, scoreflag);
    Sleep(250);
    BoardDisplay(board, r, c);
    Sleep(250);
    if(mode==1)
    {
        FillBoard(board, r, c);
    }
    else if (mode>1)
    {
        FillBoardEndless(board, r, c);
    }
    Sleep(250);
}

void BoardCycleLT(Gem board[][8], const int r, const int c, const int mode, int *score, int *scoreflag, int moves, int multi, int *banked)
{
    if(mode==3)
    {
        destroyGemsLT(board, score, scoreflag, multi, banked);
    }
    else
    {
        destroyGemsPT(board, score, scoreflag);
    }
    Sleep(250);
    BoardDisplay(board, r, c);
    Sleep(250);
    if(mode==1)
    {
        FillBoard(board, r, c);
    }
    else if (mode>1)
    {
        if(mode==3 && (moves>0 && banked>0))
        {
            FillBoardLT(board, r, c, multi);
        }
        else
        {
            FillBoardEndless(board, r, c);
        }
    }
    Sleep(250);
}
