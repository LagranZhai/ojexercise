#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=2e5;
struct Graph{
    struct Edge{
        int v,nxt,w;
    }edg[maxn*3];
    int head[maxn*2],cnt{0};
    void addedge(int u,int v,int w){
        edg[++cnt]={v,head[u],w};
        head[u]=cnt;
    }    
}g1,g2;

int n,m;
int a[maxn*2];
int dis[maxn*2];
bool vis[maxn*2];
void dijkstra(){
    std::fill(dis,dis+maxn*3,std::numeric_limits<int>::max()>>2);
    
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    int u,v,w;
    for(int i{1};i<=m;i++){
        cin>>u>>v>>w;
        g1.addedge(u,v,w);
        g1.addedge(v,u,w);
    }
    for(int i{1};i<=n;i++){
        cin>>a[i];
    }
    cout.flush();
    return 0;
}