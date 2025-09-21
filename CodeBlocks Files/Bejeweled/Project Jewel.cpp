#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <windows.h>

#define NUM_ROWS 8
#define NUM_COLS 8

/* 產生 [0, n) 均勻分布的整數亂數 */
int randint(int n) {
  if ((n - 1) == RAND_MAX) {
    return rand();
  } else {
    /* 計算可以被整除的長度 */
    long end = RAND_MAX / n;
    assert (end > 0L);
    end *= n;

    /* 將尾端會造成偏差的幾個亂數去除，
       若產生的亂數超過 limit，則將其捨去 */
    int r;
    while ((r = rand()) >= end);

    return r % n;
  }
}


void BoardDisplay(const char board[][8], const int r, const int c)
{
    system("cls");
    printf("  ABCDEFGH\n");
    for (int i=0;i<c;i+=1)
    {
        printf("%d ", i+1);
        for (int j=0;j<r;j+=1)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }



}

void FillBoard(char board[][8], const int r, const int c)
{
    srand( time(NULL) );
    int checkc=0;
    char temp=' ';

    for(int i=(c-1);i>=0;i-=1)
    {
        for(int j=0;j<r;j+=1)
        {
            if(board[i][j]==' ')
            {
                checkc=i;
                while(board[checkc][j]==' ')
                {
                    checkc-=1;
                }
                if(checkc<0)
                {
                    board[i][j]=(randint(7)+1)+'0';
                }
                else
                {
                    temp=board[i][j];
                    board[i][j]=board[checkc][j];
                    board[checkc][j]=temp;
                }
            }
        }
    }
}

void Swap(char board[][8], char inputc, int inputr, char dir, int *mflag)
{
    if((toupper(inputc)-'A'>7) || ((inputr<1) || (inputr>8)) || ((toupper(dir)!='U') && (toupper(dir)!='D') && (toupper(dir)!='L') && (toupper(dir)!='R')))
    {
        (*mflag)=1;
    }
    else if ((toupper(inputc)=='A' && toupper(dir) == 'L') || (toupper(inputc)=='H' && toupper(dir) == 'R') || (inputr==1 && toupper(dir) == 'U') || (inputr==8 && toupper(dir) == 'D'))
    {
        (*mflag)=2;
    }
    else
    {

        char temp = board[inputr-1][(toupper(inputc)-'A')];

        if(toupper(dir)=='U')
        {
            board[inputr-1][(toupper(inputc)-'A')]=board[inputr-2][(toupper(inputc)-'A')];
            board[inputr-2][(toupper(inputc)-'A')]=temp;

        }
        else if (toupper(dir)=='D')
        {
            board[inputr-1][(toupper(inputc)-'A')]=board[inputr][(toupper(inputc)-'A')];
            board[inputr][(toupper(inputc)-'A')]=temp;
        }
        else if (toupper(dir)=='L')
        {
            board[inputr-1][(toupper(inputc)-'A')]=board[inputr-1][(toupper(inputc)-'A'-1)];
            board[inputr-1][(toupper(inputc)-'A'-1)]=temp;
        }
        else if (toupper(dir)=='R')
        {
            board[inputr-1][(toupper(inputc)-'A')]=board[inputr-1][(toupper(inputc)-'A'+1)];
            board[inputr-1][(toupper(inputc)-'A'+1)]=temp;
        }

        (*mflag)=0;

    }
}

