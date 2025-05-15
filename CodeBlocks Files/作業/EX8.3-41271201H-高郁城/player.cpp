#include <stdio.h>
#include "player.h"

void Input(Player *p)
{
    printf("\nPlease input the required values: \n\n");
    printf("Name: ");
    scanf("%s", p->name);
    printf("No: ");
    scanf("%d", &p->no);
    printf("Position: ");
    scanf(" %c", &p->position);

    printf("3 Percentages (FG, 3P, and FT): ");
    for (int i=0; i<3; i+=1)
    {
        scanf("%lf", &p->percentages[i]);
    }
    printf("\n");
}

void Output(Player p)
{
    printf("\t%s", p.name);
    printf(" %d (%c) ",p.no, p.position);

    for (int i=0; i<3; i+=1)
    {
        printf("%.1f%% ", p.percentages[i]);
    }
}
