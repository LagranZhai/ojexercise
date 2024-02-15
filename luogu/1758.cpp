//P1758
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=510,p=1024523;
int n,m;
std::string a{"$"},b{"%"};
int dp[maxn][maxn],tmp[maxn][maxn];
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    std::string t;
    cin>>t;
    a+=t;
    cin>>t;
    b+=t;
    tmp[0][0]=1;
    for(int i{1};i<=n+m;i++){
        std::fill(dp[0],dp[0]+maxn*maxn,0);
        for(int j{0};j<=std::min(i,n);j++){
            for(int k{0};k<=std::min(i,n);k++){
                if(a[j]==a[k]&&j>0&&k>0)dp[j][k]=(dp[j][k]+tmp[j-1][k-1])%p;
                if(a[j]==b[i-k]&&j>0&&k<i)dp[j][k]=(dp[j][k]+tmp[j-1][k])%p;
                if(b[i-j]==a[k]&&k>0&&j<i)dp[j][k]=(dp[j][k]+tmp[j][k-1])%p;
                if(b[i-j]==b[i-k]&&j<i&&k<i)dp[j][k]=(dp[j][k]+tmp[j][k])%p;
            }
        }
        for(int j{0};j<=n;j++){
            for(int k{0};k<=n;k++){
                tmp[j][k]=dp[j][k];
            }
        }
    }
    cout<<dp[n][n]<<"\n";
    cout.flush();
    return 0;
}