#include <iostream>
using namespace std;

int main() {
  int n;

  while(cin>>n){
    int score,ans=0;
    for (int i=0; i<n;i++){
      cin>>score;
      ans=ans+score;
    }
	if (ans<=59*n){
      cout<<"yes"<<endl;
    }
    else {
      cout<<"no"<<endl;
    }
  }
}

