#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e6,logw=21,p=1e9+7;
int dp[maxn+10][logw];
int main(){
    ios::sync_with_stdio(false);
    int n;
    cin>>n;
    for(int i{0};i<logw;i++)dp[0][i]=1;
    int ans{0};
    for(int i{1};i<=n;i++){
        for(int j{1};j<logw&&i>=(1<<j);j++){
            ans=j;
            for(int k{1};k<=i/(1<<j);k++){
                if(i-k*(1<<j)>0)dp[i][j]+=dp[i-k*(1<<j)][j-1];
                else{
                    dp[i][j]++;
                }
            }
            for(int k{j};k<logw&&i>=(1<<k);k++){
                dp[i][k]+=dp[]
            }
        }
    }
    // int ans{0};
    // for(int i{0};i<logw;i++){
    //     ans+=dp[n][i];
    //     cout<<dp[n][i]<<"\n";
    // }
    cout<<dp[n][ans]<<std::endl;
    cout<<std::flush;
    return 0;
}