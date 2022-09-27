#include<bits/stdc++.h>
using namespace std;
const int maxn=1000+10;
int n,m,p;
int val[maxn][maxn],sum[maxn][maxn];
int pri[maxn],mm[maxn];
int dp[maxn][maxn];
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m>>p;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>val[j][i];
		}
	}
	for(int i=1;i<=n;i++)cin>>pri[i];
	for(int i=1;i<=m;i++){
		//sum[i-1][0]=val[i-1][n];
		for(int j=1;j<=n;j++){
			//if(j==1)sum[i][j]=val[i-1][n];
			sum[i][j]=sum[i-1][j-1]+val[i][j];
		}
	}
	memset(dp,0xc0,sizeof dp);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			dp[i][j]=mm[i-1]+val[i][j];
			for(int k=1;k<=min(i,p);k++){
				if(j>k){
					dp[i][j]=max(dp[i][j],max(dp[i-k][(j-k)],mm[i-k-1])+sum[i][j]-sum[i-k][j-k]-pri[j-k]);
					//dp[i][j]-=pri[j-k];
				}
				else{
					dp[i][j]=max(dp[i][j],max(dp[i-k][(j-k)+n],mm[i-k-1])+sum[i][j]+sum[i-j][n]-sum[i-k][(j-k)+n]-pri[j-k+n]);
					//dp[i][j]-=pri[j-k+n];
				}
			}
			mm[i]=max(mm[i],dp[i][j]);
		}
	}                                                                                             
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			cout<<dp[i][j]<<" ";
			
			}
			cout<<endl;
		}
		
	cout<<mm[m]<<endl;
	return 0;
}
