#include<iostream>
using namespace std;
long long dp[10000009],u[10009],v[10009];
int t,m;
int main(){
	ios::sync_with_stdio(false);
	cin>>t>>m;
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i];
	}
	for(int i=1;i<=m;i++){
		for(int j=u[i];j<=t;j++){
			dp[j]=max(dp[j],dp[j-u[i]]+v[i]);
		}		
	}
	cout<<dp[t];
	return 0;
}
