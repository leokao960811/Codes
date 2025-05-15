#ifndef PLAYER_H
#define PLAYER_H

struct Player
{
    int no;
    char name[30], position;
    double percentages[3];
};

void Output(Player);
void Input(Player*);
#endif
