#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int maxn=8e3;
ll a[maxn+100],n,dp[maxn+10][maxn+10];
const ll M=998244353;
ll qpow(ll a,int b){
	ll ans=1;
	while(b>0){
		if(b&1)ans*=a;
		ans%=M;
		b>>=1;
		a=a*a%M;
	}
	return ans;
}
ll niyuan(ll o){
	return qpow(o,M-2);
}
int main(){
	freopen("frog.in","r",stdin);
	ios::sync_with_stdio(false);
	cin>>n;
	ll sum=1;
	int flag1;
	for(int i=1;i<=n-1;i++){
		cin>>a[i];
		sum*=a[i];
		sum%=M;
	}
	dp[0][1]=sum;
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			for(int k=1;k<=a[j];k++){
				dp[i][j+k]+=dp[i-1][j]*niyuan(a[j]);
				dp[i][j+k]%=M;
			}
		}
	}
	ll fenmu=sum*sum%M;fenmu%=M;
	ll fenzi=0;
	for(int i=1;i<=n-1;i++){
		ll t=dp[i][n]*dp[i][n];
		t%=M;
		fenzi+=t;
		fenzi%=M;
	}
	ll ans=niyuan(fenmu)%M;
	ans*=fenzi;
	ans%=M;
	ans%=M;
	cout<<ans<<endl;
	return 0;
}
