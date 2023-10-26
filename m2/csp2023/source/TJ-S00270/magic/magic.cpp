#include<bits/stdc++.h>
using namespace std;
int main(){
	freopen("magic.in","r",stdin);
	freopen("magic.out","w",stdout);
	unsigned long long cur=1,ans=1,n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cur=(cur*3)%1000000007;
		ans+=cur;
		ans%=1000000007;
	}
	cout<<ans;
}
