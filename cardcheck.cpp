#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//Card structure definition
struct Card
{
    char face[3]= {};
    int num=0;
    int suit=0;
};

//Structure function
Card face_check(Card *cd)
{
    char suit=cd->face[0]; //pass by address
    char num[3]= {};
    strcpy(num, cd->face+1);

    if (toupper(num[0])=='A')
    {
        cd->num=1;
    }
    else if (toupper(num[0])=='K')
    {
        cd->num=13;
    }
    else if (toupper(num[0])=='Q')
    {
        cd->num=12;
    }
    else if (toupper(num[0])=='J')
    {
        cd->num=11;
    }
    else if (strcmp(num, "10")==0)
    {
        cd->num=10;
    }
    else if(isdigit(num[0]) && num[0]-'0'>1)
    {
        cd->num=num[0]-'0';
    }
    else
    {
        cd->num=-1;
    }

    if(toupper(suit)=='S')
    {
        cd->suit=0;
    }
    else if(toupper(suit)=='H')
    {
        cd->suit=1;
    }
    else if(toupper(suit)=='D')
    {
        cd->suit=2;
    }
    else if(toupper(suit)=='C')
    {
        cd->suit=3;
    }
    else
    {
        cd->suit=-1;
    }

    return *cd;
}


int main()
{
    //File process, setting pointers
    FILE *infp = fopen("Cards.txt", "r");
    FILE *outfp = fopen("CardResult.txt", "a");

    int num[14] = {0};
    int suit[4] = {0};
    int deck_check[53] = {0};
    //char str[5]= {};

    int same_card=0;
    bool TwoP=false;
    bool FullHouse=false;
    bool Flush=false;
    bool Straight=false;

    int hands=0;

//    2 ways to read line files:

//    1)
//    fscanf(infp, "%d\n", &hands);

//  2)
    fscanf(infp, "%d", &hands);
    char dum[10]={};
    fgets(dum, 10, infp);

    int cnt=0;

    while (cnt<hands)
    {

        Card cd;
        int r=0;
        while (r<5)
        {
            fscanf(infp, "%3s", cd.face); //fscan
            face_check(&cd);

            if(cd.suit==-1 || cd.num==-1)
            {
                printf("Card doesn't exist\n");
                continue;
            }

            int card_count=(cd.suit*13)+cd.num;

            if(deck_check[card_count]==1)
            {
                printf("Card already existed\n");
                continue;
            }

            deck_check[card_count]+=1;
            num[cd.num]+=1;
            suit[cd.suit]+=1;
            r+=1;
        }


//        for(int i=1; i<14; i+=1)
//        {
//            printf("%d ",num[i]);
//            if(i==13)
//            {
//                printf("\n");
//            }
//        }

//        for(int i=0; i<4; i+=1)
//        {
//            printf("%d ",suit[i]);
//            if(i==3)
//            {
//                printf("\n");
//            }
//        }

        for(int i=1; i<14; i+=1)
        {
            switch(num[i])
            {
            case 4:
                same_card=4;
                break;
            case 3:
                if(same_card>3) {}
                else
                {
                    same_card=3;
                }
                for(int i=1; i<14; i+=1)
                {
                    if(num[i]==2)
                    {
                        FullHouse=true;
                    }
                }
                break;
            case 2:
                if(same_card>2) {}
                else
                {
                    same_card=2;
                }
                for(int j=1; j<14; j+=1)
                {
                    if(num[j]==2 && j!=i)
                    {
                        TwoP=true;
                    }
                }
                break;
            case 1:
                if(((num[i+1]==1) && (num[i+2]==1) && (num[i+3]==1)  && (num[i+4]==1)) || ((num[1]==1) && (num[10]==1) && (num[11]==1)  && (num[12]==1) && (num[13]==1)))
                {
                    Straight=true;
                }
            }
        }

        for(int i=0; i<4; i+=1)
        {
            if(suit[i]==5)
            {
                Flush=true;
            }
        }

        //Print to file

        if(Straight == true && Flush == true)
        {
            printf("Straight Flush\n");
            fprintf(outfp, "Straight Flush\n");
        }
        else if(same_card == 4)
        {
            printf("Four of a Kind\n");
            fprintf(outfp, "Four of a Kind\n");
        }
        else if(FullHouse == true)
        {
            printf("Full House\n");
            fprintf(outfp, "Full House\n");
        }
        else if(Flush == true)
        {
            printf("Flush\n");
            fprintf(outfp, "Flush\n");
        }
        else if(Straight == true)
        {
            printf("Straight\n");
            fprintf(outfp, "Straight\n");
        }
        else if(same_card == 3)
        {
            printf("Three of a Kind\n");
            fprintf(outfp, "Three of a Kind\n");
        }
        else if(TwoP == true)
        {
            printf("Two Pair\n");
            fprintf(outfp, "Two Pair\n");
        }
        else if(same_card == 2)
        {
            printf("Pair\n");
            fprintf(outfp, "Pair\n");
        }
        else
        {
            printf("High Card\n");
            fprintf(outfp, "High Card\n");
        }

        for(int i=1; i<14; i+=1)
        {
            num[i] = 0;
        }
        for(int i=0; i<4; i+=1)
        {
            suit[i] = 0;
        }
        for(int i=1; i<53; i+=1)
        {
            deck_check[i] = 0;
        }

        same_card=0;
        TwoP=false;
        FullHouse=false;
        Flush=false;
        Straight=false;

        cnt+=1;
    }

    fclose(infp);
    fclose(outfp); //close files after read and write
}
