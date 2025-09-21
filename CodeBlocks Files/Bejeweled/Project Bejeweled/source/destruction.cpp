#include <stdio.h>
#include "Structs.h"
#include "destruction.h"

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
