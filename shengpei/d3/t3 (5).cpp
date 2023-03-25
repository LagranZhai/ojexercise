#include<iostream>
#include<string.h>
using namespace std;
using ll= long long;
int dp[20][20];
int a[20];
ll cnt=0;
bool dfs(int i,int j,int n){
	if(i==n&&j==n){
		if(dp[i][j]==0){
			cnt++;
//			for(int i=1;i<=n;i++){
//				for(int j=1;j<=n;j++){
//					cout<<dp[i][j]<<' ';
//				}
//				cout<<'\n';
//			}
//			cout<<'\n';
			return 1;
		}
	}
	if(i+1<=n&&dp[i+1][j]==0){
		if(dfs(i+1,j,n))return 1;
	}
	if(j+1<=n&&dp[i][j+1]==0){
		if(dfs(i,j+1,n))return 1;
	}
	return 0;
}
void gene(int n,int i){
	if(i==n){
		for(int j=1;j<=n;j++){
			if(!a[j]){
				a[j]=1;
				dp[i][j]=1;
				if(dp[1][1]==0)dfs(1,1,n);		
				a[j]=0;
				dp[i][j]=0;
			}
		}
		return;
	}
	for(int j=1;j<=n;j++){
		if(!a[j]){
			a[j]=1;
			dp[i][j]=1;
			gene(n,i+1);
			a[j]=0;
			dp[i][j]=0;
		}
	}	
}
void solve(int n){
	gene(n,1);
	cout<<cnt/<<endl;
}
int main(){
	ios::sync_with_stdio(false);
	int t;int n;
	//cin>>t;
	for(int i=1;i<=4;i++){
		//cin>>n;
		memset(a,0,sizeof a);
		memset(dp,0,sizeof dp);
		cnt=0;
		solve(i);
	}
	return 0;
}
