#include<bits/stdc++.h>
using namespace std;
const int maxt=100;
const int maxn=100;
const int maxp=1e4;
int p[maxt*2][maxn*2];
int dp[maxp*2];
int main(){
    ios::sync_with_stdio(false);
    int t,n,m;
    cin>>t>>n>>m;
    for(int i=1;i<=t;i++){
        for(int j=1;j<=n;j++){
            cin>>p[i][j];
        }
    }
    int ans=m;
    for(int i=2;i<=t;i++){
        for(int j=0;j<=ans;j++)dp[j]=ans;
        for(int j=1;j<=n;j++){
            for(int k=ans-p[i-1][j];k>=0;k--){              
                dp[k]=max(dp[k],dp[k+p[i-1][j]]+p[i][j]-p[i-1][j]);
            }
        }
        for(int j=0;j<=maxp;j++)ans=max(ans,dp[j]);
        //cout<<ans<<endl;
    }
    cout<<ans<<endl;
    return 0;
}
