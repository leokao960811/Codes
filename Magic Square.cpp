#include <iostream>
using namespace std;
int main(){
	
	int n;
	cin>>n;
	int ma[n+1][n+1]{0};
	int i,j,no=1;
	
	i=(n+1)/2;
	j=1;
	ma[i][j]=no;
	
	for(no=2;no<=n*n;no++){
		i++;
		if (i>n) i=1;
		j--;
		if (j<1) j=n;
		
		if(ma[i][j]!=0){
			i--;
			if(i<1) i=i+n;
			j=j+2;
			if(j>n) j=j-n;
		}
		ma[i][j]=no;
	}
	
	for(j=1;j<=n;j++){
		for(i=1;i<=n;i++){
			cout<<ma[i][j]<<"\t";
		}
		cout<<endl;
	}
	
	
	return 0;
}

