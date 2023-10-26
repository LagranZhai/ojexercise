#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
constexpr int maxn=100;
#define int long long
int dp[maxn+10][maxn+10][maxn+10];
int x[maxn*2],y[maxn*2],z[maxn*2];
struct Edge{
    int v{0},nxt{0},p{0},q{0};
}edg[maxn*2];
int head[maxn*2],cnt{0};
void addedge(int u,int v,int p,int q){
    edg[++cnt].v=v;
    edg[cnt].p=p;
    edg[cnt].q=q;
    edg[cnt].nxt=head[u];
    head[u]=cnt;
}
int n,m,k,g;
bool vis[maxn*2][maxn*2][maxn*2];
struct Node{
    int dis{0},cur{0},ck{0},cg{0};
    bool operator<(const Node& A)const{
        return dis>A.dis;
    }
};
std::priority_queue<Node> q;
void relax(int cur,int to,int ck,int cg,int ck1,int cg1,int w){
    if(dp[to][ck1][cg1]>dp[cur][ck][cg]+w){
        dp[to][ck1][cg1]=dp[cur][ck][cg]+w;
        q.push({dp[to][ck1][cg1],to,ck1,cg1});
    }
}
int dijkstra(){
    std::fill(dp[0][0],dp[0][0]+(maxn+10)*(maxn+10)*(maxn+10),1e18);
    // q.push({2,0,0,0});q.push({1,0,0,0});
    // cerr<<q.top().dis;
    // q.pop();q.pop();
    // memset(dp,999999,sizeof(dp));
    dp[1][0][0]=0;
    q.push({0,1,0,0});
    while(!q.empty()){
        // int dis,cur,ck,cg;
        Node curn=q.top();
        int dis{curn.dis},cur{curn.cur},ck{curn.ck},cg{curn.cg};
        q.pop();
        if(cur==n)return dis;
        if(vis[cur][ck][cg])continue;
        vis[cur][ck][cg]=1;
        int now{dis%(x[cur]+y[cur]+z[cur])};
        for(int e{head[cur]};e;e=edg[e].nxt){
            int to{edg[e].v};
            if(now<x[cur]){
                relax(cur,to,ck,cg,ck,cg,edg[e].q);
                if(ck<m-k)relax(cur,to,ck,cg,ck+1,cg,edg[e].p);
            }
            else if(now<x[cur]+y[cur]){
                relax(cur,to,ck,cg,ck,cg,(x[cur]+y[cur]+z[cur])-now+edg[e].q);
                if(ck<m-k)relax(cur,to,ck,cg,ck+1,cg,(x[cur]+y[cur]+z[cur])-now+edg[e].p);
                if(cg<g){
                    relax(cur,to,ck,cg,ck,cg+1,edg[e].q);
                    if(ck<m-k)relax(cur,to,ck,cg,ck+1,cg+1,edg[e].p);
                }
            }
            else{
                relax(cur,to,ck,cg,ck,cg,(x[cur]+y[cur]+z[cur])-now+edg[e].q);
                if(ck<m-k)relax(cur,to,ck,cg,ck+1,cg,(x[cur]+y[cur]+z[cur])-now+edg[e].p);
            }
        }
    }
    // return 0;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m>>k>>g;
    for(int i{1};i<=n;i++){
        cin>>x[i]>>y[i]>>z[i];
    }
    int u,v,p,q;
    for(int i{1};i<=m;i++){
        cin>>u>>v>>p>>q;
        addedge(u,v,p,q);
        addedge(v,u,p,q);
    }
    cout<<dijkstra()<<std::endl;
    // dijkstra();
    // int ans{std::numeric_limits<int>::max()};
    // for(int i{0};i<=m-k;i++){
    //     for(int j{0};j<=g;j++){
    //         // if(dp[n][i][j]==0)cout<<i<<" "<<j<<"\n";
    //         ans=std::min(ans,dp[n][i][j]);
    //     }
    // }
    // cout<<ans<<"\n";
    cout<<std::flush;
    return 0;
}