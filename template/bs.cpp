#include<bits/stdc++.h>
using namespace std;
int a[100];
int lb(int l,int r,int x){
	int mid=l+((r-l)>>1);
	while(l<=r){
		mid=l+((r-l)>>1);
		if(a[mid]<x){
			l=mid+1;
		}
		else r=mid-1;
	}
	return l;
}
int main(){
	srand(time(0));
	for(int i=1;i<=1000;i++){
		for(int j=0;j<50;j++){
			if(j>0){
				if(rand()%3==2){
					a[j]=a[j-1];
				}
			}
			a[j]=rand();
		}
		sort(a,a+50);
		int x=a[rand()%50];
		int c=lower_bound(a,a+50,x)-a;
		int b=lb(0,49,x);
		if(c!=b)cout<<"err"<<endl;
	}
	return 0;
}
