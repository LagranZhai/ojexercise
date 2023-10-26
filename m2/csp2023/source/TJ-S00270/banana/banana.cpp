#include<bits/stdc++.h>
using namespace std;
int main(){
	freopen("banana.in","r",stdin);
	freopen("banana.out","w",stdout);
	long long d,n,k,ms[100],dp[1001][20],a[1002];
	scanf("%ld",&d);
	int ans[d+1];
	for(int i=0;i<d+1;i++){
		ans[i]=0;
	}
	for(int o=0;o<d;o++){
		int msn=0;
		scanf("%ld%ld",&n,&k);
		for(int i=1;i<=n;i++){
			scanf("%ld",&a[i]);
		}
		for(int i=1;i<=sqrt(k);i++){
			if(k/i*i==k){
				msn++;
				ms[msn]=i;
			}
		}
		for(int i=0;i<=n;i++){
			for(int j=0;j<=msn;j++){
				dp[i][j]=0;
			}
		}
		for(int i=1;i<=n;i++){
			if(k/a[i]*a[i]==k){
				for(int j=1;j<=msn;j++){
					if(a[i]==ms[j]){
						dp[i][j]++;
					}
					dp[i][j]+=dp[i-1][j];
					int index;
					for(int i=1;i<=msn;i++){
						if(k/a[i]==ms[i]){
							index=i;
							break;
						}
					}
					dp[i][j]+=dp[i-1][index];
			}	
			}
		}
		ans[o]=dp[n][msn];
	}
	for(int i=0;i<d;i++){
		cout<<ans[i]<<endl;
	}
}
