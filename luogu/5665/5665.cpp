#include<iostream>
#include<string.h>
using namespace std;
const int maxn=5010;
int n,type;
long long a[maxn],dp[maxn][maxn],b[maxn][maxn];
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>type;
	if(type==0){
		for(int i=1;i<=n;i++){
			cin>>a[i];
			a[i]+=a[i-1];
		}
	}
	//cout<<"1"<<endl;
	memset(dp,0x7f,sizeof dp);
	for(int i=1;i<=n;i++){
		for(int j=i-1;j>=0;j--){
			long long t=(a[i]-a[j]);
			long long temp=t*t;
			if(j==0){
				dp[i][0]=temp;
			}
			for(int k=j-1;k>=0;k--){
				if(t<b[i][j])break;
				dp[i][j]=dp[j][k]+temp;
				b[i][j]=temp;
			}
		}
	}
	long long ans;
	for(int i=0;i<=n-1;i++){
		ans=min(ans,dp[n][i]);
	}
	cout<<ans;
	return 0;
}
