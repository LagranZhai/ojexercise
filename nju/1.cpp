#include<bits/stdc++.h>
using std::cin;
using std::cout;
// using ll=long long;
#define int long long
std::vector<std::array<std::vector<int>,5>> dp;
int cnt{};
void dfs(int n,int r){
    if(r==1){
        dp[n][r].push_back(-1);
        return ;
    }
    for(int i{0};i<=std::sqrt(n);i++){
        cnt++;
        if(dp[n-i*i][r-1].empty()){
            dfs(n-i*i,r-1);
            if(dp[n-i*i][r-1][0]==-1)continue;
        }
        if(dp[n-i*i][r-1][0]==-1)continue;
        for(auto a:dp[n-i*i][r-1]){
            dp[n][r].push_back(a);
        }
        dp[n][r].push_back(i);
        break;
    }
    if(dp[n][r].empty())dp[n][r].push_back(-1);
    return ;
}
signed main(){
    int n=114514191;
    // cin>>n;
    dp.reserve(n+1);
    for(int i{0};i*i<=n;i++){
        dp[i*i][1].push_back(i);
    }
    dp[0][2]={0,0};dp[0][3]={0,0,0};
    dfs(n,4);
    // for(int i{1};i<=n;i++){
    //     if(i%10000==0)cout<<i<<std::endl;
    //     dfs(i,4);
    //     auto& ans=dp[i][4];      
    //     int res{0};  
    //     for(auto a:ans){
    //         res+=a*a;
    //     }
    //     if(res!=i){
    //         cout<<"a"<<i<<std::endl;
    //         break;
    //     }
    // }
    auto& ans=dp[n][4];    
    // cout<<"b"<<std::endl;
    std::sort(ans.begin(),ans.end());
    // cout<<ans.size()<<std::endl;
    for(auto it{ans.rbegin()};it!=ans.rend();it++){
        cout<<(*it)<<" ";
    }
    cout<<cnt<<std::endl;
    return 0;
}