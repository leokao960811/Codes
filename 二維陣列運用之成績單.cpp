#include <iostream>
using namespace std;
int main()
{
	
	int n=6,k=5;
	int a[6][5]={{86,92,57,81,65},{96,98,81,67,74},{91, 40, 92, 78, 67},{68, 88, 50, 89, 78},{87, 96, 70, 62, 68},{84, 75, 94, 56, 90}};
	int sum;
	cout<<"�y��\t���\t�^��\t�ƾ�\t�۵M\t���|\t�`��\t����"<<endl;
	for(int x=0;x<n;x++){
		sum=0; //�k�s 
		cout<<x+1<<"\t"; //��X�y�� 
		for(int y=0;y<k;y++){
		cout<<a[x][y]<<"\t"; //���� 
		sum=sum+a[x][y]; //�`���Z(�`�N�Y��) 
		}
		cout<<sum<<"\t"<<sum/5.0; //��X�`���Z�M���� 
		cout<<endl;
   } 	
	
		
 return 0;
}
