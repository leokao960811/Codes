#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "Structs.h"
#include "detection.h"
#include "destruction.h"
#include "specialgems.h"
#include "board.h"
#include "poker.h"

void SwapPK(Gem board[][8], Move mv, int *mflag, int mode, Gem hand[][5], int mvcnt, bool cascade)
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
                    triggerHypercubePK(board, row0, col0, targetColor, mode, hand, mvcnt, cascade);
                else
                    triggerHypercubePK(board, row1, col1, targetColor, mode, hand, mvcnt, cascade);
            }
            *mflag = 3; // Flag indicating Hypercube swap triggered.
        }
        else
        {
            *mflag = 0;
        }
    }
}

void BoardInitPK(Gem board[][8], const int r, const int c, Move input, int mode, Gem hand[][5], int mvcnt, bool cascade)
{
    // Initialize board.
    for (int i = 0; i < c; i++)
    {
        for (int j = 0; j < r; j++)
        {
            board[i][j].color = (randint(7) + 1) + '0';
        }
    }

    while (detectAndMarkMatchesPK(board, input, mode, hand, mvcnt, cascade))
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

void HandDisplay(Gem hand[][5], const int r, const int c)
{
    printf("\nCurrent hand:\n");
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (hand[i][j].type==6)
            {
                printf("\e[48;2;255;208;0m");
            }
            else if (hand[i][j].type==5)
            {
                printf("\e[48;2;190;160;0m");
            }
            else if (hand[i][j].type == 4)
            {
                printf("\e[48;2;255;255;255m");
            }
            else if (hand[i][j].type == 3)
            {
                hand[i][j].color='H';
                printf("\e[48;2;80;80;80m");
            }
            else if (hand[i][j].type == 2)
            {
                printf("\e[48;2;0;203;255m");
            }
            else if (hand[i][j].type == 1)
            {
                printf("\e[48;2;255;121;2m");
            }
            else
            {
                printf("\e[48;2;0;0;0m");
            }
            printf("%c", hand[i][j].color);
            printf("\x1b[0m");
        }
        printf("\x1b[0m\n");
    }
}

