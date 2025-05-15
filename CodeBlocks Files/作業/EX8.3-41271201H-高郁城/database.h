#ifndef DATABASE_H
#define DATABASE_H
#include "player.h"

constexpr int MaxNumPlayers = 1000;

struct Database
{
    Player pl[MaxNumPlayers];
    int size = 0;
};

bool Add(Database *db, Player);
void Output(const Database *db);
int Search(const Database  *db, const char name[]);
bool Remove(Database *db, int ind);

#endif
