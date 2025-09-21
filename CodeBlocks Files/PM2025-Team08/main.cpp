#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "princess.h"
#include "place.h"
#include "titlerule.h"

void PrintAskPlayerName();
void PrintHorizontalLine();
void PrintGameBoard(int dayNum, Princess *princess, const PlaceSet *places, const TitleRuleSet *Ts);
void PrintAfterGoing(char placeName[], const Princess *princess);
void PrintGameOver(Princess *princess, TitleRuleSet *titleRuleSet);

constexpr int daysInGame = 14;

int main()
{
  Princess princess;
  PlaceSet places;
  TitleRuleSet *rule_set;

  /* 詢問玩家名稱 */
  PrintAskPlayerName();
  char line[18] = {};
  scanf("%s", line);
  printf("\nPrincess %s, let's start the %d-day journey!\n\n", line, daysInGame);
  strcpy(princess.name, line);
  system("pause");

  /* 載入設定檔 */
  princess.LoadAttributesFromFile("attributes.txt");
  readPlaces("places.txt", &places);
  //system("pause");

  rule_set = init_rule("titlerules.txt");

  system("cls");

//  for(int i=0; i<places.num_places;i+=1)
//  {
//      printf("%s\n",places.places[i].name_);
//      for(int j=0;j<places.places[i].num_effects_;j+=1)
//      {
//          printf("%s %d\n",places.places[i].effects_[j], places.places[i].effects_[j].PlusMinus);
//      }
//
//  }
//  system("pause");

//  Print(rule_set);
//  system("pause");

  int dayNum = 0;
  while (dayNum < daysInGame)
  {
    /* 遊戲中一天的開始 */
    dayNum++;
    system("cls");

    int placeSelection = 0;
    PrintGameBoard(dayNum, &princess, &places, rule_set);
    printf("\nWhich place would you like to go?...(1 ~ %d)>", places.num_places);
    scanf("%d", &placeSelection);

    /* 執行地點效果 */
    if (placeSelection <=0 || placeSelection > places.num_places){
      printf("Princess %s keeps idle today. Nothing happens.\n\n", princess.name);
    } else {
      if (IsQualified(&princess, &places.places[placeSelection-1])){
        PrintAfterGoing(places.places[placeSelection-1].name_, &princess);
        placeEffect(&places.places[placeSelection-1], &princess);
      } else {
        printf("Sorry, Princess %s, we are not good enough to go to %s.\n\n", princess.name, places.places[placeSelection-1].name_);
      }
    }

    system("pause");
  }

  system("cls");
  PrintGameOver(&princess, rule_set);
}

void PrintAskPlayerName()
{
  printf("=========================================\n|   Princess Maker Extremely Simplied   |\n=========================================\n\nHello Princess, what's your name?...(no more than 17 chars)>");
}

void PrintHorizontalLine()
{
  printf("==================================================================\n");
}

void PrintGameBoard(int dayNum, Princess *princess, const PlaceSet *places, const TitleRuleSet *Ts)
{

    char *curTitle = Profession(princess,Ts);
    char Title[4] = {};
    if(strcmp(curTitle,"Nobody")!=0)
    {
        strncpy(Title, curTitle, 3);
        for (int k = 0; k < 4; ++k)
        {
          Title[k] = toupper(Title[k]);
        }
    }

    printf("Day  %2d ( %2d days left)        Princess %s: ($ %4d) %s\n\n", dayNum, daysInGame-dayNum, princess->name, princess->money, Title);

    princess->Print();

    PrintHorizontalLine();

    printf("All %d places to go:\n\n", places->num_places);
    Print(places, princess);

   PrintHorizontalLine();
}

void PrintAfterGoing(char placeName[], const Princess *princess)
{
  printf("\nAfter going to %s, Princess %s makes her ability better:\n\n", placeName, princess->name);
}

void PrintGameOver(Princess *princess, TitleRuleSet *titleRuleSet)
{
  printf("Princess %s: ($ %d)\n\n", princess->name, princess->money);
  princess->Print();

  char *title = Profession(princess, titleRuleSet);

  printf("After %d days, Princess %s becomes a %s.", daysInGame, princess->name, title);
}
