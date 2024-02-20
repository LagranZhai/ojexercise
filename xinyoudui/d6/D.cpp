//PD
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=500;
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int T;cin>>T;
    srand(time(nullptr));
    while(T--){
        int n,m;
        cin>>n>>m;
        std::vector<int> g[maxn];
        int dp[maxn]{},r[maxn]{};
        for(int i{};i<n;i++)r[i]=rand()%998244353;
        int u,v;
        for(int i{};i<m;i++){
            cin>>u>>v;
            g[v].push_back(u);
            dp[u]+=r[v];
        }
        bool flag=0;
        for(int i{};i<n;i++){
            if(g[i].empty())continue;
            int t=dp[g[i][0]];
            for(auto a:g[i]){
                if(t!=dp[a]){
                    flag=1;break;
                }
            }
        }
        if(flag)cout<<"No\n";
        else cout<<"Yes\n";
    }
    cout.flush();
    return 0;
}