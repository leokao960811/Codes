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

int randint(int n);

void Swap(Gem board[][8], Move mv, int *mflag, int mode, Gem hand[][5], int mvcnt, bool cascade);

void FillBoard(Gem board[][8], const int r, const int c);
void FillBoardEndless(Gem board[][8], const int r, const int c);
void FillBoardLT(Gem board[][8], const int r, const int c, int multi);

void ensureMatch(Gem board[][8], int dropboard[][8]);
bool checkMatchesInGrid(Gem testBoard[NUM_ROWS][NUM_COLS]);
bool possibleMoveExists(Gem board[][8]);

void BoardInit(Gem board[][8], const int r, const int c, Move input, int mode, Gem hand[][5], int mvcnt, bool cascade);
void BoardDisplay(Gem board[][8], const int r, const int c);
void HandDisplay(Gem board[][8], const int r, const int c);

bool detectAndMarkMatches(Gem board[][8], Move input, int mode, Gem hand[][5], int mvcnt, bool cascade);
bool hasSpecial(Gem board[][8], const int r, const int c);

void explodeFlame(Gem board[][8], int i, int j, int mode, Gem hand[][5], int mvcnt, bool cascade);
void rowcol(Gem board[][8],int i, int j, int mode, Gem hand[][5], int mvcnt, bool cascade);
void explodeLightning(Gem board[][8], int i, int j, int mode, Gem hand[][5], int mvcnt, bool cascade);
void triggerHypercube(Gem board[][8], int wi, int wj, char targetColor, int mode, Gem hand[][5], int mvcn, bool cascade);
void explodeSupernova(Gem board[][8], int i, int j, int mode, Gem hand[][5], int mvcnt, bool cascade);

void destroyGems(Gem board[][8]);
void destroyGemsPT(Gem board[][8], int *score, int *scoreflag);
void destroyGemsLT(Gem board[][8], int *score, int *scoreflag, int multi, int *banked);

void BoardCycle(Gem board[][8], const int r, const int c, const int mode);
void BoardCyclePT(Gem board[][8], const int r, const int c, const int mode, int *score, int *scoreflag, int multi, int *banked);
void BoardCycleLT(Gem board[][8], const int r, const int c, const int mode, int *score, int *scoreflag, int moves, int multi, int *banked);

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

void Swap(Gem board[][8], Move mv, int *mflag, int mode, Gem hand[][5], int mvcnt, bool cascade)
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
                    triggerHypercube(board, row0, col0, targetColor, mode, hand, mvcnt, cascade);
                else
                    triggerHypercube(board, row1, col1, targetColor, mode, hand, mvcnt, cascade);
            }
            *mflag = 3; // Flag indicating Hypercube swap triggered.
        }
        else
        {
            *mflag = 0;
        }
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
                dropboard[i][j]=1;
                checkc = i;
                while (checkc >= 0 && board[checkc][j].color == ' ')
                    checkc--;
                if (checkc < 0)
                {
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

                ensureMatch(board, dropboard);
            }
        }

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
                dropboard[i][j]=1;
                checkc = i;
                while (checkc >= 0 && board[checkc][j].color == ' ')
                    checkc--;
                if (checkc < 0)
                {
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
    //if (possibleMoveExists(board) || detectAndMarkMatches(board))
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

void BoardInit(Gem board[][8], const int r, const int c, Move input, int mode, Gem hand[][5], int mvcnt, bool cascade)
{
    // Initialize board.
    for (int i = 0; i < c; i++)
    {
        for (int j = 0; j < r; j++)
        {
            board[i][j].color = (randint(7) + 1) + '0';
        }
    }

    while (detectAndMarkMatches(board, input, mode, hand, mvcnt, cascade))
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

void BoardDisplay(Gem board[][8], const int r, const int c)
{
    system("cls");
    printf("  ABCDEFGH\n");
    for (int i = 0; i < c; i++)
    {
        printf("%d ", i + 1);
        for (int j = 0; j < r; j++)
        {
            //int flag=0;
            switch(board[i][j].type)
            {
            case 6:
                printf("\e[38;2;255;208;0m");
                //printf("T");
                //flag=1;
                break;
            case 5:
                printf("\e[38;2;190;160;0m");
                //printf("t");
                //flag=1;
                break;
            case 4:
                printf("\e[38;2;255;255;255m");
                //printf("S");
                //flag=1;
                break;
            case 3:
                board[i][j].color='H';
                printf("\e[38;2;80;80;80m");
                //printf("H");
                //flag=1;
                break;
            case 2:
                printf("\e[38;2;0;203;255m");
                //printf("L");
                //flag=1;
                break;
            case 1:
                printf("\e[38;2;255;173;0m");
                //printf("F");
                break;
            default:
                printf("\x1b[0m");
                //printf(" ");
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
bool detectAndMarkMatches(Gem board[][8], Move input, int mode, Gem hand[][5], int mvcnt, bool cascade)
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
                explodeFlame(board, i, j, mode, hand, mvcnt, cascade);
            if (board[i][j].type == 2 && board[i][j].destroy==1)
                explodeLightning(board, i, j, mode, hand, mvcnt, cascade);
            if (board[i][j].type == 3 && board[i][j].destroy==1)
                triggerHypercube(board, i, j, mode, board[input.row-1][input.col-'A'].color, hand, mvcnt, cascade);

            if (board[i][j].type == 4 && board[i][j].destroy==1)
                explodeSupernova(board, i, j, mode, hand, mvcnt, cascade);
        }
    }
    return foundMatch;
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

// --- Explosion Functions with Chain Reaction ---
// Explodes a Flame Gem (type 1) in a 3x3 area.
// Before marking a neighboring cell as destroyed, if it is a special gem (Flame or Lightning)
// and has not yet exploded, trigger its explosion.
void explodeFlame(Gem board[][8], int i, int j, int mode, Gem hand[][5], int mvcnt, bool cascade)
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
                        explodeFlame(board, ni, nj, mode, hand, mvcnt, cascade);
                    else if (board[ni][nj].type == 2)
                        explodeLightning(board, ni, nj, mode, hand, mvcnt, cascade);
                    else if (board[ni][nj].type == 3)
                        triggerHypercube(board, i, j, board[i][j].color, mode, hand, mvcnt, cascade);
                    else if (board[ni][nj].type == 4)
                        explodeSupernova(board, ni, nj, mode, hand, mvcnt, cascade);
                }
                board[ni][nj].destroy = 2;
            }
        }
    }
}

