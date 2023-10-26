#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=5000;
#define int long long
struct Edge{
    int v{0},nxt{0};
}edg[maxn*3];
int head[maxn*2],cnt{0};
void addedge(int u,int v){
    edg[++cnt].v=v;
    edg[cnt].nxt=head[u];
    head[u]=cnt;
    return ;
}
int n;
int sum[maxn+100],mulsum[maxn+100],c[maxn+100];
int ans{0};
int dfs(int u,int f,int dep){
    c[dep]++;
    int maxdep{dep};
    for(int e{head[u]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            maxdep=std::max(maxdep,dfs(to,u,dep+1));
        }
    }
    return maxdep;
}
void solve(int u,int f){
    std::fill(sum,sum+maxn+100,0);
    std::fill(mulsum,mulsum+maxn+100,0);
    int maxdep{0};
    for(int e{head[u]};e;e=edg[e].nxt){
        int to{edg[e].v};
        std::fill(c,c+maxdep+100,0);
        maxdep=dfs(to,u,1);
        for(int i{1};i<=maxdep;i++){
            ans+=c[i]*mulsum[i];
            mulsum[i]+=c[i]*sum[i];
            sum[i]+=c[i];
        }
    }
    for(int e{head[u]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            solve(to,u);
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin>>n;
    int u,v;
    for(int i{1};i<n;i++){
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    solve(1,0);
    cout<<ans<<std::endl;
    cout<<std::flush;
    return 0;
}