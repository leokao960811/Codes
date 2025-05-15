#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int main()
{
    srand(2);
    FILE *tcc1=fopen("EX9.1-41271201H-°ª­§«°.cpp","r");

    int dice=0, play=0, money=1000;

    int choice=0;

    char option='n';

    while(choice!=4)
    {
        printf("Simple Gamble Simulator\n"
               "You have played %d times, and you have $%d.\n\n"
               "(1) Roll a die (Earn $10 on 1, 2, 3, lose 10 on other numbers.)\n"
               "(2) Load\n"
               "(3) Save\n"
               "(4) Exit\n\n"
               "Enter your choice...> ", play, money);

        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
        {
            if(money<10)
            {
                printf("You have no money to play! Maybe load a save file?\n");
            }
            else
            {


                dice=(rand()%6+1);
                if(dice<=3)
                {
                    printf("The result is %d and you won $10.\n",dice);
                    money+=10;
                }
                else
                {
                    printf("The result is %d and you lost $10.\n",dice);
                    money-=10;
                }
                play+=1;
            }
            system("pause");
            break;
        }

        case 2:
        {

            FILE *fp = fopen("data.txt", "r");
            if (fp == nullptr)
            {
                printf("No data found.\n");
                system("pause");
            }
            else
            {
                printf("Are you sure? You will lose current play data...> ");
                scanf(" %c", &option);

                if(tolower(option)=='n')
                {
                    printf("Load canceled.\n");
                    system("pause");
                }
                else
                {
                    fscanf(fp, "%d %d", &play,&money);
                    printf("Save loaded.\n");
                    system("pause");
                }
            }
            fclose(fp);
            break;
        }

        case 3:
        {
            FILE *fp = nullptr;
            if ((fp = fopen("data.txt", "r")) != nullptr)
            {
                fclose(fp);

                printf("Save file already exists. Do you want to erase all data?(y/n)?...> ");
                scanf(" %c", &option);

                if(tolower(option)=='n')
                {
                    printf("Save canceled.\n");
                    system("pause");
                    break;
                }
            }

            if((fp = fopen("data.txt", "w")) == nullptr)
            {
                printf("The file can't be opened to write!");
                return 1;
            }

            printf("\nData saved.\n");
            fprintf(fp, "%d %d", play, money);

            system("pause");
            fclose(fp);
            break;
        }

        case 4:
            break;

        default:
            printf("Input not recognized.\n");
            system("pause");
            break;
        }

        //system("cls");

    }

    FILE *tcc2=fopen("EX9.1-41271201H-°ª­§«°.cpp","r");
    printf("[%d]",tcc2-tcc1);

    return 0;
}
