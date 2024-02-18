//PB
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=1e5,maxm=2e5;
struct Edge{
    int v,nxt,w;
}edg[maxm*2];
int head[maxn],cnt{0};
void addedge(int u,int v,int w){
    edg[++cnt]={v,head[u],w};
    head[u]=cnt;
}
int n,m,a,b,c,d,e;
struct Dis{
    int dis[maxn];
    void dijkstra(int s){
        std::fill(dis,dis+maxn,std::numeric_limits<int>::max()>>3);
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
}rel[10];
int r[10],rev[maxn];
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    for(int i{1};i<=5;i++)cin>>r[i],rev[r[i]]=i;
    int u,v,w;
    for(int i{1};i<=m;i++){
        cin>>u>>v>>w;
        addedge(u,v,w);addedge(v,u,w);
    }
    rev[1]=0;
    rel[0].dijkstra(1);
    for(int i{1};i<=5;i++){
        rel[i].dijkstra(r[i]);
    }
    // rel[1].dijkstra(a);
    // rel[2].dijkstra(b);
    // rel[3].dijkstra(c);
    // rel[4].dijkstra(d);
    // rel[5].dijkstra(e);
    int p[10];
    for(int i{1};i<=5;i++){
        p[i]=i;
    }
    int ans{std::numeric_limits<int>::max()};
    do{
        int cur{1},res{0};
        for(int i{1};i<=5;i++){
            res+=rel[rev[cur]].dis[r[p[i]]];
            cur=r[p[i]];
        }
        ans=std::min(ans,res);
    }while(std::next_permutation(p+1,p+6));
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}