#include <stdio.h>
#include "Structs.h"
#include "specialgems.h"

// --- Explosion Functions with Chain Reaction ---
// Explodes a Flame Gem (type 1) in a 3x3 area.
// Before marking a neighboring cell as destroyed, if it is a special gem (Flame or Lightning)
// and has not yet exploded, trigger its explosion.
void explodeFlame(Gem board[][8], int i, int j)
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
                        explodeFlame(board, ni, nj);
                    else if (board[ni][nj].type == 2)
                        explodeLightning(board, ni, nj);
                    else if (board[ni][nj].type == 3)
                        triggerHypercube(board, ni, nj, board[i][j].color);
                    else if (board[ni][nj].type == 4)
                        explodeSupernova(board, ni, nj);
                }
                board[ni][nj].destroy = 2;
            }
        }
    }
}

//Deleting an entire row and column
void rowcol(Gem board[][8],int i, int j)
{
    // Process the entire row.
    for (int col = 0; col < NUM_COLS; col++)
    {
        if (col == j)
            continue;
        if ((board[i][col].type > 0) && board[i][col].destroy != 2)
        {
            if (board[i][col].type == 1)
                explodeFlame(board, i, col);
            else if (board[i][col].type == 2)
                explodeLightning(board, i, col);
            else if (board[i][col].type == 3)
                triggerHypercube(board, i, col, board[i][j].color);
            else if (board[i][col].type == 4)
                explodeSupernova(board, i, col);
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
                explodeFlame(board, row, j);
            else if (board[row][j].type == 2)
                explodeLightning(board, row, j);
            else if (board[row][j].type == 3)
                triggerHypercube(board, row, j, board[i][j].color);
            else if (board[row][j].type == 4)
                explodeSupernova(board, row, j);
        }
        board[row][j].destroy = 2;
    }
}

// Explodes a Lightning Gem (type 2) by marking its entire row and column.
// For each cell in that row/column, if it is special and not yet exploded, trigger its explosion.
void explodeLightning(Gem board[][8], int i, int j)
{
    if (i < 0 || i >= NUM_ROWS || j < 0 || j >= NUM_COLS)
        return;
    if (board[i][j].type != 2)
        return;
    if (board[i][j].destroy == 2)
        return;
    board[i][j].destroy = 2;
    rowcol(board,i,j);
}

// The Hypercube explosion. When triggered (by a swap), it destroys
// all gems matching the target color. (If triggered by a special gem, targetColor
// is the special gem's color.) Hypercube also triggers chain reactions.
void triggerHypercube(Gem board[][8], int wi, int wj, char targetColor)
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
                        explodeFlame(board, i, j);
                    else if (board[i][j].type == 2)
                        explodeLightning(board, i, j);
                    else if (board[i][j].type == 3 && !(i == wi && j == wj))
                        triggerHypercube(board, i, j, 'H');
                    else if (board[i][j].type == 4)
                        explodeSupernova(board, i, j);
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
                        explodeFlame(board, i, j);
                    else if (board[i][j].type == 2)
                        explodeLightning(board, i, j);
                    else if (board[i][j].type == 4)
                        explodeSupernova(board, i, j);
                    board[i][j].destroy = 2;
                }
            }
        }
    }
}

void explodeSupernova(Gem board[][8], int i, int j)
{
    if (i < 0 || i >= NUM_ROWS || j < 0 || j >= NUM_COLS)
        return;
    if (board[i][j].type != 4)
        return;
    if (board[i][j].destroy == 2)
        return;
    board[i][j].destroy = 2;
    rowcol(board,i,j);

    if(i-1>=0 && j-1>=0)
    {
        board[i-1][j-1].destroy = 2;
        rowcol(board,i-1,j-1);
    }
    if(i+1<8 && j-1>=0)
    {
        board[i+1][j-1].destroy = 2;
        rowcol(board,i+1,j-1);
    }
    if(i-1>=0 && j+1<8)
    {
        board[i-1][j+1].destroy = 2;
        rowcol(board,i-1,j+1);
    }
    if(i+1<8 && j+1<8)
    {
        board[i+1][j+1].destroy = 2;
        rowcol(board,i+1,j+1);
    }

}