// Match detecting and marking function
// Updates the grid by setting matched cells to 0, and returns true if any match was found.
//bool detectAndMarkMatches(char board[][8], int r/*ROWS*/, int c/*COLUMNS*/) {
bool detectAndMarkMatches(char board[][8]) {
    int horizRun[NUM_ROWS][NUM_COLS] = {0};
    int vertRun[NUM_ROWS][NUM_COLS] = {0};
    bool destroy[NUM_ROWS][NUM_COLS] = {false};
    bool foundMatch = false;  // flag to track if any match is detected

    // Check horizontal runs
    for (int i = 0; i < NUM_ROWS; i++) {
        horizRun[i][0] = 1;
        for (int j = 1; j < NUM_COLS; j++) {
            if (board[i][j] != 0 && board[i][j] == board[i][j - 1])
                horizRun[i][j] = horizRun[i][j - 1] + 1;
            else
                horizRun[i][j] = 1;
        }
    }

    // Check vertical runs
    for (int i = 0; i < NUM_COLS; i++) {
        vertRun[0][i] = 1;
        for (int j = 1; j < NUM_ROWS; j++) {
            if (board[j][i] != 0 && board[j][i] == board[j - 1][i])
                vertRun[j][i] = vertRun[j - 1][i] + 1;
            else
                vertRun[j][i] = 1;
        }
    }

    //Mark horizontal matches
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            int count = horizRun[i][j];
            if (count >= 3) {
                // Check if we're at the end of a horizontal sequence.
                if (j == NUM_COLS - 1 || board[i][j] != board[i][j + 1]) {
                    int startCol = j - count + 1;
                    for (int col = startCol; col <= j; col++) {
                        destroy[i][col] = true;
                    }
                    foundMatch = true;
                    //printf("Horizontal match of %d at row %d, cols %d-%d\n", count, r, startCol, c);
                }
            }
        }
    }

    // Mark vertical matches.
    for (int i = 0; i < NUM_COLS; i++) {
        for (int j = 0; j < NUM_ROWS; j++) {
            int count = vertRun[j][i];
            if (count >= 3) {
                if (j == NUM_ROWS - 1 || board[j][i] != board[j + 1][i]) {
                    int startRow = j - count + 1;
                    for (int row = startRow; row <= j; row++) {
                        destroy[row][i] = true;
                    }
                    foundMatch = true;
                    //printf("Vertical match of %d at col %d, rows %d-%d\n", count, c, startRow, r);
                }
            }
        }
    }

    //Detect T or L shapes by checking intersections
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (horizRun[i][j] >= 3 && vertRun[i][j] >= 3) {

                //printf("Potential T/L shape at cell (%d, %d)\n", r, c);
            }
        }
    }

    BoardDisplay(board,8,8);
    Sleep(500);

    //Destroy matched pieces by setting them to ' '
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (destroy[i][j]) {
                board[i][j] = ' ';
            }
        }
    }

    return foundMatch;
}

//----------------------------------------------------------
// checkMatchesInGrid()
// Checks for the existence of any horizontal or vertical match
// in a given grid (passed as a 2D array).

// T and Ls are unnecessary to be checked.
// This function DOES NOT modify the grid.
bool checkMatchesInGrid(char testBoard[NUM_ROWS][NUM_COLS]) {
    int horizRun[NUM_ROWS][NUM_COLS] = {0};
    int vertRun[NUM_ROWS][NUM_COLS] = {0};

    // Compute horizontal runs.
    for (int r = 0; r < NUM_ROWS; r++) {
        horizRun[r][0] = 1;
        for (int c = 1; c < NUM_COLS; c++) {
            if (testBoard[r][c] != 0 && testBoard[r][c] == testBoard[r][c - 1])
                horizRun[r][c] = horizRun[r][c - 1] + 1;
            else
                horizRun[r][c] = 1;
        }
    }

    // Compute vertical runs.
    for (int c = 0; c < NUM_COLS; c++) {
        vertRun[0][c] = 1;
        for (int r = 1; r < NUM_ROWS; r++) {
            if (testBoard[r][c] != 0 && testBoard[r][c] == testBoard[r - 1][c])
                vertRun[r][c] = vertRun[r - 1][c] + 1;
            else
                vertRun[r][c] = 1;
        }
    }

    // Check for horizontal match.
    for (int r = 0; r < NUM_ROWS; r++) {
        for (int c = 0; c < NUM_COLS; c++) {
            if (horizRun[r][c] >= 3) {
                if (c == NUM_COLS - 1 || testBoard[r][c] != testBoard[r][c + 1])
                    return true;
            }
        }
    }

    // Check for vertical match.
    for (int c = 0; c < NUM_COLS; c++) {
        for (int r = 0; r < NUM_ROWS; r++) {
            if (vertRun[r][c] >= 3) {
                if (r == NUM_ROWS - 1 || testBoard[r][c] != testBoard[r + 1][c])
                    return true;
            }
        }
    }

    return false;
}