// --- Match Detection and Marking ---
bool detectAndMarkMatchesPK(Gem board[][8], Move input, int mode, Gem hand[][5], int mvcnt, bool cascade)
{
    int horizRun[NUM_ROWS][NUM_COLS] = {0};
    int vertRun[NUM_ROWS][NUM_COLS] = {0};
    int markedGems[NUM_ROWS][NUM_COLS] = {0};

    bool foundMatch = false;
    // Compute horizontal runs.
    for (int i = 0; i < NUM_ROWS; i++)
    {
        horizRun[i][0] = 1;
        for (int j = 1; j < NUM_COLS; j++)
        {
            if (board[i][j].color != ' ' && board[i][j].color == board[i][j-1].color)
            {
                horizRun[i][j] = horizRun[i][j-1] + 1;
            }
            else
            {
                horizRun[i][j] = 1;
            }
        }
    }
    // Compute vertical runs.
    for (int j = 0; j < NUM_COLS; j++)
    {
        vertRun[0][j] = 1;
        for (int i = 1; i < NUM_ROWS; i++)
        {
            if (board[i][j].color != ' ' && board[i][j].color == board[i-1][j].color)
            {
                vertRun[i][j] = vertRun[i-1][j] + 1;
            }

            else
            {
                vertRun[i][j] = 1;
            }
        }
    }
    // Process horizontal matches.
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j < NUM_COLS; j++)
        {
            int count = horizRun[i][j];
            if (count >= 3)
            {
                if (j == NUM_COLS - 1 || board[i][j].color != board[i][j+1].color)
                {
                    int startCol = j - count + 1;
                    if (count == 4)
                    {
                        // Choose flame gem location:
                        int flamePos;
                        if (input.row >= 1 && input.col != ' ')
                        {
                            int swappedCol = toupper(input.col) - 'A';
                            if (swappedCol >= startCol && swappedCol <= j)
                                flamePos = swappedCol;
                            else
                                flamePos = (randint(2) == 0 ? startCol : j);
                        }
                        else
                        {
                            flamePos = (randint(2) == 0 ? startCol : j);
                        }
                        // If caused by swap, force explosion (destroy flag = 1)
                        for (int col = startCol; col <= j; col++)
                        {
                            if (col == flamePos)
                            {
                                board[i][col].type = 1; // Flame
                                markedGems[i][col]+=3;
                            }
                            else
                            {
                                markedGems[i][col]+=1;
                            }
                        }
                        if(mode==4)
                        {
                            if(cascade==false)
                            {
                                hand[0][mvcnt].type=1;
                            }
                        }
                    }

                    else if (count == 5)
                    {
                        // Create Hypercube at the third gem in the sequence.
                        for (int col = startCol; col <= j; col++)
                        {
                            if (col == startCol + 2)
                            {
                                board[i][col].type = 3; // Hypercube
                                markedGems[i][col]+=3;
                            }
                            else
                            {
                                markedGems[i][col]+=1;
                            }
                        }
                        if(mode==4)
                        {
                            if(cascade==false)
                            {
                                hand[0][mvcnt].type=3;
                            }
                        }
                    }


                    else if (count >= 6)
                    {
                        // 6-match creates a Supernova: choose the middle gem.
                        for (int col = startCol; col <= j; col++)
                        {
                            if (col == startCol+2)
                            {
                                board[i][col].type = 4; //Supernova
                                markedGems[i][col]+=3;
                            }
                            else
                            {
                                markedGems[i][col]+=1;
                            }
                        }
                    }
                    else
                    {
                        for (int col = startCol; col <= j; col++)
                            markedGems[i][col]+=1;
                    }

                    foundMatch = true;
                }

                if(mode==4)
                {
                    if(cascade==true)
                    {
                        continue;
                    }
                    else if(hand[0][mvcnt].color!=' ' && board[i][j].color != hand[0][mvcnt].color)
                    {
                        hand[1][mvcnt].color=board[i][j].color;
                    }
                    else
                    {
                        hand[0][mvcnt].color=board[i][j].color;
                    }
                }
            }
        }
    }
    // Process vertical matches.
    for (int j = 0; j < NUM_COLS; j++)
    {
        for (int i = 0; i < NUM_ROWS; i++)
        {
            int count = vertRun[i][j];
            if (count >= 3)
            {
                if (i == NUM_ROWS - 1 || board[i][j].color != board[i+1][j].color)
                {
                    int startRow = i - count + 1;
                    if (count == 4)
                    {
                        int flamePos;
                        if (input.row >= 1 && input.col != ' ')
                        {
                            int swappedRow = input.row - 1;
                            if (swappedRow >= startRow && swappedRow <= i)
                                flamePos = swappedRow;
                            else
                                flamePos = ((randint(2) == 0) ? startRow : i);
                        }
                        else
                        {
                            flamePos = (randint(2) == 0 ? startRow : i);
                        }
                        for (int row = startRow; row <= i; row++)
                        {
                            if (row == flamePos)
                            {
                                board[row][j].type = 1; // Flame
                                markedGems[row][j]+=3;
                            }
                            else
                            {
                                markedGems[row][j]+=1;
                            }
                        }
                        if(mode==4)
                        {
                            if(cascade==false)
                            {
                                hand[0][mvcnt].type=1;
                            }
                        }
                    }

                    else if (count == 5)
                    {
                        for (int row = startRow; row <= i; row++)
                        {
                            if (row == startRow+2)
                            {
                                board[row][j].type = 3; // Hypercube
                                markedGems[row][j]+=3;
                            }
                            else
                            {
                                markedGems[row][j]+=1;
                            }
                            if(mode==4)
                            {
                                if(cascade==false)
                                {
                                    hand[0][mvcnt].type=3;
                                }
                            }
                        }
                    }
                    else if (count >= 6)
                    {
                        for (int row = startRow; row <= i; row++)
                        {
                            if (row == startRow+2)
                            {
                                board[row][j].type = 4;
                                markedGems[row][j]+=3;
                            }
                            else
                            {
                                markedGems[row][j]+=1;
                            }
                        }
                    }

                    else
                    {
                        for (int row = startRow; row <= i; row++)
                        {
                            markedGems[row][j]+=1;
                        }
                    }

                    foundMatch = true;
                }
                if(mode==4)
                {
                    if(cascade==true)
                    {
                        continue;
                    }
                    else if(hand[0][mvcnt].color!=' ' && board[i][j].color != hand[0][mvcnt].color)
                    {
                        hand[1][mvcnt].color=board[i][j].color;
                    }
                    else
                    {
                        hand[0][mvcnt].color=board[i][j].color;
                    }
                }
            }
        }
    }

    //Special Intersection check
    int typecheck=0;
    for (int i = 0; i < NUM_ROWS; i+=1) //h,i
    {
        for (int j = 0; j < NUM_COLS; j+=1) //v,j
        {
            if (markedGems[i][j]==4)
            {
                for(int c=0; c<NUM_COLS; c+=1)
                {
                    if (horizRun[i][c]==4 && horizRun[i][c+1]!=5)
                        markedGems[i][j]-=2;
                    typecheck=1;
                }


                for(int r=0; r<NUM_ROWS; r+=1)
                {
                    if (vertRun[r][j]==4 && vertRun[r+1][j]!=5)
                        markedGems[i][j]-=2;
                    typecheck=2;
                }

                if(typecheck==1)
                {
                    if (horizRun[i][j]==2)
                    {
                        markedGems[i][j+1]+=2;
                        board[i][j+1].type = 1;
                    }
                    else if (horizRun[i][j]==3)
                    {
                        markedGems[i][j-1]+=2;
                        board[i][j-1].type = 1;
                    }
                }

                else if(typecheck==2)
                {
                    if (vertRun[i][j]==2)
                    {
                        markedGems[i+1][j]+=2;
                        board[i+1][j].type = 1;
                    }
                    else if (vertRun[i][j]==3)
                    {
                        markedGems[i-1][j]+=2;
                        board[i-1][j].type = 1;
                    }
                }
            }
        }
    }

    // Processing intersections for Lightning Gems
    for (int i = 0; i < NUM_ROWS; i++) //h,i
    {
        for (int j = 0; j < NUM_COLS; j++) //v,j
        {
            if (markedGems[i][j]==2)
            {
                board[i][j].type = 2;
                if(mode==4)
                {
                    if(cascade==false)
                    {
                        hand[0][mvcnt].color=board[i][j].color;
                        hand[0][mvcnt].type=2;
                    }

                }
            }
        }
    }


    //Check marked gems for destruction (Only marked with 1)
    for (int i = 0; i < NUM_ROWS; i++) //h,i
    {
        for (int j = 0; j < NUM_COLS; j++) //v,j
        {
            if(markedGems[i][j]==1)
            {
                board[i][j].destroy=1;
            }
        }
    }

    //Processing triggered special gems
    for (int i = 0; i < NUM_ROWS; i++) //h,i
    {
        for (int j = 0; j < NUM_COLS; j++) //v,j
        {
            if (board[i][j].type == 1 && board[i][j].destroy==1)
                explodeFlamePK(board, i, j, mode, hand, mvcnt, cascade);
            if (board[i][j].type == 2 && board[i][j].destroy==1)
                explodeLightningPK(board, i, j, mode, hand, mvcnt, cascade);
            if (board[i][j].type == 3 && board[i][j].destroy==1)
                triggerHypercubePK(board, i, j, mode, board[input.row-1][input.col-'A'].color, hand, mvcnt, cascade);

            if (board[i][j].type == 4 && board[i][j].destroy==1)
                explodeSupernovaPK(board, i, j, mode, hand, mvcnt, cascade);
        }
    }
    return foundMatch;
}

