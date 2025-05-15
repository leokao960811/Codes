#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

int main()
{
    FILE *indexfp = fopen("Universities.txt", "r");
    FILE *outfp = fopen("result.txt", "a");
    FILE *checkfp = fopen("result.txt","r");

    char processed[30][100]; //儲存已處理的檔案
    int process_cnt=0;

    char filename[20]= {};
    char str[10]= {};



    if(indexfp == nullptr)
    {
        printf("File not found.");
    }

    //result.txt檢查
    if (checkfp != NULL)
    {
        while (fscanf(checkfp, "%s %*f", processed[process_cnt]) == 1)
        {
            process_cnt+=1;
        }
        fclose(checkfp);
    }

    while (fscanf(indexfp, "%10s", str)==1)
    {

        //確認已處理
        int is_processed = 0;
        for (int i = 0; i < process_cnt; i++)
        {
            if (strcmp(str, processed[i]) == 0)
            {
                is_processed = 1;
                break;
            }
        }

        if (is_processed)
        {
            continue;
        }

        //處理成績、計算平均
        snprintf(filename, sizeof(filename), "%s.txt", str);

        FILE *fp=fopen(filename,"r");


        if(fp == nullptr)
        {
            continue;
        }

        int n=0, sum=0, cnt=0;

        while (fscanf(fp, "%d", &n)==1)
        {
            sum+=n;
            cnt+=1;
        }
        fclose(fp);

        double avg = (double)sum/cnt;

        if(outfp == nullptr)
        {
            printf("File not found.");
        }

        fprintf(outfp, "%s %.2lf\n", str, avg);

    }

    fclose(indexfp);
    fclose(outfp);

    return 0;
}
