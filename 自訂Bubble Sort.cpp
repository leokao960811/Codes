#include <iostream>
using namespace std;
int main()
{
int n,t,b;
cout<<"��J�}�C������: ";
cin>>n;
int a[n];
cout<<"��J�}�C����: ";
for(b=0;b<n;b++){
	cin>>a[b];
}

for (int i=1;i<n;i++){
	
	for(int k=0;k<n;k++){
		cout<<a[k]<<" ";
	}
	cout<<endl;
	
	for(int j=0;j<n-i;j++){
		
	if (a[j]>a[j+1]){
	t=a[j+1];
	a[j+1]=a[j];
	a[j]=t;
}
	
}

}
	
cout<<"�ƧǦn���}�C��: "<<endl;	
for(int k=0;k<n;k++)
	cout<<a[k]<<" ";
cout<<endl;
 	

 return 0;
}

