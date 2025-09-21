#include "Structs.h"

void Swap(Gem board[][8], Move mv, int *mflag);
int randint(int n);

void FillBoard(Gem board[][8], const int r, const int c);
void FillBoardEndless(Gem board[][8], const int r, const int c);
void FillBoardLT(Gem board[][8], const int r, const int c, int multi);

void ensureMatch(Gem board[][8], int dropboard[][8]);

void BoardDisplay(Gem board[][8], const int r, const int c);
void BoardInit(Gem board[][8], const int r, const int c, Move input);

void BoardCycle(Gem board[][8], const int r, const int c, const int mode);
void BoardCyclePT(Gem board[][8], const int r, const int c, const int mode, int *score, int *scoreflag);
void BoardCycleLT(Gem board[][8], const int r, const int c, const int mode, int *score, int *scoreflag, int moves, int multi, int *banked);
