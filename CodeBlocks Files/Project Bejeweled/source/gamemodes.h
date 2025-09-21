#include "Structs.h"

void Classic(Gem board[][8], Move input, const int r, const int c, const int mode, int *score, int *scoreflag, int *matchflag);
void Endless(Gem board[][8], Move input, const int r, const int c, const int mode, int *score, int *scoreflag, int *matchflag);
void Stratamax(Gem board[][8], Move input, const int r, const int c, const int mode, int *score, int *scoreflag, int *matchflag);
void Poker(Gem board[][8], Move input, const int r, const int c, const int mode, int *score, int *scoreflag, int *matchflag);