//Deleting an entire row and column
void rowcol(Gem board[][8],int i, int j, int mode, Gem hand[][5], int mvcnt, bool cascade)
{
    // Process the entire row.
    for (int col = 0; col < NUM_COLS; col++)
    {
        if (col == j)
            continue;
        if ((board[i][col].type > 0) && board[i][col].destroy != 2)
        {
            if (board[i][col].type == 1)
                explodeFlame(board, i, col, mode, hand, mvcnt, cascade);
            else if (board[i][col].type == 2)
                explodeLightning(board, i, col, mode, hand, mvcnt, cascade);
            else if (board[i][col].type == 3)
                triggerHypercube(board, i, j, board[i][j].color, mode, hand, mvcnt, cascade);
            else if (board[i][col].type == 4)
                explodeSupernova(board, i, col, mode, hand, mvcnt, cascade);
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
                explodeFlame(board, row, j, mode, hand, mvcnt, cascade);
            else if (board[row][j].type == 2)
                explodeLightning(board, row, j, mode, hand, mvcnt, cascade);
            else if (board[row][j].type == 3)
                triggerHypercube(board, i, j, board[i][j].color, mode, hand, mvcnt, cascade);
            else if (board[row][j].type == 4)
                explodeSupernova(board, row, j, mode, hand, mvcnt, cascade);
        }
        board[row][j].destroy = 2;
    }
}

// Explodes a Lightning Gem (type 2) by marking its entire row and column.
// For each cell in that row/column, if it is special and not yet exploded, trigger its explosion.
void explodeLightning(Gem board[][8], int i, int j, int mode, Gem hand[][5], int mvcnt, bool cascade)
{
    if (i < 0 || i >= NUM_ROWS || j < 0 || j >= NUM_COLS)
        return;
    if (board[i][j].type != 2)
        return;
    if (board[i][j].destroy == 2)
        return;
    board[i][j].destroy = 2;
    rowcol(board, i, j, mode, hand, mvcnt, cascade);
}

// The Hypercube explosion. When triggered (by a swap), it destroys
// all gems matching the target color. (If triggered by a special gem, targetColor
// is the special gem's color.) Hypercube also triggers chain reactions.
void triggerHypercube(Gem board[][8], int wi, int wj, char targetColor, int mode, Gem hand[][5], int mvcnt, bool cascade)
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
                        explodeFlame(board, i, j, mode, hand, mvcnt, cascade);
                    else if (board[i][j].type == 2)
                        explodeLightning(board, i, j, mode, hand, mvcnt, cascade);
                    else if (board[i][j].type == 3 && !(i == wi && j == wj))
                        triggerHypercube(board, i, j, mode, 'H', hand, mvcnt, cascade);
                    else if (board[i][j].type == 4)
                        explodeSupernova(board, i, j, mode, hand, mvcnt, cascade);
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
                        explodeFlame(board, i, j, mode, hand, mvcnt, cascade);
                    else if (board[i][j].type == 2)
                        explodeLightning(board, i, j, mode, hand, mvcnt, cascade);
                    else if (board[i][j].type == 4)
                        explodeSupernova(board, i, j, mode, hand, mvcnt, cascade);
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

