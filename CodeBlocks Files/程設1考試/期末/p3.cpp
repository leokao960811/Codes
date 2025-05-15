#include <stdio.h>

char GetDirection(int x, int y, int nx, int ny)
{
    char dir=' ';
    if((ny-y>0) && (x==nx)) dir='N';
    else if((ny==y) && (nx-x>0)) dir='E';
    else if((ny==y) && (nx-x<0)) dir='W';
    else if((ny-y<0) && (x==nx)) dir='S';

    return dir;
}

char GetTurn(int odir, int ndir)
{
    char turn=' ';
    if (odir == ndir) turn='-';
    else if((odir=='E' && ndir=='N') || (odir=='N' && ndir=='W') || (odir=='W' && ndir=='S') || (odir=='S' && ndir=='E')) turn='L';
    else if((odir=='E' && ndir=='S') || (odir=='S' && ndir=='W') || (odir=='W' && ndir=='N') || (odir=='N' && ndir=='E')) turn='R';

    return turn;
}

int main()
{
    int times=0;

    int oldx=0, oldy=0;
    char odir='E';

    scanf("%d", &times);
    int n=0;
    int lturn=0, rturn=0;

    while(n<times)
    {
        int x=0, y=0;
        scanf("%d%d", &x, &y);


        char ndir=GetDirection(oldx,oldy,x,y);
        char chdir=GetTurn(odir,ndir);

        //printf("%d %d %d %d\n", oldx,oldy,x,y);
        //printf("%c %c %c\n", odir, ndir, chdir);

        if(chdir=='L') lturn+=1;
        else if(chdir=='R') rturn+=1;

        //printf("%d %d\n", lturn, rturn);

        n+=1;

        oldx=x;
        oldy=y;
        odir=ndir;
    }

    printf("%d %d", lturn, rturn);
}

