#include<iostream>
using namespace std;
int u[101],v[101],dp[101][1001];
int main(){
	ios::sync_with_stdio(false);
	int t,m;
	cin>>t>>m;
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i];
	}
	for(int i=1;i<=m;i++){
		for(int j=0;j<u[i];j++){
			dp[i][j]=dp[i-1][j];
		}
		for(int j=u[i];j<=t;j++){
			dp[i][j]=max(dp[i-1][j],dp[i-1][j-u[i]]+v[i]);
		}
	}
	cout<<dp[m][t];
	return 0;
} 
