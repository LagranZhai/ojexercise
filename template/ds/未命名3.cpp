#include<bits/stdc++.h>
using namespace std;
struct A{
	int a,b;
	A(int _a=0,int _b=0):a(_a),b(_b){
	}
};
struct Cmp{
	bool operator()(const A &m,const A &n){
		return m.b>n.b;
	}
};
A arr[100];
priority_queue<A,vector<A>,Cmp> qa;
int main(){
	sort(arr,arr+10,Cmp());
	lower_bound(arr,arr+10,A(1,1),Cmp());
	return 0;
} 
