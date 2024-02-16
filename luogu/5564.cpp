//P5564
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=100*2,maxm=2000*2,p=998244353;
int a[maxn][maxm];
int s[maxn];
int dp[maxn][maxn*2],g[maxn][maxn];
int n,m;
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    int ans{1};
    for(int i{1};i<=n;i++){
        for(int j{1};j<=m;j++){
            cin>>a[i][j];
            s[i]+=a[i][j];s[i]%=p;
        }
        ans=ans*(s[i]+1)%p;
    }
    for(int i{1};i<=m;i++){
        std::fill(dp[0],dp[0]+maxn*maxn*2,0);
        dp[0][n]=1;
        for(int j{1};j<=n;j++){
            for(int k{n-j};k<=j+n;k++){
                if(k>0ll){
                    dp[j][k]+=dp[j-1][k-1]*a[j][i]%p;dp[j][k]%=p;
                }
                if(k<2*n){
                    dp[j][k]+=dp[j-1][k+1]*((s[j]-a[j][i]+p)%p)%p;dp[j][k]%=p;
                }
                dp[j][k]+=dp[j-1][k];dp[j][k]%=p;
            }
        }
        for(int k{1};k<=n;k++){
            ans=(ans+(p-dp[n][k+n]))%p;
        }
    }
    cout<<ans-1<<"\n";
    cout.flush();
    return 0;
}