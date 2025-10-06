#include<bits/stdc++.h>
using std::cin,std::cout;
constexpr int maxn=static_cast<int>(2e5);
void dfs(int u,auto& child,auto& dp,auto& vmax){
    if(child[u].empty()){
        vmax[u]=dp[u]=1;
        return;
    }
    for(auto v:child[u]){
        dfs(v,child,dp,vmax);
    }
    if(u==1){
        for(auto v:child[u]){
            vmax[u]=std::max(vmax[u],vmax[v]);
        }
        return;
    }
    dp[u]=std::numeric_limits<int>::max();
    for(auto v:child[u]){
        dp[u]=std::min(dp[u],dp[v]+1);
    }
    vmax[u]=dp[u];
    for(auto v:child[u]){
        vmax[u]=std::max(vmax[u],vmax[v]);
    }
    return;
}
int main(){
    std::ios::sync_with_stdio(false);
    int T;
    cin>>T;
    while(T--){
        int n;cin>>n;
        std::vector<int> p(n+1),dp(n+1),vmax(n+1);
        std::vector<std::vector<int>> child(n+1);
        for(int i{2};i<=n;i++){
            cin>>p[i];
            child[p[i]].push_back(i);
        }
        // cout<<child[8].empty()<<std::endl;
        // dfs(1,child,dp);
        dfs(1,child,dp,vmax);
        cout<<vmax[1]<<std::endl;
    }
    return 0;
}