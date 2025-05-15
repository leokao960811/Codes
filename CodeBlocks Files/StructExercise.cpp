#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Player
    {
        int no=0;
        char name[30]="", position=' ';
        double percentages[3]={};
    };


// Pass struct by address value
void InputPlayer(Player *a){

    printf("Input player name, number, position, and three percentages(FG, 3-point, and FT)...>");
    scanf("%d%s %c", &a->no, &a->name, &a->position);
    for (int i=0; i<3; i+=1)
    {
        scanf("%lf", &a->percentages[i]);
    }
}

// Pass struct by object value
void OutputPlayer(Player a){

    printf("Player's Data:\n"
           "No.: %d\n"
           "Name: %s\n"
           "Position: %c\n",a.no, a.name, a.position);

    printf("FG(%%), 3P(%%), FT(%%): ");
    for (int i=0; i<3; i+=1)
    {
        printf("%7.1f ", a.percentages[i]);
    }


}

int main()
{

    Player a;
    OutputPlayer(a);
    putchar('\n');

    InputPlayer(&a);
    OutputPlayer(a);
}
