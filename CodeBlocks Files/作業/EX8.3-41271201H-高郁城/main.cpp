#include <stdio.h>
#include <string.h>
#include "player.h"
#include "database.h"

int main()
{
    int input=0;
    char Ninput[30]={};
    char Actinput=' ';
    Database db = {};
    Player p={};

    while(input!=4)
    {

        printf("A simple player database\n\n"
               "(1) Add a player\n"
               "(2) Show all players\n"
               "(3) Search player(s) by name\n"
               "(4) Exit the program\n\n"
               "Please select a function¡K> ");

        scanf("%d", &input);

        if(input>4)
        {
            while(input>4)
            {
                printf("Please select a function¡K> ");
                scanf("%d", &input);
            }
        }
        else
        {
            switch(input)
            {
            case 1:
                if((db.size)>=1000)
                {
                    printf("The database is full. (Max: 1000 players)\n\n");
                }
                else
                {
                    Input(&p);
                    db.pl[db.size]=p;
                    db.size+=1;
                }
                continue;

            case 2:
                Output(&db);
                continue;

            case 3:
                printf("Please input the name of the player¡K> ");
                scanf("%s",Ninput);
                if(Search(&db,Ninput)==-1)
                {
                    printf("%s is not found.\n", Ninput);
                }
                else
                {
                    int index=Search(&db,Ninput);
                    Output(db.pl[index]);

                    printf("\nNext action (Remove/reInput/None)¡K> ");
                    scanf(" %c", &Actinput);
                    if(Actinput=='I')
                    {
                        Input(&db.pl[index]);
                    }
                    else if(Actinput=='R')
                    {
                        Remove(&db, index);
                    }
                    else
                    {
                        printf("\n");
                        continue;
                    }
                }
                printf("\n");
                continue;
            }
        }

    }
}
