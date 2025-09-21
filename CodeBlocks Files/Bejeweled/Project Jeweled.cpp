#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <windows.h>
#include <ctype.h>

#define NUM_ROWS 8
#define NUM_COLS 8

struct Gem
{
    char color = ' '; // Number characters are used for its color (e.g. '1', '2', etc.)
    int type = 0;     // 0 = normal, 1 = Flame, 2 = Lightning, 3 = Hypercube, 4 = Supernova
    int destroy = 0;  // 1 = normal destruction, 2 = from special explosions
};

struct Move
{
    char col = ' ';
    int row = 0;
    char dir = ' ';
};

bool detectAndMarkMatches(Gem board[][8], Move input);
void explodeFlame(Gem board[][8], int i, int j);
void explodeLightning(Gem board[][8], int i, int j);
void triggerHypercube(Gem board[][8], int wi, int wj, char targetColor);
void explodeSupernova(Gem board[][8], int i, int j);

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

void ensureMatch(Gem board[][8], int dropboard[][8]);
bool checkMatchesInGrid(Gem testBoard[NUM_ROWS][NUM_COLS]);
bool possibleMoveExists(Gem board[][8]);

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

void ensureMatch(Gem board[][8], int dropboard[][8])
{
    int flag=0;
    // Check for possible moves before finalizing gem drop
    if (possibleMoveExists(board))
        return; // No need to force a match if moves already exist

    else
    {
        while (flag==0)
        {
            int Rcol=randint(8);
            int Rrow=randint(8);

            // Try adjusting the gem to match its neighbors
            if (Rcol >= 2 && board[Rrow][Rcol - 1].color == board[Rrow][Rcol - 2].color)
            {
                board[Rrow][Rcol].color = board[Rrow][Rcol - 1].color; // Create a horizontal match
                flag=1;
            }
            else if (Rrow >= 2 && board[Rrow - 1][Rcol].color == board[Rrow - 2][Rcol].color)
            {
                board[Rrow][Rcol].color = board[Rrow - 1][Rcol].color; // Create a vertical match
                flag=1;
            }
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
            if (board[i][j].type == 4)
            {
                printf("\e[48;2;255;255;255m");
            }
            else if (board[i][j].type == 3)
            {
                board[i][j].color='H';
                printf("\e[48;2;80;80;80m");
            }
            else if (board[i][j].type == 2)
            {
                printf("\e[48;2;0;203;255m");
            }
            else if (board[i][j].type == 1)
            {
                printf("\e[48;2;255;121;2m");
            }
            else
            {
                printf("\e[48;2;0;0;0m");
            }
            printf("%c", board[i][j].color);
            printf("\x1b[0m");
        }
        printf("\x1b[0m\n");
    }
}

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

void destroyGems(Gem board[][8])
{
    for (int r = 0; r < NUM_ROWS; r++)
    {
        for (int c = 0; c < NUM_COLS; c++)
        {

            if (board[r][c].destroy != 0)
            {
                board[r][c].color = ' ';
                board[r][c].type = 0;
                board[r][c].destroy = 0;

            }
        }
    }
}

void destroyGemsPT(Gem board[][8], int *score, int *scoreflag)
{
    for (int r = 0; r < NUM_ROWS; r++)
    {
        for (int c = 0; c < NUM_COLS; c++)
        {

            if (board[r][c].destroy != 0)
            {
                if ((*scoreflag) == 1 && board[r][c].destroy==1 && board[r][c].type > 1)
                {
                    *score+=20;
                }
                else if (((*scoreflag) == 1 && board[r][c].destroy == 1 && board[r][c].type == 0) || ((*scoreflag == 0) && board[r][c].destroy == 1 && board[r][c].type > 1))
                {
                    *score+=10;
                }
                else if(((*scoreflag) == 0 && board[r][c].destroy == 1) || board[r][c].destroy == 2)
                {
                    *score+=5;
                }
                board[r][c].color = ' ';
                board[r][c].type = 0;
                board[r][c].destroy = 0;
            }
        }
    }

    if (*scoreflag==1)
    {
        *scoreflag=0;
    }

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

int main()
{
    srand(time(NULL));
    Gem board[8][8] = {};
    Move input;
    const int c = 8, r = 8;
    int matchflag = 0;

    int score=0;
    int scoreflag=0;

//    //Initialize board with special gems.
//    for (int i = 0; i < c; i++)
//    {
//        for (int j = 0; j < r; j++)
//        {
//            int type = randint(100);
//            board[i][j].color = (randint(7) + 1) + '0';
//            if (type < 1)
//            {
//                board[i][j].type = 4;
//            }
//            else if (type < 2)
//            {
//                board[i][j].type = 3;
//                board[i][j].color = 'H';
//            }
//            else if (type < 4)
//            {
//                board[i][j].type = 2;
//            }
//            else if (type < 9)
//            {
//                board[i][j].type = 1;
//            }
//            else
//            {
//                board[i][j].type = 0;
//            }
//        }
//    }

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

    //Main game loop.
    while (possibleMoveExists(board))
    {
        printf("\nScore: %d\n",score);
        printf("Input Column(A-H), Row(1,8), Direction(U, D, L, R): ");
        scanf(" %c %d  %c", &input.col, &input.row, &input.dir);
        Swap(board, input, &matchflag);
        BoardDisplay(board, r, c);
        // If no match is detected and no Hypercube was involved, revert move.
        if (matchflag != 3 && !detectAndMarkMatches(board, input))
        {
            BoardDisplay(board, r, c);
            Sleep(500);
            Swap(board, input, &matchflag); // revert move
        }
        else
        {
            scoreflag=1;

            if(matchflag==3)
            {
                destroyGemsPT(board, &score, &scoreflag);
                Sleep(500);
                BoardDisplay(board, r, c);
                Sleep(500);
                FillBoard(board, r, c);
                //FillBoardEndless(board, r, c);
                Sleep(500);
            }

            while (detectAndMarkMatches(board, input))
            {
                BoardDisplay(board, r, c);
                Sleep(500);
                destroyGemsPT(board, &score, &scoreflag);
                Sleep(500);
                BoardDisplay(board, r, c);
                Sleep(500);
                FillBoard(board, r, c);
                //FillBoardEndless(board, r, c);
                Sleep(500);
            }
        }
        BoardDisplay(board, r, c);
        Sleep(500);

        if (matchflag > 0 && matchflag != 3)
        {
            if (matchflag == 1)
                printf("Move not recognized.\n");
            else
                printf("Invalid move.\n");
        }
    }
    printf("No moves left.\n");
    printf("Final Score: %d", score);
    return 0;
}
