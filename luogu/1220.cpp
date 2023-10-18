#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=50,inf=std::numeric_limits<int >::max();
int a[maxn*2],x[maxn*2],sum[maxn*2];
int dp[maxn+100][maxn+100][2];
int n,c;
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>c;
    for(int i{1};i<=n;i++){
        cin>>x[i]>>a[i];
        sum[i]=sum[i-1]+a[i];
    }
    std::fill(dp[0][0],dp[0][0]+(maxn+100)*(maxn+100)*2,inf);
    dp[c][c][0]=dp[c][c][1]=0;
    for(int l{2};l<=n;l++){
        for(int i{1};i+l-1<=n;i++){
            if(dp[i+1][i+l-1][0]!=inf)dp[i][i+l-1][0]=std::min(dp[i][i+l-1][0],dp[i+1][i+l-1][0]+(sum[i]+sum[n]-sum[i+l-1])*(x[i+1]-x[i]));
            if(dp[i+1][i+l-1][1]!=inf)dp[i][i+l-1][0]=std::min(dp[i][i+l-1][0],dp[i+1][i+l-1][1]+(sum[i]+sum[n]-sum[i+l-1])*(x[i+l-1]-x[i]));
            if(dp[i][i+l-2][1]!=inf)dp[i][i+l-1][1]=std::min(dp[i][i+l-1][1],dp[i][i+l-2][1]+(sum[i-1]+sum[n]-sum[i+l-2])*(x[i+l-1]-x[i+l-2]));
            if(dp[i][i+l-2][0]!=inf)dp[i][i+l-1][1]=std::min(dp[i][i+l-1][1],dp[i][i+l-2][0]+(sum[i-1]+sum[n]-sum[i+l-2])*(x[i+l-1]-x[i]));                            
        }
    }
    cout<<std::min(dp[1][n][0],dp[1][n][1])<<std::endl;
    return 0;
}