#include <iostream>
using namespace std;
int main()
{
	
	int n=6,k=5;
	int a[6][5]={{86,92,57,81,65},{96,98,81,67,74},{91, 40, 92, 78, 67},{68, 88, 50, 89, 78},{87, 96, 70, 62, 68},{84, 75, 94, 56, 90}};
	int sum;
	cout<<"座號\t國文\t英文\t數學\t自然\t社會\t總分\t平均"<<endl;
	for(int x=0;x<n;x++){
		sum=0; //歸零 
		cout<<x+1<<"\t"; //輸出座號 
		for(int y=0;y<k;y++){
		cout<<a[x][y]<<"\t"; //分數 
		sum=sum+a[x][y]; //總成績(注意縮排) 
		}
		cout<<sum<<"\t"<<sum/5.0; //輸出總成績和平均 
		cout<<endl;
   } 	
	
		
 return 0;
}
