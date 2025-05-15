#ifndef GEM
#define GEM
struct Gem
{
    char color = ' '; // Number characters are used for its color (e.g. '1', '2', etc.)
    int type = 0;     // 0 = normal, 1 = Flame, 2 = Lightning, 3 = Hypercube, 4 = Supernova
    int destroy = 0;  // 1 = normal destruction, 2 = from special explosions
};
#endif

#ifndef MOVE
#define MOVE
struct Move
{
    char col = ' ';
    int row = 0;
    char dir = ' ';
};
#endif

#ifndef NUM_ROWS
#define NUM_ROWS 8
#endif

#ifndef NUM_COLS
#define NUM_COLS 8
#endif
