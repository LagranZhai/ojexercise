#include<iostream>
#include<string.h>
#include<queue>
using namespace std;
const int maxn=2000+10;
int n,m,p;
int val[maxn][maxn],sum[maxn][maxn];
int pri[maxn],mm[maxn];
int dp[maxn][maxn],h[maxn][maxn];
int getnxt(int j,int k){
	if(((j-k+100*n)%n?(j-k+100*n)%n:n)<=0)std::cerr<<j;
	return ((j-k+100*n)%n>0)?((j-k+100*n)%n):n;
}
using  pii=std::pair<int,int> ;
deque<pii> q[maxn];
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
			sum[i][j]=sum[i-1][getnxt(j,1)]+val[i][j];
		}
	}
	for(int i{1};i<=n;i++){
		q[i%n].push_back({-pri[i],0});
	}
	std::cerr<<"a";
	for(int i{1};i<=m;i++){
		for(int j{1};j<=n;j++){
			std::cerr<<i<<" "<<j<<"\n";
			while((!q[((j-i)+n)%n].empty())&&q[((j-i)+n)%n].front().second<i-p){
				q[((j-i)+n)%n].pop_front();
				cerr<<"u";
			}
			std::cerr<<i<<" "<<j<<"\n";
			if(!q[((j-i)+n)%n].empty())dp[i][j]=q[((j-i)+n)%n].front().first+sum[i][getnxt(j,1)];
			std::cerr<<i<<" "<<j<<"\n";
			while((!q[((j-i)+n)%n].empty())&&q[((j-i)+n)%n].back().first<dp[i][j]-sum[i][getnxt(j,1)]-pri[j]){
				q[((j-i)+n)%n].pop_back();
			}
			std::cerr<<i<<" "<<j<<"\n";
			q[((j-i)+n)%n].push_back({dp[i][j]-sum[i][getnxt(j,1)]-pri[j],i});
		}
	}
	int ans{0};
	std::cerr<<ans;
	for(int i{1};i<=n;i++){
		ans=std::max(ans,dp[m][i]);
	}
// 	memset(dp,0xc0,sizeof dp);
// 	dp[0]=0;
//     //memset(mm,0xc0,sizeof mm);
// //    for(int i=0;i<=n;i++){
// //        dp[0][i]=0;
// //    }
// //	for(int i=1;i<=n;i++){
// //		dp[1]=max(dp[1],val[1][i]);
// //	}
// 	for(int i=1;i<=m;i++){
// 		for(int j=1;j<=n;j++){
// 			//dp[i][j]=mm[i-1]+val[i][j];
// 			for(int k=1;k<=p&&k<=i;k++){
// 				if(j>k){
// 					dp[i]=max(dp[i],dp[i-k]+sum[i][j]-sum[i-k][j-k]-pri[j-k]);
// 					//dp[i][j]-=pri[j-k];
// 				}
// 				else{
// 					dp[i]=max(dp[i],dp[i-k]+sum[i][j]-sum[i-k][((j-k)+2*n)%n]-pri[(j-k+2*n)%n]);
// 					//dp[i][j]-=pri[j-k+n];
// 				}
// 			}
// 		}
// 	}                                                                                             

	cout<<ans<<endl;
	return 0;
}