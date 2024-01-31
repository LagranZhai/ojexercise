#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e4;
struct Edge{
    int v{0},nxt{0},w{0};
}edg[maxn*3];
int head[maxn*2],cnt{0};
bool ismst[maxn*2];
void addedge(int u,int v,int w){
    edg[++cnt]={v,head[u],w};
    head[u]=cnt;
}
int n,m;
int fa[maxn*2],siz[maxn*2],dep[maxn*2],hson[maxn*2];
int val[maxn*2];
void dfs1(int x,int f){
    siz[x]=1;
    fa[x]=f;
    dep[x]=dep[f]+1;
    hson[x]=0;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            dfs1(to,x);
            siz[x]+=siz[to];
            val[to]=edg[e].w;
            if(siz[to]>siz[hson[x]])hson[x]=to;
        }
    }
}
int dfn[maxn*2],rnk[maxn*2],tot{0},top[maxn*2];
void dfs2(int x,int f,int ctop){
    dfn[x]=++tot;
    rnk[tot]=x;
    top[x]=ctop;
    if(hson[x]!=0){
        dfs2(hson[x],x,ctop);
    }
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f&&to!=hson[x]){
            dfs2(to,x,to);
        }
    }
}
struct Data{
    int max{};
    Data operator+(Data A){
        return {std::min(max,A.max)};
    }
}tree[maxn*5];
void build(int p,int cl,int cr){
    if(cl==cr){
        tree[p].max=val[rnk[cl]];
        return ;
    }
    int mid=(cl+cr)/2;
    build(p*2,cl,mid);
    build(p*2+1,mid+1,cr);
    tree[p]=tree[p*2]+tree[p*2+1];
}
void query(int p,int cl,int cr,int l,int r,Data& ans){
    if(cl>=l&&cr<=r){
        ans=ans+tree[p];
        return ;
    }
    if(cl!=cr){
        int mid=(cl+cr)/2;
        if(l<=mid)query(p*2,cl,mid,l,r,ans);
        if(r>mid)query(p*2+1,mid+1,cr,l,r,ans);
    }
    return ;
}
int jump(int x,int y){
    Data ans{std::numeric_limits<int>::max()};
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            std::swap(x,y);
        }
        query(1,1,n,dfn[top[x]],dfn[x],ans);
        x=fa[top[x]];
    }
    if(dep[x]<dep[y]){
        std::swap(x,y);
    }
    query(1,1,n,dfn[y]+1,dfn[x],ans);
    return ans.max;
}
struct EDGE{
    int u,v,w,id;
}edge[maxn*3];
int ecnt{0};
namespace dsu{
    int fa[maxn*2];
    void init(){
        for(int i{1};i<=n;i++){
            fa[i]=i;
        }
    }
    int getfa(int x){
        return x==fa[x]?x:(fa[x]=getfa(fa[x]));
    }
    void merge(int x,int y){
        fa[getfa(x)] = getfa(y);
    }
    int kruskal(){
        std::sort(edge+1,edge+ecnt+1,[](auto A,auto B){return A.w>B.w;});
        int cnt{0},ans{0};
        for(int i{1};i<=ecnt;i++){
            if(cnt==n-1)break;
            if(getfa(edge[i].u)==getfa(edge[i].v)){
                continue;
            }
            ismst[edge[i].id]=1;
            ans+=edge[i].w;
            merge(edge[i].u,edge[i].v);
            addedge(edge[i].u,edge[i].v,edge[i].w);
            addedge(edge[i].v,edge[i].u,edge[i].w);
            ++cnt;
        }
        return ans;
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    int u,v,w;
    for(int i{1};i<=m;i++){
        cin>>u>>v>>w;
        edge[++ecnt]={u,v,w,i};
    }
    for(int i{1};i<=n;i++){
        edge[++ecnt]={n+1,i,-1,i};
    }
    n++;
    dsu::init();
    dsu::kruskal();
    dfs1(n,0);
    dfs2(n,0,n);
    build(1,1,n);
    int q;
    cin>>q;
    int x,y;
    for(int i{1};i<=q;i++){
        cin>>x>>y;
        cout<<jump(x,y)<<"\n";
    }
    cout.flush();
    return 0;
}