#include <assert.h>
#include <stdio.h>
#include <stdlib.h> //rand()%n+1
#include <time.h> //srand(time(NULL))
#include <new>

int randint(int n) {
  if ((n - 1) == RAND_MAX) {
    return rand();
  } else {
    /* 計算可以被整除的長度 */
    long end = RAND_MAX / n;
    assert (end > 0L);
    end *= n;

    /* 將尾端會造成偏差的幾個亂數去除，
       若產生的亂數超過 limit，則將其捨去 */
    int r;
    while ((r = rand()) >= end);

    return r % n;
  }
}

int shotrng(){

    int v = randint(100);

     if(v < 1) return 0;
else if(v < 2) return 1;
else if(v < 3) return 2;
else if(v < 4) return 3;
else if(v < 6) return 4;
else if(v < 9) return 5;
else if(v < 14) return 6;
else if(v < 22) return 7;
else if(v < 30) return 8;
else if(v < 40) return 9;
else return 10; //Pro Strike Rate: ~60%
}

int sparerng(){
    int v = randint(100);

     if(v < 25) return 0;
else return 1;
}

int main()
{
    srand(time(NULL));
    printf("Bowling Score Calculator");

    while (true)
    {

        int mode=0;
        int mark=0;
        int spare=0;
        char pin[21] {' '};
        int pcount[21] {0},
        score[10] {0},
        total[10] {0};



        printf("\nInsert or Random?(0/1): \n");
        scanf("%d",&mode);
        while(mode<0 || mode>1)
        {
            printf("Invalid Input.\n");
            printf("Insert or Random?(0/1): \n");
        scanf("%d",&mode);
        }
        if(mode==0)
        {
            printf("\nInsert Scores:\n");
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
        }
        else
        {
            for(int i=0;i<18;i++)
            {
        	    if(i%2==0)
        	    {
            	    pin[i]=shotrng();
        	    }
        	    else
        	    {
            	    if (pin[i-1]==10)
            	    {
                	    continue;
            	    }
            	    else
            	    {
            	        spare=sparerng();
            	        if (spare==1)
            	        {
            	            pin[i]=10-pin[i-1];
            	        }
                	    else
                	    {
                	        pin[i]=randint(10-pin[i-1]);
                	    }
            	    }
        	    }
    	    }

    	    pin[18]=shotrng();

            if(pin[18]==10)
            {
                pin[19]=shotrng();
                if(pin[19]==10)
                {
                    pin[20]=shotrng();
                }
                else
                {
                    spare=sparerng(); //19,20
            	    if (spare==1)
            	    {
            	        pin[20]=10-pin[19];
            	    }
                    else
                    {
                        pin[20]=randint(10-pin[19]);
                    }
                }
            }

            else
            { //18, 19
        	    spare=sparerng();
                if (spare==1)
                {
            	    pin[19]=10-pin[18];
                }
                else
                {
                    pin[19]=randint(10-pin[18]);
                }
           	    if(pin[18]+pin[19]==10)
           	    {
            	    pin[20]=shotrng();
           	    }
           	    else
           	    {
               	    pin[20]=0;
           	    }
            }

        for(int i=0;i<21;i++){
        	if(i<18){
        	    if(i%2==0 && pin[i]==10){
        	        pin[i]+=30;
        	        pin[i+1]=-48;
        	    }
        	    else if(i%2==1 && (pin[i]+pin[i-1]==10)){
        	        pin[i]=-1;
        	    }
        	}
        	else{
        	    if(i==18){
        	        if(pin[i]==10){
        	            pin[i]+=30;
        	        }
        	    }
        	    if(i==19){
        	        if(pin[i-1]==40 && pin[i]==10){
        	            pin[i]+=30;
        	        }
        	        else if(pin[i]+pin[i-1]==10){
        	            pin[i]=-1;
        	        }
        	    }

        	    if(i==20){
        	        if(pin[i-2]==40){
        	            if(pin[i-1]==40 && pin[i]==10){
        	                pin[i]+=30;
        	            }
        	            else if(pin[i-1]+pin[i]==10){
        	                pin[i]=-1;
        	            }
        	        }
        	        else if(pin[i-1]==-1){
        	            if(pin[i]==10){
        	                pin[i]+=30;
        	            }
        	        }
        	    }
        	}
    	}
        for(int i=0;i<22;i++){
    	        pin[i]+=48;
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

//        printf("Raw: \t\t");
//        for(int i=0; i<21; i+=1)
//        {
//            printf("%d ", pin[i]);
//            if((i>0) && (i%2==1) && (i<18))
//            {
//                printf("\t");
//            }
//        }
//
//        printf("\n");

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
                if(pin[i]==45) {pcount[i]=0;}
                else{pcount[i]=pin[i]-48;}
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