// --- Explosion Functions with Chain Reaction ---
// Explodes a Flame Gem (type 1) in a 3x3 area.
// Before marking a neighboring cell as destroyed, if it is a special gem (Flame or Lightning)
// and has not yet exploded, trigger its explosion.
void explodeFlamePK(Gem board[][8], int i, int j, int mode, Gem hand[][5], int mvcnt, bool cascade)
{
    if (i < 0 || i >= NUM_ROWS || j < 0 || j >= NUM_COLS)
        return;
    if (board[i][j].type != 1)
        return;
    if (board[i][j].destroy == 2)  // Already exploded
        return;
    board[i][j].destroy = 2; // Mark self as exploded
    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            int ni = i + di, nj = j + dj;
            if (ni >= 0 && ni < NUM_ROWS && nj >= 0 && nj < NUM_COLS)
            {
                // If neighbor is special and not yet exploded, trigger its explosion before marking.
                if ((board[ni][nj].type > 0) && board[ni][nj].destroy != 2)
                {
                    if (board[ni][nj].type == 1)
                        explodeFlamePK(board, ni, nj, mode, hand, mvcnt, cascade);
                    else if (board[ni][nj].type == 2)
                        explodeLightningPK(board, ni, nj, mode, hand, mvcnt, cascade);
                    else if (board[ni][nj].type == 3)
                        triggerHypercubePK(board, i, j, board[i][j].color, mode, hand, mvcnt, cascade);
                    else if (board[ni][nj].type == 4)
                        explodeSupernovaPK(board, ni, nj, mode, hand, mvcnt, cascade);
                }
                board[ni][nj].destroy = 2;
            }
        }
    }
}

