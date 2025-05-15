#include <iostream>
#include <cstdlib> //rand()%n+1
#include <ctime> //srand(time(NULL))
using namespace std;
int main() {
	
	while (true){
    int i,j;
    int a,b;
    int n,m,l; //n=row, m=column, l=mine
    int flag=2;
    
    cout<<"Input minefield Height, Width, Minecount"<<endl;
    cout<<"(Input -1 to quit):";
    
    cin>>n>>m>>l;
    if((n==-1) || (m==-1) || (l==-1)){
        return false;
    }
    else if(l>(n*m)){ //check valid minecount
    	cout<<"Too many mines!"<<endl;
    	continue;
	}
    else{
    char board[1024][1024]; //don't initalize size based on inputs, learned that the hard way
    srand(time(NULL));

    for (i=0;i<=m+1;i++){ //initialize array
        for (j=0;j<=n+1;j++){
            board[i][j]='.';
        }
    }
    
    for(int c=1;c<=l;c++){//mine generate 
        a=rand()%m+1;
        b=rand()%n+1;
        if(board[a][b]=='.'){
            board[a][b]='#';
        }
        else{
            c--;
        }
    }
        
    
            
    
    //for (i=0;i<=m+1;i++){ //debug
        //for (j=0;j<=n+1;j++){
            //cout<<board[i][j]<<" ";
        //}
        //cout<<endl;
    //}
    //cout<<endl;
    
    
    for (i=1;i<=m;i++){ //checker
        for (j=1;j<=n;j++){
            flag=2;
            if(board[i][j]=='#'){
                continue;
            }
            if(board[i-1][j-1]=='#'){
                flag++;
                }
            if(board[i][j-1]=='#'){
                flag++;
                }
            if(board[i+1][j-1]=='#'){
                flag++;
                }
            if(board[i-1][j]=='#'){
                flag++;
                }
            if(board[i+1][j]=='#'){
                flag++;
                }
            if(board[i-1][j+1]=='#'){
                flag++;
                }
            if(board[i][j+1]=='#'){
                flag++;
                }
            if(board[i+1][j+1]=='#'){
                flag++;
                }
                
            if(flag>2){
                board[i][j]=board[i][j]+flag;    
            }
        }
    }
    
    for (i=1;i<=m;i++){ //print board
        for (j=1;j<=n;j++){
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
    
    cout<<endl;
	    }
	}
    return 0;
}

