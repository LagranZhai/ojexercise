#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=300;
std::vector<int > x;
int dp[maxn*2][maxn*2][2];
int n,m;
int pos[maxn*2];
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    int t;
    x.push_back(0);
    for(int i{1};i<=n;i++){
        cin>>t;
        x.push_back(t);
    }
    std::sort(std::begin(x),std::end(x));
    for(int i{0};i<x.size();i++){
        pos[i+1]=x[i];
        // cout<<pos[i+1]<<" ";
    }
    int start=std::lower_bound(std::begin(x),std::end(x),0)-std::begin(x)+1;
    int ans{0};
    for(int num{2};num<=n+1;num++){
        std::fill(dp[0][0],dp[0][0]+(maxn*2)*(maxn*2)*2,std::numeric_limits<int>::max()/2);
        dp[start][start][0]=dp[start][start][1]=0;
        for(int l{2};l<=num;l++){
            for(int i{1};i+l-1<=n+1;i++){
                dp[i][i+l-1][0]=std::min(dp[i+1][i+l-1][0]+(pos[i+1]-pos[i])*(num-l+1),dp[i+1][i+l-1][1]+(pos[i+l-1]-pos[i])*(num-l+1));
                dp[i][i+l-1][1]=std::min(dp[i][i+l-2][1]+(pos[i+l-1]-pos[i+l-2])*(num-l+1),dp[i][i+l-2][0]+(pos[i+l-1]-pos[i])*(num-l+1));
            }
        }
        for(int i{1};i+num-1<=n+1;i++){
            ans=std::max({ans,(num-1)*m-dp[i][i+num-1][0],(num-1)*m-dp[i][i+num-1][1]});
        }
    }
    cout<<ans<<std::endl;
    return 0;
}