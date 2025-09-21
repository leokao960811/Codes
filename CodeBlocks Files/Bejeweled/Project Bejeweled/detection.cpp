#include <stdio.h>
#include <ctype.h>
#include "Structs.h"
#include "board.h"
#include "detection.h"
#include "specialgems.h"

// --- Match Detection and Marking ---
bool detectAndMarkMatches(Gem board[][8], Move input)
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
                    {
                        markedGems[i][j]-=2;
                        typecheck=1;
                    }
                }


                for(int r=0; r<NUM_ROWS; r+=1)
                {
                    if (vertRun[r][j]==4 && vertRun[r+1][j]!=5)
                    {
                        markedGems[i][j]-=2;
                        typecheck=2;
                    }
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
                explodeFlame(board, i, j);
            if (board[i][j].type == 2 && board[i][j].destroy==1)
                explodeLightning(board, i, j);
            if (board[i][j].type == 3 && board[i][j].destroy==1)
                triggerHypercube(board, i, j, board[input.row-1][input.col-'A'].color);
            if (board[i][j].type == 4 && board[i][j].destroy==1)
                explodeSupernova(board, i, j);
        }
    }
    return foundMatch;
}

bool checkMatchesInGrid(Gem testBoard[NUM_ROWS][NUM_COLS])
{
    int horizRun[NUM_ROWS][NUM_COLS] = {0};
    int vertRun[NUM_ROWS][NUM_COLS] = {0};
    for (int r = 0; r < NUM_ROWS; r++)
    {
        horizRun[r][0] = 1;
        for (int c = 1; c < NUM_COLS; c++)
        {
            if (testBoard[r][c].color != ' ' && testBoard[r][c].color == testBoard[r][c-1].color)
                horizRun[r][c] = horizRun[r][c-1] + 1;
            else
                horizRun[r][c] = 1;
        }
    }
    for (int c = 0; c < NUM_COLS; c++)
    {
        vertRun[0][c] = 1;
        for (int r = 1; r < NUM_ROWS; r++)
        {
            if (testBoard[r][c].color != ' ' && testBoard[r][c].color == testBoard[r-1][c].color)
                vertRun[r][c] = vertRun[r-1][c] + 1;
            else
                vertRun[r][c] = 1;
        }
    }
    for (int r = 0; r < NUM_ROWS; r++)
    {
        for (int c = 0; c < NUM_COLS; c++)
        {
            if (horizRun[r][c] >= 3)
            {
                if (c == NUM_COLS - 1 || testBoard[r][c].color != testBoard[r][c+1].color)
                    return true;
            }
        }
    }
    for (int c = 0; c < NUM_COLS; c++)
    {
        for (int r = 0; r < NUM_ROWS; r++)
        {
            if (vertRun[r][c] >= 3)
            {
                if (r == NUM_ROWS - 1 || testBoard[r][c].color != testBoard[r+1][c].color)
                    return true;
            }
        }
    }
    return false;
}

bool possibleMoveExists(Gem board[][8])
{
    for (int r = 0; r < NUM_ROWS; r++)
    {
        for (int c = 0; c < NUM_COLS; c++)
        {
            if(board[r][c].color=='H')
            {
                return true;
            }
        }
    }

    Gem tempBoard[NUM_ROWS][NUM_COLS];
    for (int r = 0; r < NUM_ROWS; r++)
    {
        for (int c = 0; c < NUM_COLS; c++)
        {
            if (c + 1 < NUM_COLS)
            {
                for (int i = 0; i < NUM_ROWS; i++)
                {
                    for (int j = 0; j < NUM_COLS; j++)
                    {
                        tempBoard[i][j] = board[i][j];
                    }
                }
                Gem temp = tempBoard[r][c];
                tempBoard[r][c] = tempBoard[r][c+1];
                tempBoard[r][c+1] = temp;
                if (checkMatchesInGrid(tempBoard))
                    return true;
            }
            if (r + 1 < NUM_ROWS)
            {
                for (int i = 0; i < NUM_ROWS; i++)
                {
                    for (int j = 0; j < NUM_COLS; j++)
                    {
                        tempBoard[i][j] = board[i][j];
                    }
                }
                Gem temp = tempBoard[r][c];
                tempBoard[r][c] = tempBoard[r+1][c];
                tempBoard[r+1][c] = temp;
                if (checkMatchesInGrid(tempBoard))
                    return true;
            }
        }
    }
    return false;
}

bool hasSpecial(Gem board[][8], const int r, const int c)
{
    for (int i = 0; i < NUM_ROWS; i++) //h,i
    {
        for (int j = 0; j < NUM_COLS; j++) //v,j
        {
            if(board[i][j].type>0)
            {
                return true;
            }
        }
    }

    return false;
}
