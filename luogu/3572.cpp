#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+6;
int n,d[maxn],qq,dp[maxn],k[30],q[maxn];
int front=0,back=0;
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>d[i];
	}
	cin>>q;
	for(int i=1;i<=q;i++){
		cin>>k[i];
	}
	for(int j=1;j<=qq;j++){
		memset(dp,0x7f,sizeof dp);
		dp[1]=0;
		//deque<int > q;
		q[1]=1,head=1,tail=1;
		for(int i=2;i<=n;i++){
			while(!q.empty()&&i>k[j]&&q.front()<i-k[j])q.pop_front();
			dp[i]=min(dp[i],dp[q.front()]+(d[i]>=d[q.front()]));
			while(!q.empty()&&dp[q.back()]>dp[i])q.pop_back();
			while(!q.empty()&&dp[q.back()]==dp[i]&&d[q.back()]<d[i])q.pop_back();
			q.push_back(i);
			
//			for(int l=1;l<=k[j]&&l<=i;l++){
//				dp[i]=min(dp[i],dp[i-l]+(d[i]>=d[i-l]));
//			}
		}
		cout<<dp[n]<<endl;
		
	}
	
	return 0;
}
