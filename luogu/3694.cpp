#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::ios;
constexpr int maxn=1e5,maxm=20;
#define int long long
int sum[maxm+10][maxn+10];
int cnt[maxn*2];
int n,m;
int dp[(1ll<<(maxm+1))];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    int t;
    for(int i{1};i<=n;i++){
        cin>>t;
        cnt[t]++;
        for(int j{1};j<=m;j++){
            if(j!=t)sum[j][i]=sum[j][i-1];
            else sum[j][i]=sum[j][i-1]+1;
        }
    }
    std::fill(dp,dp+(1ll<<(maxm+1)),std::numeric_limits<int>::max());
    dp[0]=0;
    for(int S{1};S<(1ll<<m);S++){
        int tot{0};
        for(int i{0};i<m;i++){
            if((1ll<<i)&S){
                tot+=cnt[i+1];
            }
        }
        for(int i{0};i<m;i++){
            if((1ll<<i)&S){
                dp[S]=std::min(dp[S],dp[S^(1ll<<i)]+cnt[i+1]-(sum[i+1][tot]-sum[i+1][tot-cnt[i+1]]));
            }
        }
    }
    cout<<dp[(1ll<<m)-1]<<"\n";
    cout.flush();
    return 0;
}