//Deleting an entire row and column
void rowcolPK(Gem board[][8],int i, int j, int mode, Gem hand[][5], int mvcnt, bool cascade)
{
    // Process the entire row.
    for (int col = 0; col < NUM_COLS; col++)
    {
        if (col == j)
            continue;
        if ((board[i][col].type > 0) && board[i][col].destroy != 2)
        {
            if (board[i][col].type == 1)
                explodeFlamePK(board, i, col, mode, hand, mvcnt, cascade);
            else if (board[i][col].type == 2)
                explodeLightningPK(board, i, col, mode, hand, mvcnt, cascade);
            else if (board[i][col].type == 3)
                triggerHypercubePK(board, i, j, board[i][j].color, mode, hand, mvcnt, cascade);
            else if (board[i][col].type == 4)
                explodeSupernovaPK(board, i, col, mode, hand, mvcnt, cascade);
        }
        board[i][col].destroy = 2;
    }
    // Process the entire column.
    for (int row = 0; row < NUM_ROWS; row++)
    {
        if (row == i)
            continue;
        if ((board[row][j].type > 0) && board[row][j].destroy != 2)
        {
            if (board[row][j].type == 1)
                explodeFlamePK(board, row, j, mode, hand, mvcnt, cascade);
            else if (board[row][j].type == 2)
                explodeLightningPK(board, row, j, mode, hand, mvcnt, cascade);
            else if (board[row][j].type == 3)
                triggerHypercubePK(board, i, j, board[i][j].color, mode, hand, mvcnt, cascade);
            else if (board[row][j].type == 4)
                explodeSupernovaPK(board, row, j, mode, hand, mvcnt, cascade);
        }
        board[row][j].destroy = 2;
    }
}

// Explodes a Lightning Gem (type 2) by marking its entire row and column.
// For each cell in that row/column, if it is special and not yet exploded, trigger its explosion.
void explodeLightningPK(Gem board[][8], int i, int j, int mode, Gem hand[][5], int mvcnt, bool cascade)
{
    if (i < 0 || i >= NUM_ROWS || j < 0 || j >= NUM_COLS)
        return;
    if (board[i][j].type != 2)
        return;
    if (board[i][j].destroy == 2)
        return;
    board[i][j].destroy = 2;
    rowcolPK(board, i, j, mode, hand, mvcnt, cascade);
}

