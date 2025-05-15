#include <iostream>
using namespace std;

int main(){
	int a,b,c,d,x;
	
	cin>>c>>d;
	
	for(a=1;a<=c;a++){
		for(b=1;b<=d;b++){
			x=a*b;
			cout<<a<<"x"<<b<<"="<<x<<"\t";	
		}	
		cout<<endl;
}

  return 0;
}

