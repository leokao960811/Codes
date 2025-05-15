#include <stdio.h>
int main()
{
    printf("Bowling Score Calculator");
    while (true)
    {
        printf("\nInsert Scores:\n");
        char pin[21] {' '};
        int pcount[21] {0}, score[10] {0}, total[10] {0};

        for(int i=0; i<21;)
        {
            scanf(" %c", &pin[i]);

            if(pin[i]=='X' && i<18)
            {
                i+=2;
            }
            else
            {
                i+=1;
            }
        }

        printf("Marks: \t\t");
        for(int i=0; i<21; i+=1)
        {
            printf("%c ", pin[i]);
            if((i>0) && (i%2==1) && (i<18))
            {
                printf("\t");
            }
        }

        printf("\n");

        printf("Pincount: \t");
        for(int i=0; i<21; i+=1)
        {
            if(!pin[i])
            {
                pcount[i]=0;

            }
            else if(pin[i]=='X')
            {
                pcount[i]=10;
            }
            else if(pin[i]=='/' && pcount[i-1]<10)
            {
                pcount[i]=10-pcount[i-1];
            }
            else
            {
                pcount[i]=pin[i]-48;
            }

            printf("%d ", pcount[i]);
            if((i>0) && (i%2==1) && (i<18))
            {
                printf("\t");
            }
        }

        printf("\n");

        printf("Frame Score: \t");
        for(int i=0; i<10; i+=1)
        {
            if(i==9)
            {
                if(pcount[i*2]==10)
                {
                    if(pcount[(i*2)+1]==10)
                    {
                        if(pcount[(i+1)*2]==10)
                        {
                            score[i]=30;
                        }
                        else
                        {
                            score[i]=20+pcount[(i+1)*2];
                        }
                    }
                    else
                    {
                        score[i]=10+pcount[(i*2)+1]+pcount[(i+1)*2];
                    }
                }
                else
                {
                    if(pin[(i*2)+1]=='/')
                    {
                        score[i]=10+pcount[(i+1)*2];
                    }
                    else
                    {
                        score[i]=pcount[i*2]+pcount[(i*2)+1];
                    }
                }
            }
            else
            {
                if(pcount[i*2]==10)
                {
                    if(pcount[(i+1)*2]==10)
                    {
                        if(i==8)
                        {
                            if(pcount[((i+1)*2)+1]==10)
                            {
                                score[i]=30;
                            }
                            else
                            {
                                score[i]=20+pcount[((i+1)*2)+1];
                            }
                        }
                        else if(pcount[(i+2)*2]==10)
                        {
                            score[i]=30;
                        }
                        else
                        {
                            score[i]=20+pcount[(i+2)*2];
                        }
                    }
                    else
                    {
                        score[i]=10+pcount[(i+1)*2]+pcount[((i+1)*2)+1];
                    }
                }
                else if(pin[i*2+1]=='/')
                {
                    score[i]=10+pcount[(i+1)*2];
                }
                else
                {
                    score[i]=pcount[i*2]+pcount[i*2+1];
                }
            }

            printf("%d\t", score[i]);
        }

        printf("\n");

        printf("Total Score: \t");
        for(int i=0; i<10; i+=1)
        {
            if(i==0)
            {
                total[i]=score[i];
            }
            else
            {
                total[i]=total[i-1]+score[i];
            }
            printf("%d\t",total[i]);
        }
    }
    return 0;
}
