#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=200,maxm=5e4;
#define int long long
int n,m;
int g1tog2[maxm+100],g3tog4[maxm+100];
struct Graph{
    struct Edge{
        int v,nxt,c,d;
    }edg[maxm+100];
    int head[maxn*2],cnt{0};
    int tdis{std::numeric_limits<int>::max()>>2};
    void addedge(int u,int v,int c,int d){
        edg[++cnt]={v,head[u],c,d};
        head[u]=cnt;
    }
    bool vis[maxn*2];
    std::pair<int,int> fa[maxn+100];
    int sp[maxm*2];
    int ansofdel[maxn*2];
    void dijkstra(int s,int t,int del,int *dis,int &ans){
        std::fill(dis,dis+maxn+100,std::numeric_limits<int>::max()>>2);
        std::fill(vis,vis+maxn+100,0);
        dis[s]=0;
        int viscnt{0};
        while(viscnt<n){
            int cur{0};
            for(int i{1};i<=n;i++){
                if(!vis[i]&&dis[i]<dis[cur]){
                    cur=i;
                }
            }
            if(dis[cur]>=std::numeric_limits<int>::max()>>2||cur==0)break;
            vis[cur]=1;viscnt++;
            for(int e{head[cur]};e;e=edg[e].nxt){
                if(e==del)continue;
                int to{edg[e].v};
                if(!vis[to]&&dis[to]>dis[cur]+edg[e].c){
                    dis[to]=dis[cur]+edg[e].c;
                    fa[to]={cur,e};
                }
            }
        }
        ans=dis[t];
    }
    std::unordered_set<int> issp{};
    int dis[maxn*2];
    void getsp(int s,int t){
        dijkstra(s,t,0,dis,tdis);
        int cur{t};
        while(fa[cur].first!=0){
            if(fa[cur].second!=0){
                issp.insert(fa[cur].second);
                int oh{head[cur]};
                addedge(cur,fa[cur].first,edg[fa[cur].second].c,edg[fa[cur].second].d);
                dijkstra(s,t,fa[cur].second,dis,sp[fa[cur].second]);
                edg[head[cur]]={};
                head[cur]=oh;cnt--;
            }
            cur=fa[cur].first;
        }
    }
    // void fromsp(int s,int t,Graph &from){
    //     int cur{s};
    //     while(cur!=0){
    //         int u=from.fa[cur].first;
    //         if(from.fa[cur].second!=0){
    //             int oh{head[u]};
    //             addedge(u,cur,from.edg[fa[cur].second].c,from.edg[fa[cur].second].d);
    //             dijkstra(s,t,g1tog2[from.fa[cur].second],dis,sp[g1tog2[from.fa[cur].second]]);
    //             edg[head[cur]]={};
    //             head[u]=oh;cnt--;
    //         }
    //         cur=fa[cur].first;
    //     }
    // }
    // int dp[maxn+100][maxn+100];
}g1,g2,g3,g4;
struct E{
    int u,v,c,d,idx1,idx3;
}edge[maxm+10];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    int u,v,c,d;
    for(int i{1};i<=m;i++){
        cin>>u>>v>>c>>d;
        g1.addedge(u,v,c,d);
        g2.addedge(v,u,c,d);
        g1tog2[g1.cnt]=g2.cnt;
        g3.addedge(u,v,c,d);
        g4.addedge(v,u,c,d);
        g3tog4[g3.cnt]=g4.cnt;
        edge[i]={u,v,c,d,g1.cnt,g3.cnt};
    }
    g1.getsp(1,n);
    g2.dijkstra(n,1,0,g2.dis,g2.tdis);
    g3.getsp(n,1);
    g4.dijkstra(1,n,0,g4.dis,g4.tdis);
    int ans{std::numeric_limits<int>::max()};
    for(int i{1};i<=m;i++){
        int cur1{std::numeric_limits<int>::max()>>2},cur2{std::numeric_limits<int>::max()>>2};
        int u{edge[i].u},v{edge[i].v};
        if(g1.issp.find(edge[i].idx1)!=g1.issp.end()){
            // if(g2.issp.find(g1tog2[edge[i].idx1])==g2.issp.end())cout<<"w\n";
            // cur1=std::min(g1.dp[g1.issp[edge[i].idx1]][n],g1.dp[g1.issp[edge[i].idx1]][v]+edge[i].c+edge[i].d+g2.dp[g2.issp[g1tog2[edge[i].idx1]]][u]);
            cur1=g1.sp[edge[i].idx1];
        }
        else{
            cur1=std::min(g1.tdis,g1.dis[v]+edge[i].c+edge[i].d+g2.dis[u]);
        }
        if(g3.issp.find(edge[i].idx3)!=g3.issp.end()){
            // if(g4.issp.find(g3tog4[edge[i].idx3])==g4.issp.end())cout<<"w\n";
            // cur2=std::min(g3.dp[g3.issp[edge[i].idx3]][1],g3.dp[g3.issp[edge[i].idx3]][v]+edge[i].c+edge[i].d+g4.dp[g4.issp[g3tog4[edge[i].idx3]]][u]);
            cur2=g3.sp[edge[i].idx3];
        }
        else{
            cur2=std::min(g3.tdis,g3.dis[v]+edge[i].c+edge[i].d+g4.dis[u]);
        }
        if(cur1>(int)std::numeric_limits<signed>::max()||cur2>(int)std::numeric_limits<signed>::max())continue;
        ans=std::min(cur1+cur2,ans);
    }
    if(ans>(int)std::numeric_limits<signed>::max())cout<<-1<<"\n";
    else cout<<std::min(g1.tdis+g3.tdis,ans)<<"\n";
    cout.flush();
    return 0;
}