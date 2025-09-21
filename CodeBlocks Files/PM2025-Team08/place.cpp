#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cctype>
//#include <new>

#include "place.h"
#include "princess.h"

#define MAX_PLACES 10
#define MAX_LINE_LEN 1000

bool IsQualified(Princess *princess, const Place *place)
{
  if (princess->money + place->cost_reward_ < 0)
  {
    return false;
  }

  for (int i = 0; i < place->num_effects_; ++i)
  {
    const Effect *e = &place->effects_[i];

    const Attribute *attr = princess->GetAttribute(e->attributes);
    int current = attr ? attr->val : 0;
    //printf("\n");
    //printf("%s: %d, %d ",attr->name ,current, e->PlusMinus);

    if (current + e->PlusMinus < 0)
    {
      //printf("Stats too low! ");
      return false;
    }
  }

  return true;
}

int readPlaces(const char *filename, PlaceSet *places)
{

  FILE *file = fopen(filename, "r");
  char line[MAX_LINE_LEN];
  int placeCount = 0;
  Place currentPlace = {};

  memset((void *)&currentPlace, 0, sizeof(Place));

  while (fgets(line, sizeof(line), file))
  {
      line[strcspn(line, "\r\n")] = '\0';

    if (strlen(line) == 0)
      continue;

    if (strcmp(line, "#") == 0)
    {
      if (places->num_places < MaxNumPlaces)
      {
        placeCount++;
        places->places[places->num_places++] = currentPlace;
      }
      memset((void *)&currentPlace, 0, sizeof(Place));
    }
    else if (currentPlace.name_[0] == '\0')
    {
      char name[20];
      int reward = 0;
      if (sscanf(line, "%19s %d", name, &reward) == 2)
      {
        strncpy(currentPlace.name_, name, sizeof(currentPlace.name_) - 1);
        currentPlace.cost_reward_ = reward;
      }
      else
      {
        printf("地點格式錯誤：%s\n", line);
      }
    }
    else
    {
      char attr[20];
      int val;
      if (sscanf(line, "%20s %d", attr, &val) == 2)
      {
        if (currentPlace.num_effects_ < 10)
        {
          strncpy(currentPlace.effects_[currentPlace.num_effects_].attributes, attr, 12);
          currentPlace.effects_[currentPlace.num_effects_].PlusMinus = val;
          currentPlace.num_effects_++;
        }
      }
      else
      {
        printf("屬性格式錯誤：%s\n", line);
      }
    }
  }

  if (file != nullptr)
    fclose(file);

  return placeCount;
}

void Print(const PlaceSet *places, Princess *princess)
{
  for (int i = 0; i < places->num_places; ++i)
  {
    const Place *p = &places->places[i];
    printf("[%02d]  %-18s", i + 1, p->name_);


    if (!IsQualified(princess, p))
    {
      printf("  - Unqualified\n");
    }
    else
    {
      printf("  $%6d", p->cost_reward_);
      for (int j = 0; j < p->num_effects_; ++j)
      {
        const char *attr = p->effects_[j].attributes;
        int val = p->effects_[j].PlusMinus;

        char abbrev[4] = {};
        strncpy(abbrev, attr, 3);
        for (int k = 0; k < 3; ++k)
        {
          abbrev[k] = toupper(abbrev[k]);
        }

        printf("  %s %+d", abbrev, val);
      }
      printf("\n");
    }
  }
}

void placeEffect(const Place *place, Princess *princess)
{
  princess->money += place->cost_reward_;

  if (place->cost_reward_ >= 0){
    printf("               Money +%d\n", place->cost_reward_);
  } else {
    printf("               Money %d\n", place->cost_reward_);
  }

  for (int i = 0; i < place->num_effects_; ++i)
  {
    const Effect *effect = &place->effects_[i];

    // printf("%s\n\n", effect->attributes);
    Attribute *attr = princess->GetAttribute(effect->attributes);

    if (attr)
    {
      attr->AddValue(effect->PlusMinus);
      if (effect->PlusMinus >= 0){
        printf("%20s +%d\n", attr->name, effect->PlusMinus);
      } else {
        printf("%20s -%d\n", attr->name, effect->PlusMinus);
      }
    }
  }
}
