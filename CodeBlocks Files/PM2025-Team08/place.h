#ifndef PLACE_H
#define PLACE_H
#include "princess.h"

constexpr int MaxNumPlaces = 10;

struct Effect
{
    char attributes[20] = {}; //誰給我一開始設10?????
    int PlusMinus = 0;
};
struct Place
{
    char name_[20] = {};
    Effect effects_[10] = {};
    int num_effects_ = 0;
    int cost_reward_ = 0;
};
struct PlaceSet
{
    Place places[MaxNumPlaces] = {};
    int num_places = 0;
};

bool IsQualified(Princess* princess, const Place* place);
int readPlaces(const char* filename, PlaceSet* places);
void Print(const PlaceSet *places, Princess* a);
void placeEffect(const Place *place, Princess *princess);
#endif
