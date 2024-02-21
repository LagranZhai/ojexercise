//PD
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=2e5,maxm=4e5;
std::vector<int> g1[maxn],g2[maxn];
int vis[maxn];
std::vector<int> cc[maxn];
int nc{};
int in[maxn];
int n,m;
void dfs(int x,int i){
    if(vis[x])return ;
    cc[i].push_back(x);
    vis[x]=1;
    for(auto to:g2[x]){
        dfs(to,i);
    }
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    int u,v;
    for(int i{};i<m;i++){
        cin>>u>>v;
        g1[u].push_back(v);
        in[v]++;
        g2[u].push_back(v);
        g2[v].push_back(u);
    }
    int ans{0};
    for(int i{1};i<=n;i++){
        if(vis[i])continue;
        dfs(i,++nc);
        std::queue<int> q;
        for(int v:cc[nc]){
            if(!in[v])q.push(v);
        }
        while(!q.empty()){
            int cur{q.front()};q.pop();
            for(int v:g1[cur]){
                in[v]--;
                if(!in[v])q.push(v);
            }
        }
        bool flag{};
        for(int v:cc[nc]){
            if(in[v])flag=1;
        }
        if(flag)ans+=cc[nc].size();
        else ans+=cc[nc].size()-1;
    }
    cout<<ans;
    cout<<std::endl;
    return 0;
}