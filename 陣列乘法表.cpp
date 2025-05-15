#include <iostream>
using namespace std;

int main(){
	int a[9][9];
	cout<<"X\t";
	
	for(int k=0;k<9;k++){
		cout<<k+1<<"\t";
	}
	cout<<endl;
	for(int i=0;i<9;i++){
			cout<<i+1<<"\t";
		for(int j=0;j<9;j++){
			a[i][j]=(i+1)*(j+1);
			cout<<a[i][j]<<"\t";
		}
		cout<<endl;
	}
  return 0;
}

