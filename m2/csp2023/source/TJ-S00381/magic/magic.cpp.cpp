#include<bits/stdc++.h>
using namespace std;
long long n,sum,base=1;
signed main(){
	freopen("magic.in","r",stdin);
	freopen("magic.out","w",stdout);
	const long long m=1e9+7;
	cin>>n;
	for(int i=0;i<n;i++){
		sum+=base;
		base*=3;
		base%=m;
	}
	cout<<sum;
	return 0;
}