void explodeSupernova(Gem board[][8], int i, int j, int mode, Gem hand[][5], int mvcnt, bool cascade)
{
    if (i < 0 || i >= NUM_ROWS || j < 0 || j >= NUM_COLS)
        return;
    if (board[i][j].type != 4)
        return;
    if (board[i][j].destroy == 2)
        return;
    board[i][j].destroy = 2;
    rowcol(board, i, j, mode, hand, mvcnt, cascade);

    if(i-1>=0 && j-1>=0)
    {
        board[i-1][j-1].destroy = 2;
        rowcol(board, i-1, j-1, mode, hand, mvcnt, cascade);
    }
    if(i+1<8 && j-1>=0)
    {
        board[i+1][j-1].destroy = 2;
        rowcol(board, i+1, j-1, mode, hand, mvcnt, cascade);
    }
    if(i-1>=0 && j+1<8)
    {
        board[i-1][j+1].destroy = 2;
        rowcol(board, i-1, j+1, mode, hand, mvcnt, cascade);
    }
    if(i+1<8 && j+1<8)
    {
        board[i+1][j+1].destroy = 2;
        rowcol(board,i+1, j+1, mode, hand, mvcnt, cascade);
    }

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

void destroyGemsLT(Gem board[][8], int *score, int *scoreflag, int multi, int *banked)
{
    for (int r = 0; r < NUM_ROWS; r++)
    {
        for (int c = 0; c < NUM_COLS; c++)
        {

            if (board[r][c].destroy != 0)
            {
                if(board[r][c].type>4)
                {
                    if(board[r][c].type==6)
                    {
                        if((*banked)>30)
                        {
                            *banked=30;
                        }
                        else
                        {
                            *banked+=5;
                        }
                    }
                    else
                    {
                        if((*banked)>30)
                        {
                            *banked=30;
                        }
                        else
                        {
                            (*banked)+=3;
                        }
                    }
                }


                if ((*scoreflag) == 1 && board[r][c].destroy==1 && board[r][c].type > 1)
                {
                    *score+=(20*multi);
                }
                else if (((*scoreflag) == 1 && board[r][c].destroy == 1 && board[r][c].type == 0) || ((*scoreflag == 0) && board[r][c].destroy == 1 && board[r][c].type > 1))
                {
                    *score+=(10*multi);
                }
                else if(((*scoreflag) == 0 && board[r][c].destroy == 1) || board[r][c].destroy == 2)
                {
                    *score+=(5*multi);
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

void BoardCycle(Gem board[][8], const int r, const int c, const int mode)
{
    destroyGems(board);
    Sleep(500);
    BoardDisplay(board, r, c);
    Sleep(500);
    if(mode==1)
    {
        FillBoard(board, r, c);
    }
    else if (mode>1)
    {
        FillBoardEndless(board, r, c);
    }
    Sleep(500);
}

void BoardCyclePT(Gem board[][8], const int r, const int c, const int mode, int *score, int *scoreflag, int multi, int *banked)
{
    if(mode==3)
    {
        destroyGemsLT(board, score, scoreflag, multi, banked);
    }
    else
    {
        destroyGemsPT(board, score, scoreflag);
    }
    Sleep(500);
    BoardDisplay(board, r, c);
    Sleep(500);
    if(mode==1)
    {
        FillBoard(board, r, c);
    }
    else if (mode>1)
    {
        FillBoardEndless(board, r, c);
    }
    Sleep(500);
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
    Sleep(500);
    BoardDisplay(board, r, c);
    Sleep(500);
    if(mode==1)
    {
        FillBoard(board, r, c);
    }
    else if (mode>1)
    {
        if(mode==3 && (moves>0 && (*banked>0)))
        {
            FillBoardLT(board, r, c, multi);
        }
        else
        {
            FillBoardEndless(board, r, c);
        }
    }
    Sleep(500);
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

    int mode=4;

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



    BoardInit(board, r, c, input, mode, hand, mvcnt, cascade);
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

        printf("\nScore: %d, Lives: %d\n", score, lives);
        //printf("%d\n", mvcnt);
        printf("Input Column(A-H), Row(1,8), Direction(U, D, L, R): ");
        scanf(" %c %d  %c", &input.col, &input.row, &input.dir);
        Swap(board, input, &matchflag, mode, hand, mvcnt, cascade);
        BoardDisplay(board, r, c);
        HandDisplay(hand,2,5);

        cascade = false;

        // If no match is detected and no Hypercube was involved, revert move.
        if (matchflag != 3 && !detectAndMarkMatches(board, input, mode, hand, mvcnt, cascade))
        {
            BoardDisplay(board, r, c);
            Sleep(500);
            Swap(board, input, &matchflag, mode, hand, mvcnt, cascade); // revert move
        }
        else
        {
            cascade=true;
            if(matchflag==3)
            {
                BoardCycle(board, r, c, mode);
            }

            while (detectAndMarkMatches(board, input, mode, hand, mvcnt, cascade))
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

        if (matchflag > 0 && matchflag != 3)
        {
            if (matchflag == 1)
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
                score+=scores[0][0]+bonus;
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
                    score+=scores[0][1]+bonus;
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
                        score+=scores[0][2]+bonus;
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
                        score+=scores[0][3]+bonus;
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
                        score+=scores[0][4]+bonus;
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
                        score+=scores[0][6]+bonus;
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
                    score+=scores[0][5]+bonus;
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
    printf("Final Score: %d, Hands Made: %d", score, handcount);
    return 0;
}
