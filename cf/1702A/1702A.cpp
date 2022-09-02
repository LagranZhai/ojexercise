#include<iostream>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	int a[10000];
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	int t;
	for(int i=0;i<n;i++){
		t=a[i];
		if(t<10000){
			if(t<100){
				if(t<10){
					cout<<t-1<<"\n";
				}
				else{
					cout<<t-10<<"\n";
				}
			}
			else{
				if(t<1000){
					cout<<t-100<<"\n";
				}
				else{
					cout<<t-1000<<"\n";
				}
			}
		}
		else{
			if(t<1000000){
				if(t<100000){
					cout<<t-10000<<"\n";
				}
				else{
					cout<<t-100000<<"\n";
				}
			}
			else{
				if(t<100000000){
					if(t<10000000){
						cout<<t-1000000<<"\n";
					}
					else{
						cout<<t-10000000<<"\n";
					}
				}
				else{
					if(t<1000000000){
						cout<<t-100000000<<"\n";
					}
					else{
						cout<<0<<"\n";
					}
				}
			}
		}
	}
	return 0;
}
