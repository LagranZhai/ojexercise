#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
#define int long long
constexpr int maxn=1e5,maxm=2e5;
struct Graph{
    struct Edge{
        int v{0},nxt{0},w{0},id{0};
    }edg[maxm*3];
    int head[maxn*2],cnt{0};
    void addedge(int u,int v,int w,int id){
        edg[++cnt].v=v;
        edg[cnt].id=id;
        edg[cnt].w=w;
        edg[cnt].nxt=head[u];
        head[u]=cnt;
    }
}g1{},g[2];
int dis1[maxn*2],dis2[maxn*2];
int *dis[2]={dis1,dis2};
bool vis[maxn*2];
struct Node{
    int dis{0},p{0},f{0},id{0};
    bool operator<(const Node A)const{
        return dis>A.dis;
    }
};
std::priority_queue<Node> q;
void dijkstra(int s,int type){ //0from1 1fromn
    std::fill(dis[type],dis[type]+maxn*2,std::numeric_limits<int>::max()>>3);
    std::fill(vis,vis+maxn*2,0);
    dis[type][s]=0;
    q.push({0,s,0,0});
    while(!q.empty()){
        Node cur{q.top()};
        q.pop();
        if(!vis[cur.p]){
            g[type].addedge(cur.p,cur.f,0,cur.id);
            g[type].addedge(cur.f,cur.p,0,cur.id);
            vis[cur.p]=1;
            for(int e{g1.head[cur.p]};e;e=g1.edg[e].nxt){
                int to{g1.edg[e].v};
                if(!vis[to]&&dis[type][to]>dis[type][cur.p]+g1.edg[e].w){
                    dis[type][to]=dis[type][cur.p]+g1.edg[e].w;
                    // vis[to]=1;
                    q.push({dis[type][to],to,cur.p,g1.edg[e].id});
                }
            }
        }
    }
}
int fa[maxn*2];
int lca[maxn*2][2];
int nxtedge[maxn*2][2];
void dfs(int x,int f,int type){
    // cout<<x<<"\n";
    fa[x]=f;
    for(int e{g[type].head[x]};e;e=g[type].edg[e].nxt){
        int to{g[type].edg[e].v};
        if(to!=f){
            nxtedge[to][type]=g[type].edg[e].id;
            dfs(to,x,type);
        }
    }
}
void dfs2(int x,int f,int unit,int type){
    lca[x][type]=unit;
    for(int e{g1.head[x]};e;e=g1.edg[e].nxt){
        int to{g1.edg[e].v};
        if(to!=f&&lca[to][type]==0&&dis[type][to]==dis[type][x]+g1.edg[e].w){
            dfs2(to,x,unit,type);
        }
    }
}
std::vector<int> sp;
int basecluster[maxn*2];
std::unordered_map<int,int> nodetoind;
std::unordered_set<int> bcedge;
int bcnt{0};
int n,m;
void getlca(){
    dfs(1,0,0);
    int cur{n};
    while(cur!=0){
        sp.push_back(cur);
        if(fa[cur]!=0)bcedge.insert(nxtedge[cur][0]);
        cur=fa[cur];
    }
    bcnt=sp.size();
    for(int i{0};i<bcnt;i++){
        basecluster[i+1]=sp[bcnt-i-1];
        nodetoind[basecluster[i+1]]=i+1;
        lca[basecluster[i+1]][0]=lca[basecluster[i+1]][1]=i+1;
    }
    for(int i{1};i<=bcnt;i++){
        dfs2(basecluster[i],0,i,0);
    }
    for(int i{bcnt};i>=1;i--){
        dfs2(basecluster[i],0,i-1,1);
    }
}
struct E{
    int u,v,w;
}edge[maxm*2];
//segment range min 
struct Data{
    int min{};
    Data operator+(Data A){
        return {std::min(min,A.min)};
    }
}didentity{std::numeric_limits<int>::max()};
struct Tag{
    int less{};
    Tag operator+(const Tag A){
        return {std::min(less,A.less)};
    }
    Data operator*(const Data A){
        return {std::min(less,A.min)};
    }
}tidentity{std::numeric_limits<int>::max()};
struct dm{
    Tag t{};Data d{};
}tree[maxn*4];
void build(int p,int cl,int cr){
    tree[p].t=tidentity;
    if(cl==cr){
        tree[p].d=didentity;
        return ;
    }
    int mid=(cl+cr)/2;
    build(p*2,cl,mid);
    build(p*2+1,mid+1,cr);
    tree[p].d=tree[p*2].d+tree[p*2+1].d;
    return ;
}
void pushdown(int p){
    if(tree[p].t.less!=std::numeric_limits<int>::max()){
        tree[p*2].d=tree[p].t*tree[p*2].d;
        tree[p*2].t=tree[p].t+tree[p*2].t;
        tree[p*2+1].d=tree[p].t*tree[p*2+1].d;
        tree[p*2+1].t=tree[p].t+tree[p*2+1].t;
        tree[p].t=tidentity;
    }
}
void update(int p,int cl,int cr,int l,int r,Tag w){
    if(cl>=l&&cr<=r){
        tree[p].d=w*tree[p].d;
        tree[p].t=w+tree[p].t;
        return ;
    }
    if(cl!=cr){//??
        pushdown(p);
        int mid=(cl+cr)/2;
        if(mid>=l)update(p*2,cl,mid,l,r,w);
        if(mid<r)update(p*2+1,mid+1,cr,l,r,w);
        tree[p].d=tree[p*2].d+tree[p*2+1].d;
    }
    return ;
}
void query(int p,int cl,int cr,int l,int r,Data& ans){
    if(cl>=l&&cr<=r){
        ans=ans+tree[p].d;
        return ;
    }
    if(cl!=cr){
        pushdown(p);
        int mid=(cl+cr)/2;
        if(mid>=l)query(p*2,cl,mid,l,r,ans);
        if(mid<r)query(p*2+1,mid+1,cr,l,r,ans);
    }
    return ;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
{
    int s,t,c;
    for(int i{1};i<=m;i++){
        cin>>s>>t>>c;
        edge[i].u=s;edge[i].v=t;edge[i].w=c;
        g1.addedge(s,t,c,i);
        g1.addedge(t,s,c,i);
    }
}
    dijkstra(1,0);dijkstra(n,1);
    // for(int i{1};i<=n;i++){
    //     cout<<dis[0][i]<<" "<<dis[1][i]<<"\n";
    // }
    getlca();
    build(1,1,bcnt-1);
    for(int i{1};i<=m;i++){
        if(bcedge.find(i)!=bcedge.end())continue;
        int l{lca[edge[i].u][0]},r{lca[edge[i].v][1]};
        if(l>r)continue;
        update(1,1,bcnt-1,l,r,{dis[0][edge[i].u]+edge[i].w+dis[1][edge[i].v]});
        l=lca[edge[i].v][0];r=lca[edge[i].u][1];
        if(l>r)continue;
        update(1,1,bcnt-1,l,r,{dis[0][edge[i].v]+edge[i].w+dis[1][edge[i].u]});
    }
    int ans={0};int acnt{0};
    for(int i{1};i<bcnt;i++){
        Data tmp=didentity;
        query(1,1,bcnt-1,i,i,tmp);
        if(tmp.min==ans){
            acnt++;
        }
        if(tmp.min>ans){
            ans=tmp.min;
            acnt=1;
        }
    }
    if(ans!=dis[0][n])cout<<ans<<" "<<acnt<<"\n";
    else cout<<ans<<" "<<m<<"\n";
    cout.flush();
    return 0;
}