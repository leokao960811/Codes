#ifndef DATABASE_H
#define DATABASE_H
#include "player.h"

struct Database
{
    Player *pl = nullptr;
    int size=0;
    int capacity=0;
};

bool Add(Database *db, Player *p);
void Output(const Database *db);
int Search(const Database  *db, const char name[]);
bool Remove(Database *db, int ind);
bool Copy(Database *db2, const Database *db1);
void Close (Database *db);

#endif
