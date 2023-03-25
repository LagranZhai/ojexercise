#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int maxn=8e3;
ll a[maxn+100],n,dp[maxn+10][maxn+10],b[maxn+100];
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
	//freopen("frog.in","r",stdin);
	ios::sync_with_stdio(false);
	cin>>n;
	ll sum=1;
	int flag1;
	for(int i=1;i<=n-1;i++){
		cin>>a[i];
		b[i]=niyuan(a[i]);
		sum*=a[i];
		sum%=M;
	}
	dp[0][1]=sum;
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			ll de=dp[i-1][j]*b[j];
			dp[i][j+1]+=de;
			dp[i][j+1]%=M;
			dp[i][j+a[j]+1]-=de;
			dp[i][j+a[j]+1]%=M;	
		}
		for(int j=i;j<=n;j++){
			dp[i][j]+=dp[i][j-1];
			dp[i][j]%=M;
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
