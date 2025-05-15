#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Player
{
    char name[30]= {};
    int num;
    char pos='\0';
    char source[50]= {};
};


bool IndexWrite(Player ply, char filename[])
{
    FILE *indfp = fopen(filename, "a"); //You're appending new lines here!
    if (indfp == nullptr) return false;

    fprintf(indfp, "<a href=\"%s.htm\">%s</a><br>\n", ply.name, ply.name);

    fclose(indfp);
    return true;

}

bool PlayerWrite(Player ply, char filename[])
{
    FILE *plfp = fopen(filename, "w");
    if (plfp == nullptr) return false;
    fprintf(plfp, "<table border=\"1\">\n"
            "<tr>\n"
            "<td><img src=\"pic\\%s\" width=\"100\" height=\"150\"></td>\n"
            "<td><b><font size=4>%s</font></b> %d %c</td>\n"
            "</tr>\n"
            "</table>\n", ply.source, ply.name, ply.num, ply.pos);

    fclose(plfp);
    return true;
}

bool ReadDBFile(FILE *fp, Player *p)
{
    if ((fscanf(fp, "%29[^,\n],%d,%c,%49[^\n]", p->name, &p->num, &p->pos, p->source)) != 4)
    {
        return false;
    }
    else
    {
        char dummy[100] = {};
        fgets(dummy, 100, fp);
        return true;
    }
}

int main()
{

    FILE *csvfp = fopen("PlayerDatabase.csv", "r");
    Player p;
    char index[10]="index.htm";
    char dummy[100]= {};
    char pfilename[30]= {};

    fgets(dummy, 100, csvfp); //Get rid of the first line

    while (!feof(csvfp))
    {
        ReadDBFile(csvfp, &p);
        //printf("%s %d %c %s", p.name, p.num, p.pos, p.source);

        IndexWrite(p,index);
        //printf(" Index Added.\n");

        strcpy(pfilename, p.name);
        strcat(pfilename, ".htm");

        PlayerWrite(p, pfilename);
    }

    fclose(csvfp);

    return 0;

}
