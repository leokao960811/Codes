#include <iostream>
using namespace std;

int main(){
	int r,c;
	cout<<"¿é¤J¦æ¡B¦C¼Æ: ";
	cin>>r>>c; 
	int a[r][c];
	cout<<"X\t";
	
	for(int k=0;k<c;k++){
		cout<<k+1<<"\t";
	}
	cout<<endl;
	
	for(int i=0;i<r;i++){
			cout<<i+1<<"\t";
		for(int j=0;j<c;j++){
			a[i][j]=(i+1)*(j+1);
			cout<<a[i][j]<<"\t";
		}
		cout<<endl;
	}
  return 0;
}

