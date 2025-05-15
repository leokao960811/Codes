#include <iostream>
#include <cstdlib> //rand()%n+1
#include <ctime> //srand(time(NULL))
using namespace std;

int shotrng(){ //RNG Mode Only
    int v = rand() % 100;

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
    int v = rand() % 100;

     if(v < 25) return 0; //Spare Rate: ~75% 
else return 1;
}


int main() {
    
    srand(time(NULL));
    cout<<"Bowling Calculator"<<endl;
    
    while (true){
        
    int flag[11]={0};
    int mark=0;
    int spare=0;
    int i=1;
    int n=1;
    char record[21]={' '};
    int pin[21]={0};
    int score[10]={0};
    int current=0;
    int mode=0;
    
    cout<<"Insert scores(1) or Random Generate(2)?"<<endl;
    cin>>mode;
    switch(mode){
        case 1://Insert Mode
            cout<<"Insert scores: (X for strike, / for spare, - for zeros, close to quit)"<<endl;
	        while((i<22)){//Inserting scores
                cin>>record[i];
                if((record[i]=='X') && (i<19)){
                    if(i%2==0){
                        i++;
                    }
                    else{
                        i=i+2;    
                    }
                }
                else if(record[i]!='X'){
                    i++;
                }
                else if(i>=19){
                    i++;
                }
            }
            break;
        case 2://RNG Mode
            for(int i=1;i<=19;i++){
        	if(i%2==1){ 
            	record[i]=shotrng();  
        	}
        	else{
            	if (record[i-1]==10){
                	continue;
            	}
            	else{
            	    spare=sparerng();
            	    if (spare==1){
            	        record[i]=10-record[i-1];
            	    }
                	else{
                	    record[i]=rand()%(10-record[i-1]+1)-1;
                	}
            	}
        	}
    	}
    
    	record[19]=shotrng();
        if(record[19]==10){
            record[20]=shotrng();
            if(record[20]==10){
                record[21]=shotrng();
            }
            else{
                spare=sparerng(); //20,21
            	if (spare==1){
            	    record[21]=10-record[20];
            	}
                else{
                record[21]=rand()%(10-record[20]+1)-1;
                }
            }
        }
        else{ //19, 20
        	spare=sparerng(); 
            if (spare==1){
            	record[20]=10-record[19];
            }
            else{
                record[20]=rand()%(10-record[19]+1)-1;
            }
           	if(record[19]+record[20]==10){
            	record[21]=shotrng();
           	}
           	else{
               	record[21]=0;
           	}	
        }
    
        
    	for(int i=1;i<22;i++){
        	if(i<19){
        	    if(i%2==1 && record[i]==10){
        	        record[i]+=30;
        	        record[i+1]=-48;
        	    }
        	    else if(i%2==0 && (record[i]+record[i-1]==10)){
        	        record[i]=-1;
        	    }
        	}
        	else{
        	    if(i==19){
        	        if(record[i]==10){
        	            record[i]+=30;
        	        }
        	    }
        	    if(i==20){
        	        if(record[i-1]==40 && record[i]==10){
        	            record[i]+=30;
        	        }
        	        else if(record[i]+record[i-1]==10){
        	            record[i]=-1;
        	        }
        	    }
        	    
        	    if(i==21){
        	        if(record[i-2]==40){
        	            if(record[i-1]==40 && record[i]==10){
        	                record[i]+=30;
        	            }
        	            else if(record[i-1]+record[i]==10){
        	                record[i]=-1;
        	            }
        	        }
        	        else if(record[i-1]==-1){
        	            if(record[i]==10){
        	                record[i]+=30;
        	            }
        	        }
        	    }
        	}
    	}
            for(int i=1;i<22;i++){
    	        record[i]+=48;
    	    }   
            break;
            default:
            	continue;
        }

    
    cout<<"Record: "<<"\t";//Print records
    for(int j=1;j<22;j++){
        cout<<record[j]<<" ";
        if((j%2==0) && (j<19)){
            cout<<"\t";
        }
        else if (j>=19){
            continue;
        }
    }
    cout<<endl;
    
    
    while((n<22)){//Translating to pin count
        if ((record[n]=='X') && (n<19)){
            if(n%2==1){
            pin[n]=10;
            n=n+2;    
            }
            else{
                pin[n]=0;
                n++;
            }
        }
         
        else if((record[n]=='/') && (n<19)){
            if(n%2==1){
                pin[n]=0;
                n++;
            }
            else if(n%2==0){
                if(record[n-1]=='-'){
                    pin[n]=10;
                    n++;
                }
                else{
                    pin[n]=10-(record[n-1]-'0');
                    n++;    
                }
            }
        }
        else if(n<19){
            pin[n]=record[n]-'0';
            if(record[n]=='-'){
                pin[n]=0;
            }
            n++;
        }
        else if(n>=19){
            if((record[n]=='X')){
                if((n==20) && (record[19]!='X')){
                    pin[n]=0;
                }
                else if((n==21) && (record[19]=='X') && (record[20]!='X')){
                    pin[n]=0;
                }
                else{
                    pin[n]=10;
                }
            }
            else if(record[n]=='-'){
                pin[n]=0;
            }
            else if(record[n]=='/'){
                if(n==19){
                    pin[n]=0;
                }
                else if(record[n-1]=='-'){
                    pin[n]=10;
                }
                else if((n==21) && ((pin[19]+pin[20]==10) || (pin[19]+pin[20]<=10))){
                    pin[n]=0;
                }
                else if((n==21) && (record[19]=='X') && (record[20]=='X')){
                    pin[n]=0;
                }
                else{
                    pin[n]=10-(record[n-1]-'0');    
                }

            }
            else{
                pin[n]=record[n]-'0';
            }
            if((pin[19]+pin[20]!=10) && (((record[19]!='X') && (record[20]!='X')) && ((record[19]!='/') && (record[20]!='/')))){
                pin[21]=0;
            }
            n++;
        }
    }
    
    
    cout<<"Pins: "<<"\t"<<"\t";
    for(int j=1;j<22;j++){//Print pin count
        cout<<pin[j]<<" ";
        if((j%2==0) && (j<19)){
            cout<<"\t";
            }
        else if (j>=19){
            continue;
        }
    }
    cout<<endl;
    
    
    for(int c=1;c<=20;c++){//Error detector
        if((c%2==1) && (c<19)){
            if(record[c]=='/'){
                flag[(c+1)/2]=1;
                mark=1;
            }
        }
        else if((c%2==0) && (c<19)){
            if(record[c]=='X'){
                flag[c/2]=1;
                mark=1;
            }
            else if(pin[c]+pin[c-1]>10){
                flag[c/2]=2;
                mark=1;
            }
        }
        else if(c==19){
            if(record[19]=='/'){
                flag[10]=1;
                mark=1;
            }
            else if(record[19]=='X'){
                if((record[20]!='X') && (pin[20]+pin[21]>10)){
                    flag[10]=2;
                    mark=1;
                }
                else if(record[20]=='/'){
                    flag[10]=1;
                    mark=1;
                }
                else if (((record[20]!='X') && ((record[21])=='X'))){
                    flag[10]=1;
                    mark=1;
                }
                else if (((record[20]=='X') && ((record[21])=='/'))){
                    flag[10]=1;
                    mark=1;
                }
            }
            else if(record[19]!='X'){
                if(record[20]=='X'){
                    flag[10]=1;
                    mark=1;
                }
                else if((pin[19]+pin[20]>10)){
                    flag[10]=2;
                    mark=1;
                }
                else if(((pin[19]+pin[20]<10) && ((record[20]!='X') && (record[20]!='/')) && ((record[21]!='0') && (record[21]!='-'))) || ((pin[19]+pin[20]!=10) && (record[21]=='X'))){
                    flag[10]=1;
                    mark=1;
                }
            }
        }
    }
    for (int f=1;f<=10;f++){
        if(flag[f]==1){
           cout<<"Incorrect mark(s) in Frame "<<f<<endl; 
        }
        else if(flag[f]==2){
           cout<<"Incorrect pin total in Frame "<<f<<endl; 
        }
    }
    
    if(mark==1){
        continue;
    }
    
    
    cout<<"Frame Score: "<<"\t";
    for(int s=1;s<=10;s++){//Score per frame, Total score
        current=0;
        if((record[2*s-1]=='X') && ((2*s-1)<19)){
            if((record[2*s+1]=='X') && ((2*s-1)<17)){
                current=20+pin[2*s+3];
                score[s]=score[s-1]+current;
            }
            else if(((2*s-1)==17) && (record[2*s+1]=='X')){
                current=20+pin[2*s+2];
                score[s]=score[s-1]+current;
            }
            else if((record[2*s+1]!='X') && ((2*s-1)<19)){
                current=10+pin[2*s+1]+pin[2*s+2];
                score[s]=score[s-1]+current;
            }
        }
        
        else if((record[2*s]=='/')){
            current=10+pin[2*s+1];
            score[s]=score[s-1]+current;
        }
        
        else if(((2*s-1)<19)){
            current=pin[2*s-1]+pin[2*s];
            score[s]=score[s-1]+current;
        }
        
        else if(((2*s-1)==19)){
            if(record[19]=='X'){
                if(record[20]=='X'){
                    current=20+pin[21];
                    score[s]=score[s-1]+current;
                }
                else{
                    current=10+pin[20]+pin[21];
                    score[s]=score[s-1]+current; 
                    }
                }
            else if((record[20]=='/')){
            current=10+pin[21];
            score[s]=score[s-1]+current;
            }
            else{
            current=pin[19]+pin[20];
            score[s]=score[s-1]+current;
            }
        }
        cout<<current<<"\t";//Print frame score
    }
    cout<<endl;
    
    
    cout<<"Total Score: "<<"\t";
    for(int t=1;t<=10;t++){//Print total score
        cout<<score[t]<<"\t";
    }
    cout<<endl;
    
    
    
    }
    return 0;
}
