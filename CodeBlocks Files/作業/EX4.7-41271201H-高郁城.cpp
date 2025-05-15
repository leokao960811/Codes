#include <stdio.h>
int main(){
    int chart[5][4]{0};
    int inputh,inputw;

    while (true){
        scanf("%d%d",&inputh, &inputw);
        if(inputh==0 && inputw==0) break;
        else
        {
            chart[(inputw-41)/10][(inputh-151)/10]+=1;
        }
    }


    printf("\t151~160\t161~170\t171~180\t181~190\t\n");
    for (int wei=0; wei<5; wei+=1)
    {
        printf("%d~%d\t",41+(wei*10),40+((wei+1)*10));
        for (int hei=0; hei<4; hei+=1)
        {
        printf("%d\t", chart[wei][hei]);
        }
    printf("\n");
    }
}
