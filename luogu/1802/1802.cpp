#include<iostream>
using namespace std;
long long dp[1003][1003],l[1003],w[1003],u[1003];
int n,x;
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>x;
	for(int i=1;i<=n;i++){
		cin>>l[i]>>w[i]>>u[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<u[i];j++){
			dp[i][j]=dp[i-1][j]+l[i];
		}
		for(int j=u[i];j<=x;j++){
			dp[i][j]=max(dp[i-1][j]+l[i],dp[i-1][j-u[i]]+w[i]);
		}		
	}
	cout<<dp[n][x]*5;
	return 0;
}