//----------------------------------------------------------
// possibleMoveExists()
// Iterates over the board and simulates swapping each cell with its
// right and bottom neighbors (if they exist). It uses a temporary board
// copy for each swap and checks if the swap would result in a match.

// Returns true if at least one such swap exists.
bool possibleMoveExists(char board[][8]) {
    char tempBoard[NUM_ROWS][NUM_COLS];

    // Iterate through each cell.
    for (int r = 0; r < NUM_ROWS; r++) {
        for (int c = 0; c < NUM_COLS; c++) {
            // Check swap with right neighbor.
            if (c + 1 < NUM_COLS) {
                // Copy the current board to tempGrid.
                for (int i = 0; i < NUM_ROWS; i++) {
                    for (int j = 0; j < NUM_COLS; j++) {
                        tempBoard[i][j] = board[i][j];
                    }
                }
                // Swap cell (r,c) with (r,c+1).
                int tmp = tempBoard[r][c];
                tempBoard[r][c] = tempBoard[r][c + 1];
                tempBoard[r][c + 1] = tmp;
                // Check if the swap creates a match.
                if (checkMatchesInGrid(tempBoard))
                    return true;
            }

            // Check swap with bottom neighbor.
            if (r + 1 < NUM_ROWS) {
                // Copy the current board to tempGrid.
                for (int i = 0; i < NUM_ROWS; i++) {
                    for (int j = 0; j < NUM_COLS; j++) {
                        tempBoard[i][j] = board[i][j];
                    }
                }
                // Swap cell (r,c) with (r+1,c).
                int tmp = tempBoard[r][c];
                tempBoard[r][c] = tempBoard[r + 1][c];
                tempBoard[r + 1][c] = tmp;
                // Check if the swap creates a match.
                if (checkMatchesInGrid(tempBoard))
                    return true;
            }
        }
    }
    return false;
}



struct LastMove
{
    char lcol =' ';
    int lrow = 0;
    char ldir=' ';
};

int main()
{
    srand( time(NULL) );

    const int r=8, c=8;
    int matchflag=0;
    int InputR=1;
    char InputC='A';
    char InputDir=' ';

    LastMove last= {' ', 0, ' '};

    char board[8][8]={};

    for (int i=0;i<c;i+=1)
    {
        for (int j=0;j<r;j+=1)
        {
            board[i][j]=  (randint(7)+1)+'0';
        }
    }

    while (detectAndMarkMatches(board))
        {
            BoardDisplay(board, r, c);
            FillBoard(board, r, c);
        }

    BoardDisplay(board, r, c);

    while (possibleMoveExists(board))
    {

        printf("\nInput Column(A-H), Row(1,8), Direction(U, D, L, R): ");
        scanf(" %c %d  %c", &InputC, &InputR, &InputDir);

        last.lcol=InputC;
        last.lrow=InputR;
        last.ldir=InputDir;

        Swap(board, InputC, InputR, InputDir, &matchflag);


        if (detectAndMarkMatches(board)==true)
        {
            while (detectAndMarkMatches(board))
            {
                BoardDisplay(board, r, c);
                Sleep(500);
                FillBoard(board, r, c);
                Sleep(500);
            }
        }
        else
        {
            BoardDisplay(board, r, c);
            Sleep(500);
            Swap(board, last.lcol, last.lrow, last.ldir, &matchflag);
        }

        BoardDisplay(board, r, c);
        Sleep(500);

        if(matchflag>0)
        {
            if(matchflag==1)
            {
                printf("Move not recognized.\n");
            }
            else
            {
               printf("Invalid move.\n");
            }
        }

    }

    printf("No moves left.");

    return 0;

}
