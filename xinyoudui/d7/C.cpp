//PC
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=2e5,maxm=2e6;
struct Edge{
    int v,nxt,w;
}edg[maxm*2];
int head[maxn],cnt{0};
void addedge(int u,int v,int w){
    edg[++cnt]={v,head[u],w};
    head[u]=cnt;
}
int n,m,k,s,t;
int dis[maxn];
void dijkstra(int s){
    std::fill(dis,dis+maxn,std::numeric_limits<int>::max()>>2);
    dis[s]=0;
    using pii=std::pair<int,int>;
    auto cmp=[](const pii& A,const pii& B){return A.second>B.second;};
    std::priority_queue<pii,std::vector<pii>,decltype(cmp)> q(cmp);
    q.push({s,0});
    while(!q.empty()){
        pii cur{q.top()};q.pop();
        if(dis[cur.first]==cur.second){
            for(int e{head[cur.first]};e;e=edg[e].nxt){
                int to{edg[e].v};
                if(dis[to]>dis[cur.first]+edg[e].w){
                    dis[to]=dis[cur.first]+edg[e].w;
                    q.push({to,dis[to]});
                }
            }
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m>>k>>s>>t;
    int u,v,w;
    for(int i{1};i<=m;i++){
        cin>>u>>v>>w;
        for(int j{};j<=k;j++){
            addedge(j*n+u,j*n+v,w);
            addedge(j*n+v,j*n+u,w);
            addedge(j*n+u,(j+1)*n+v,0);
            addedge(j*n+v,(j+1)*n+u,0);
        }
    }
    dijkstra(s);
    // for(int i{};i<=k*n+t;i++){
    // cout<<dis[i]<<"\n";

    // }
    int ans{std::numeric_limits<int>::max()};
    for(int i{};i<=k;i++){
        ans=std::min(ans,dis[i*n+t]);
    }
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}