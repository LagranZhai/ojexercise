#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5;
long long n,d,k;
long long x[maxn],s[maxn];
long long dp[maxn];
bool solve(long long g){
	deque<int> q;
	memset(dp,0x80,sizeof dp);
	dp[0]=0ll;
	//q.push_back(0);
	long long jump;
	if(d>g)jump=d-g;
	else jump=1ll;
	//cout<<jump<<endl;
	for(int i=1;i<=n;i++){
		int t=0;	
		if(!q.empty()){
			t=q.back();
			t++;
		}
		else{
			t=i;
			while(t>=0&&x[i]-d-g<=x[t])t--;
			t++;			
		}
		//while(!q.empty()&&x[q.back()]+jump>x[i])q.pop_back();
		while(x[t]+jump<=x[i]){
			while(!q.empty()&&dp[q.back()]<dp[t])q.pop_back();
			q.push_back(t++);
		}
		//while(!q.empty()&&x[q.back()]+jump>x[i])q.pop_back();
		while(!q.empty()&&x[q.front()]+d+g<x[i])q.pop_front();
		if(!q.empty())dp[i]=dp[q.front()]+s[i];
		//else return 0;
		//cout<<i<<" "<<dp[i]<<endl;
		if(dp[i]>=k)return 1;
	}
	return 0;
}
int main(){
	ios::sync_with_stdio();
	freopen("P3957_2.in","r",stdin);
	cin>>n>>d>>k;
	long long maxs=0;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>s[i];
		if(s[i]>0)maxs+=s[i];
	}
	if(maxs<k){
		cout<<"-1"<<endl;
		return 0;
	}
	long long len=max(d,x[n]-d);
	long long l=0,r=len,mid=(l+r)/2;
	//cout<<r<<endl;
	long long ans=0;
	while(l<=r){
		mid=(l+r)/2;
		if(solve(mid)){
			ans=mid;
			r=mid-1;
		}
		else{
			l=mid+1;
		}		
	}
	cout<<ans<<endl;
	return 0;
}
