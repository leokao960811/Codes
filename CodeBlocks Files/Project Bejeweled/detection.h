#include "Structs.h"

bool detectAndMarkMatches(Gem board[][8], Move input);
bool checkMatchesInGrid(Gem testBoard[NUM_ROWS][NUM_COLS]);
bool possibleMoveExists(Gem board[][8]);
bool hasSpecial(Gem board[][8], const int r, const int c);
