#include "Structs.h"

void SwapPK(Gem board[][8], Move mv, int *mflag, int mode, Gem hand[][5], int mvcnt, bool cascade);

void BoardInitPK(Gem board[][8], const int r, const int c, Move input, int mode, Gem hand[][5], int mvcnt, bool cascade);
void HandDisplay(Gem hand[][5], const int r, const int c);

bool detectAndMarkMatchesPK(Gem board[][8], Move input, int mode, Gem hand[][5], int mvcnt, bool cascade);

void explodeFlamePK(Gem board[][8], int i, int j, int mode, Gem hand[][5], int mvcnt, bool cascade);
void rowcolPK(Gem board[][8],int i, int j, int mode, Gem hand[][5], int mvcnt, bool cascade);
void explodeLightningPK(Gem board[][8], int i, int j, int mode, Gem hand[][5], int mvcnt, bool cascade);
void triggerHypercubePK(Gem board[][8], int wi, int wj, char targetColor, int mode, Gem hand[][5], int mvcn, bool cascade);
void explodeSupernovaPK(Gem board[][8], int i, int j, int mode, Gem hand[][5], int mvcnt, bool cascade);