// The Hypercube explosion. When triggered (by a swap), it destroys
// all gems matching the target color. (If triggered by a special gem, targetColor
// is the special gem's color.) Hypercube also triggers chain reactions.
void triggerHypercubePK(Gem board[][8], int wi, int wj, char targetColor, int mode, Gem hand[][5], int mvcnt, bool cascade)
{
    // If this Hypercube is already exploded, return.
    if (board[wi][wj].destroy == 2)
        return;
    // Mark the triggering Hypercube as exploded.
    board[wi][wj].destroy = 2;

    if (targetColor == 'H')
    {
        // Two Hypercubes swapped: destroy the entire board.
        for (int i = 0; i < NUM_ROWS; i++)
        {
            for (int j = 0; j < NUM_COLS; j++)
            {
                if (board[i][j].destroy != 2)
                {
                    board[i][j].destroy = 2;
                    // If a special gem is encountered, trigger its explosion.
                    if (board[i][j].type == 1)
                        explodeFlamePK(board, i, j, mode, hand, mvcnt, cascade);
                    else if (board[i][j].type == 2)
                        explodeLightningPK(board, i, j, mode, hand, mvcnt, cascade);
                    else if (board[i][j].type == 3 && !(i == wi && j == wj))
                        triggerHypercubePK(board, i, j, mode, 'H', hand, mvcnt, cascade);
                    else if (board[i][j].type == 4)
                        explodeSupernovaPK(board, i, j, mode, hand, mvcnt, cascade);
                }
            }
        }
    }
    else
    {
        // Destroy all gems with the target color.
        for (int i = 0; i < NUM_ROWS; i++)
        {
            for (int j = 0; j < NUM_COLS; j++)
            {
                if (board[i][j].color == targetColor && board[i][j].destroy != 2)
                {

                    // If this gem is special, trigger its explosion.
                    if (board[i][j].type == 1)
                        explodeFlamePK(board, i, j, mode, hand, mvcnt, cascade);
                    else if (board[i][j].type == 2)
                        explodeLightningPK(board, i, j, mode, hand, mvcnt, cascade);
                    else if (board[i][j].type == 4)
                        explodeSupernovaPK(board, i, j, mode, hand, mvcnt, cascade);
                    board[i][j].destroy = 2;
                }
            }
        }
    }

    if(mode==4)
    {
        hand[0][mvcnt].color=targetColor;
        if(targetColor=='H')
        {
            hand[0][mvcnt].type=3;
        }
    }
}

void explodeSupernovaPK(Gem board[][8], int i, int j, int mode, Gem hand[][5], int mvcnt, bool cascade)
{
    if (i < 0 || i >= NUM_ROWS || j < 0 || j >= NUM_COLS)
        return;
    if (board[i][j].type != 4)
        return;
    if (board[i][j].destroy == 2)
        return;
    board[i][j].destroy = 2;
    rowcolPK(board, i, j, mode, hand, mvcnt, cascade);

    if(i-1>=0 && j-1>=0)
    {
        board[i-1][j-1].destroy = 2;
        rowcolPK(board, i-1, j-1, mode, hand, mvcnt, cascade);
    }
    if(i+1<8 && j-1>=0)
    {
        board[i+1][j-1].destroy = 2;
        rowcolPK(board, i+1, j-1, mode, hand, mvcnt, cascade);
    }
    if(i-1>=0 && j+1<8)
    {
        board[i-1][j+1].destroy = 2;
        rowcolPK(board, i-1, j+1, mode, hand, mvcnt, cascade);
    }
    if(i+1<8 && j+1<8)
    {
        board[i+1][j+1].destroy = 2;
        rowcolPK(board,i+1, j+1, mode, hand, mvcnt, cascade);
    }

}
