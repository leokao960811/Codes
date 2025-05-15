#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Structure definition
struct Player
{
    int no;
    char name[30], position;
    double percentages[3];

    /*
    In-class initialization
    int no=7;
    char name[30]="J", position='C';
    double percentages[3]={24.6, 84.2, 65};
    */
};

//Nested structs
struct Team
{
    char name[30]={};
    Player players[5];
};

void InputPlayer(Player *a){

    printf("Input player number, name, position, and three percentages(FG, 3-point, and FT)...>");
    scanf("%d%s %c", &a->no, &a->name, &a->position);
    for (int i=0; i<3; i+=1)
    {
        scanf("%lf", &a->percentages[i]);
    }
}

void InputPlayers(Player team[], int sz){

    for(int i=0; i<sz; i+=1)
    {
        InputPlayer(&team[i]);
    }
}

/* Direct process version (No extra functions)
Note that team[i] is already a struct
void InputPlayers(Player team[], int sz){

    printf("Input player number, name, position, and three percentages(FG, 3-point, and FT)...>");
    scanf("%d%s %c", &team[i].no, &team[i].name, &team[i].position);
    for (int j=0; j<3; j+=1)
    {
        scanf("%lf", &team[i].percentages[j]);
    }
}
*/

void OutputPlayer(Player a){

    printf("Player's Data:\n"
           "No.: %d\n"
           "Name: %s\n"
           "Position: %c\n", a.no, a.name, a.position);

    printf("FG(%%), 3P(%%), FT(%%): ");
    for (int i=0; i<3; i+=1)
    {
        printf("%7.1f ", a.percentages[i]);
    }

}


void OutputPlayers(const Player team[], int sz)
{
    for(int i=0;i<sz;i+=1)
    {
        OutputPlayer(team[i]);
        printf("\n");
    }
}


/* Direct process version (No extra functions)
void OutputPlayers(const Player team[], int sz)
{
    for(int i=0; i<sz; i+=1)
    {
        printf("Player's Data:\n"
           "No.: %d\n"
           "Name: %s\n"
           "Position: %c\n",  team[i].no, team[i].name, team[i].position);

        printf("FG(%%), 3P(%%), FT(%%): ");
        for (int j=0; j<3; j+=1)
        {
            printf("%7.1f ", team[i].percentages[j]);
        }
        printf("\n");
    }
}
*/

int main()
{

/*
    //define variable of Player
    //"struct Player a" is also allowed
    //However, this syntax is required in C
    Player a;


    //Can be initialized by {}
    Player a = {};

    //Aggregate Initialization
    Player a = {7, "LOLOLOL", 'C', {1.5,3.6,19.5}};
    Player a = (.no=1, .name="lol");


    //= operator
    Player b = a;

    printf("%s %d %c %.1lf\n", a.name,
           a.no,
           a.position,
           a.percentages[0]);

    //sizeof()
    printf("Size: %d %d %d %d %d \n", sizeof(a.name), sizeof(a.no), sizeof(a.position), sizeof(a.percentages), sizeof(a));

    //scanf(), & operator
    Player b;
    scanf("%s%d %c%lf", &b.name, &b.no, &b.position, &b.percentages[0]);

    printf("%s %d %c %.1lf\n", b.name,
           b.no,
           b.position,
           b.percentages[0]);

    //Pointers and structs
    Player *p = &a, *q;

    printf("%s %d %c\n", (*p).name, (*p).no, (*p).position); //by object value
    q = p;
    printf("%s %d %c\n", q->name, q->no, q->position); //by address value


    //Array of structs
    Player team[2];
    //size = sizeof(team)/sizeof(team[0])

    InputPlayers(team,2);
    OutputPlayers(team, 2);

*/

    Team b;
    strcpy(b.name,"AAAH");
    n.players[0].no=7;
    strcpy(b.players[0].name,"HI");


}
