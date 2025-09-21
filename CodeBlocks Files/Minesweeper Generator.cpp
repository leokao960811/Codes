#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <new> // for nothrow
#include <windows.h>

#include <assert.h>

struct Board
{
    char **board = nullptr;
    int **state = nullptr;
    int nr=0, nc=0, minecount=0;
};

struct Move
{
    int x=0, y=0;
    char method=' ';
};

int randint(int n)
{
    if ((n - 1) == RAND_MAX)
    {
        return rand();
    }
    else
    {
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

bool Create(Board *board, int nr, int nc, int mine)
{
    if (mine>nr*nc)
    {
        printf("Too many mines!\n");
        return false;
    }

    board->nr = board->nc = 0;
    board->minecount = mine;

    //set board array
    board->board=new (std::nothrow) char *[nr+2] {};
    if(board->board==nullptr)
    {
        printf("Allocation failed.");
        return false;
    }

    for(int r=0; r<nr+2; r+=1) //I need to allocate nr+2 rows!
    {
        board->board[r]=new (std::nothrow) char [nc+2] {};
        if(board->board[r]==nullptr)
        {
            //Delete the rows first, then the column pointers
            for(int rd=0; rd<r; rd+=1)
            {
                delete [] board->board[rd];
            }
            delete [] board->board;
            board->board=nullptr;

            printf("Allocation failed.");
            return false;
        }
    }

    //set state array
    board->state=new (std::nothrow) int *[nr] {};
    if(board->state==nullptr)
    {
        printf("Allocation failed.");
        return false;
    }

    for(int r=0; r<nr; r+=1) //Allocate nr rows for state
    {
        board->state[r]=new (std::nothrow) int [nc] {};
        if(board->state[r]==nullptr)
        {
            //Delete the rows first, then the column pointers
            for(int rd=0; rd<r; rd+=1)
            {
                delete [] board->state[rd];
            }
            delete [] board->state;
            board->state=nullptr;

            printf("Allocation failed.");
            return false;
        }
    }

    board->nr=nr;
    board->nc=nc;

    return true;
}

void Initialize(Board *board)
{
    srand(time(NULL));

    for(int i=0; i<board->nr+2; i+=1)
    {
        for(int j=0; j<board->nc+2; j+=1)
        {
            board->board[i][j]='.';
        }
    }

    int count=0;
    while (count<board->minecount)
    {
        int r_row = randint(board->nr)+1;
        int r_col = randint(board->nc)+1;

        if(board->board[r_row][r_col]!='#')
        {
            board->board[r_row][r_col]='#';
            count+=1;
        }
    }

    // board result
    for(int r=1; r<board->nr+1; r+=1)
    {
        for(int c=1; c<board->nc+1; c+=1)
        {
            if(board->board[r][c]!='#')
            {
                //New checking method
                int count=0;
                int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
                int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
                for (int d = 0; d < 8; d+=1)
                {
                    int newRow = r + dx[d];
                    int newCol = c + dy[d];
                    if (board->board[newRow][newCol]  == '#')
                    {
                        count+=1;
                    }
                }
                if(count!=0)
                {
                    board->board[r][c]='0'+count;
                }
            }
        }
    }
}


void Close (Board *board)
{
    for(int rd=0; rd<(board->nr)+2; rd+=1)
    {
        delete [] board->board[rd];
    }

    delete [] board->board;

    for(int rd=0; rd<board->nr; rd+=1)
    {
        delete [] board->state[rd];
    }

    delete [] board->state;
}

bool isValid(Board *board, int x, int y)
{
    return (x >= 1) && (x <= board->nr) && (y >= 1) && (y <= board->nc);
}

bool GameFinished(Board *board)
{
    // Check if all non-mine cells are revealed
    for(int i=1; i<=board->nr; i+=1)
    {
        for(int j=1; j<=board->nc; j+=1)
        {
            // If it's not a mine and not revealed, game is not finished
            if(board->board[i][j] != '#' && board->state[i-1][j-1] != 1)
            {
                return false;
            }
        }
    }

    printf("Congratulations! You Win!\n");
    return true;
}

void FloodFill(Board *board, int x, int y)
{
    // Check bounds and if already revealed or flagged
    if (!isValid(board, x, y) || board->state[x-1][y-1] != 0)
        return;

    if (board->board[x][y] == '#')
        return;

    board->state[x-1][y-1] = 1;

    // If it's an empty cell (.), flood fill neighbors
    if (board->board[x][y] == '.')
    {
        int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
        int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

        for (int d = 0; d < 8; d++)
        {
            int newX = x + dx[d];
            int newY = y + dy[d];
            FloodFill(board, newX, newY);
        }
    }
}

bool Chord(Board *board, int x, int y)
{
    // Can only chord on revealed cells
    if (board->state[x-1][y-1] != 1)
    {
        printf("Chording is done on revealed cells.\n");
        return false;
    }

    // Can only chord on numbered cells (not empty cells or mines)
    char cellValue = board->board[x][y];
    if (cellValue < '1' || cellValue > '8')
    {
        printf("Chording can only be done on numbered cells.\n");
        return false;
    }

    int requiredFlags = cellValue - '0';
    int flagCount = 0;
    int hiddenCount = 0;

    // Count flags and hidden cells around this position
    int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int d = 0; d < 8; d++)
    {
        int nx = x + dx[d];
        int ny = y + dy[d];

        if (isValid(board, nx, ny))
        {
            if (board->state[nx-1][ny-1] == 2) // Flagged
            {
                flagCount++;
            }
            else if (board->state[nx-1][ny-1] == 0) // Hidden
            {
                hiddenCount++;
            }
        }
    }

    // Check if the correct number of flags are placed
    if (flagCount != requiredFlags)
    {
        printf("Chording not allowed.\n");
        return false;
    }

    // If no hidden cells, nothing to chord
    if (hiddenCount == 0)
    {
        printf("Cell un-chordable.\n");
        return false;
    }

    // Chord: reveal all unflagged cells around this position
    bool hitMine = false;
    for (int d = 0; d < 8; d++)
    {
        int nx = x + dx[d];
        int ny = y + dy[d];

        if (isValid(board, nx, ny) && board->state[nx-1][ny-1] == 0) // Hidden cell
        {
            if (board->board[nx][ny] == '#') // It's a mine!
            {
                board->state[nx-1][ny-1] = 1; // Reveal the mine
                hitMine = true;
            }
            else
            {
                // Use flood fill to reveal this cell and potentially adjacent cells
                FloodFill(board, nx, ny);
            }
        }
    }

    if (hitMine)
    {
        printf("BOOM! Game Over.\n");
        return true; // Game over
    }
    else
    {
        return false; // Continue game
    }
}

bool MakeMove(Board *board, Move mov)
{
    // Validate move coordinates
    if (!isValid(board, mov.x, mov.y))
    {
        printf("Invalid coordinates.\n");
        return false;
    }

    if (toupper(mov.method) == 'F')
    {
        // Check if cell is already revealed
        if (board->state[mov.x-1][mov.y-1] == 1)
        {
            printf("Cell already revealed.\n");
            return false;
        }

        // Toggle flag
        if (board->state[mov.x-1][mov.y-1] == 2)
        {
            board->state[mov.x-1][mov.y-1] = 0; // Remove flag
            printf("Flag removed.\n");
        }
        else if (board->state[mov.x-1][mov.y-1] == 0)
        {
            board->state[mov.x-1][mov.y-1] = 2; // Add flag
            printf("Cell flagged.\n");
        }
    }
    else if (toupper(mov.method) == 'O')
    {
        // Check if cell is already revealed
        if (board->state[mov.x-1][mov.y-1] == 1)
        {
            printf("Cell already revealed.\n");
            return false;
        }

        // Can't open a flagged cell
        if (board->state[mov.x-1][mov.y-1] == 2)
        {
            printf("Cannot open a flagged cell!\n");
            return false;
        }

        // Check if it's a mine
        if (board->board[mov.x][mov.y] == '#')
        {
            board->state[mov.x-1][mov.y-1] = 1; // Reveal the mine
            printf("BOOM! Game Over.\n");
            return true; // Game over
        }
        else
        {
            // Use flood fill for empty cells, or just reveal numbered cells
            FloodFill(board, mov.x, mov.y);
        }
    }
    else if(toupper(mov.method) == 'C')
    {
        if(Chord(board, mov.x, mov.y)==true)
        {
            return true;
        };
    }
    else
    {
        printf("Invalid method! Use 'O' to open or 'F' to flag.\n");
        return false;
    }

    return false; // Continue game
}



void CheckFirstMove(Board *board, Move mov)
{
    if(board->board[mov.x][mov.y] == '#')
    {
        bool mine=false;
        while(!mine)
        {
            int r_row = randint(board->nr)+1;
            int r_col = randint(board->nc)+1;

            if(board->board[r_row][r_col]!='#')
            {
                board->board[r_row][r_col]='#';
            }

            board->board[mov.x][mov.y]='.';
            mine=true;
        }
    }

    for(int r=1; r<board->nr+1; r+=1)
    {
        for(int c=1; c<board->nc+1; c+=1)
        {
            if(board->board[r][c]!='#')
            {
                //New checking method
                int count=0;
                int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
                int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
                for (int d = 0; d < 8; d+=1)
                {
                    int newRow = r + dx[d];
                    int newCol = c + dy[d];
                    if (board->board[newRow][newCol]  == '#')
                    {
                        count+=1;
                    }
                }
                if(count!=0)
                {
                    board->board[r][c]='0'+count;
                }
                else
                {
                    board->board[r][c]='.';
                }
            }
        }
    }
}

void Print(const Board *board)
{
    // Print column numbers
//    printf("   ");
//    for(int c=1; c<=board->nc; c++)
//    {
//        printf("%2d ", c);
//    }
//    printf("\n");

    for(int r=1; r<(board->nr)+1; r+=1)
    {
        //printf("%2d ", r); // Print row number
        for(int c=1; c<(board->nc)+1; c+=1)
        {
            if(board->state[r-1][c-1]==0)
            {
                //printf(" @ ");
                printf("@ ");
            }
            else if(board->state[r-1][c-1]==1)
            {
                //printf(" %c ", board->board[r][c]);
                printf("%c ", board->board[r][c]);
            }
            else if(board->state[r-1][c-1]==2)
            {
                //printf(" F ");
                printf("F ");
            }
        }
        printf("\n");
    }
}

void ResultPrint(const Board *board)
{
    for(int r=1; r<(board->nr)+1; r+=1)
    {
        for(int c=1; c<(board->nc)+1; c+=1)
        {
            printf("%c ", board->board[r][c]);
        }
        printf("\n");
    }
}

int main()
{

    int r, c, mine;
    Board board;
    Move mov;
    bool gameover=false;

    int mode=-1;

    printf("Minesweeper Generator\n");
    printf("Generate Board or Play Game?(0/1)\n");
    scanf("%d", &mode);

    while(mode>1 || mode<0)
    {
        printf("\nInvalid Input.\n");
        printf("Generate Board or Play Game?(0/1)\n");
        scanf("%d", &mode);
    }

    printf("Input row, column, and minecount: \n");
    scanf("%d %d %d", &r, &c, &mine);

    if(mode==0)
    {
        while(r>0 && c>0 && mine>0)
        {
            while (!Create(&board, r, c, mine))
            {
                printf("Input row, column, and minecount: \n");
                scanf("%d %d %d", &r, &c, &mine);
            }

            Initialize(&board);
            ResultPrint(&board);
            Close(&board);

            printf("\nInput row, column, and minecount: \n");
            scanf("%d %d %d", &r, &c, &mine);

        }
    }

    else if(mode==1)
    {
        while(r>0 && c>0 && mine>0)
        {
            while (!Create(&board, r, c, mine))
            {
                printf("Input row, column, and minecount: \n");
                scanf("%d %d %d", &r, &c, &mine);
            }

            Initialize(&board);
            gameover=false;
            int move=0;

            system("cls");
            Print(&board);

            while(!gameover && !GameFinished(&board))
            {
                printf("Enter move(row, col, method(Open/Flag))\n");
                scanf("%d %d %c", &mov.x, &mov.y, &mov.method);
                if(mov.x == 0 && mov.y == 0)
                {
                    printf("Game quit by user.\n");
                    break;
                }

                system("cls");
                if(move==0)
                {
                    CheckFirstMove(&board, mov);
                }
                gameover=MakeMove(&board, mov);
                move+=1;
                Print(&board);

                if(gameover)
                {
                    printf("Solution:\n");
                    ResultPrint(&board);
                    break;
                }
            }

            Close(&board);

            printf("\nInput row, column, and minecount: \n");
            scanf("%d %d %d", &r, &c, &mine);
        }
    }

    printf("Thanks for using.\n");
    return 0;
}

