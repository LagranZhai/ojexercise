#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	if(n==1){
		if(m==1)cout<<1<<endl;
		else swap(n,m);
	}
	if(n!=1){
		unsigned long long ans=1ull*(n-1)*m+m-1;
		cout<<ans<<endl;
	}
	return 0;
}
