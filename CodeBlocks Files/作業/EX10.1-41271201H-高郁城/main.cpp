#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "player.h"
#include "database.h"

int main()
{
    int input=0;
    char Ninput[30]= {};
    char Actinput=' ';
    Database db = {};
    Player p= {};

    while(input!=4)
    {

        printf("A simple player database\n\n"
               "(1) Add a player\n"
               "(2) Show all players\n"
               "(3) Search player(s) by name\n"
               "(4) Exit the program\n\n"
               "Please select a function...> ");

        scanf("%d", &input);

        if(input>4)
        {
            while(input>4)
            {
                printf("Please select a function...> ");
                scanf("%d", &input);
            }
        }
        else
        {
            switch(input)
            {
            case 1:
                Input(&p);
                Add(&db, &p);
                continue;

            case 2:
                Output(&db);
                continue;

            case 3:
                printf("Please input the name of the player...> ");
                scanf("%s",Ninput);
                if(Search(&db,Ninput)==-1)
                {
                    printf("%s is not found.\n", Ninput);
                }
                else
                {
                    int index=Search(&db,Ninput);
                    Output(db.pl[index]);

                    printf("\nNext action (Remove/reInput/None...> ");
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

        Close(&db);
    }



//    Database db;
//    Database db1,db2;
//    Player jeremy= {1,"jeremy",'C',{30.0,12.5,34.4}},
//           james= {2,"james",'F',{27.8,16.3,35.1}},
//           kobe= {3,"kobe",'I',{35.4,20.4,24.1}};
// ... 設定 jeremy, james, kobe 的資料


//    Add(&db1, &jeremy);
//    Add(&db2, &james);
//    Output(&db2); // 會列印 james 的資料
//    if (Copy(&db2, &db1))
//    {
//        printf("db1 is copied to db2 successfully.\n");
//    }
//    else
//    {
//        printf("db1 is not copied to db2 due to memory shortage.\n");
//    }
//    Add(&db1, &james);
//    Remove(&db1, Search(&db1, "jeremy")); // 假設自 db1 成功刪除 jeremy
//    Output(&db1); // 會列印一筆資料，james
//    Output(&db2); // 會列印一筆資料，jeremy
//    Close(&db1);
//    Close(&db2);

//    Add(&db1, &jeremy);
//    Add(&db2, &jeremy);
//    Add(&db2, &james);
//    Output(&db2); // 會列印 james 的資料
//    if (Copy(&db2, &db1))
//    {
//        printf("db1 is copied to db2 successfully.\n");
//    }
//    else
//    {
//        printf("db1 is not copied to db2 due to memory shortage.\n");
//    }
//    Add(&db1, &james);
//    Output(&db1); // 會列印兩筆資料，jeremy 和 james
//    Output(&db2); // 會列印一筆資料，jeremy (注意: size=1, capacity=2)
//    Close(&db1);
//    Close(&db2);


//    if (!Remove(&db, 0)) printf("Safe\n");
//    if (Add(&db, &jeremy))
//    {
//        printf("successful!");    // use the return value of Add()
//    }
//    else
//    {
//        printf("Insufficient memory!");
//    }
//    Output(&db); // print Jeremy's data
//    Remove(&db, 0);
//    Output(&db); // print nothing
//    Add(&db, &kobe); // 新增 kobe: 這次呼叫不會配置記憶體 capacity = size = 1
//    Output(&db);
//    Close(&db); // capacity = size = 0


}
