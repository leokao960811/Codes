#include <iostream>
#include <cstdlib> //rand()%n+1
#include <ctime> //srand(time(NULL))
using namespace std;

int shotrng(){
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

     if(v < 25) return 0;
else return 1;
}

int main(int argc, char**argv) {
		
    srand(time(NULL));
    
    while (true){
    	cout<<"Press ENTER to generate: ";
		cin.get();
		int record[22]={0};
        int spare=0;
        
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
        	cout<<char(record[i]+48)<<" ";  	
        	
        	
        	if((i%2==0) && (i<19)){
            	cout<<"\t";
        	}
        	else if (i>=19){
            	continue;
        	}
    	}
    	cout<<endl;
    	
        //for(int i=1;i<22;i++){
    	    //cout<<record[i]<<" ";
    	    //if((i%2==0) && (i<19)){
            	//cout<<"\t";
        	//}
        	//else if (i>=19){
            	//continue;
        	//}
    	//}
    	//cout<<endl;
    }
    
    
	return 0;
}
