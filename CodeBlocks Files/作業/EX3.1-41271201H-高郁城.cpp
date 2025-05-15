#include <stdio.h>
int main()
{
    int score=0,num=0;
    int high=0,low=100;
    float pass=0;
    double sum=0;
    printf("Insert scores, input -1 to calculate average...> ");
    scanf("%d",&score);
    while (score!=-1)
    {

        sum+=score;
        num++;
        if(score>=60)
        {
            pass++;
        }
        if(score>high //§O¥Îelse
        {
            high=score;
        }
        if(score<low)
        {
            low=score;
        }
        printf("Insert scores, input -1 to calculate average...> ");
        scanf("%d",&score);
        //input scores, add together for a sum
        //register number of people's scores
        //average=sum/number
    }

    if(num==0)
    {
        printf("No scores inserted.");
    }
    else
    {
        //printf("%f %d %f\n",sum,num,pass);
        double average=sum/num;
        double rate=pass/num;
        printf("\nScore Analysis:\n");
        printf("Avg: %f.\n",average);
        printf("Pass rate: %f %%\n",rate*100);
        printf("Highest score: %d\n",high);
        printf("Lowest score: %d\n",low);
    }
}

