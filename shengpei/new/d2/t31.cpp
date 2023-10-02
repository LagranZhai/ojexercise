#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e5;
int tcnt[maxn*4],tsum[maxn*4],tag[maxn*4],a[maxn*2],tag[maxn*4];
int n,q;
int head[maxn],cnt{0};
struct Edge{
    int nxt{0},v{0};
}edg[maxn*3];
void addedge(int u,int v){
    edg[++cnt].nxt=head[u];
    edg[cnt].v=v;
    head[u]=cnt;
    return ;
}
bool des[maxn];
int dfn[maxn*2],rnk[maxn*2],tot=0;
void dfs(int x,int f){
    dfn[x]=++tot;
    rnk[tot]=x;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            dfs(to,x);
        }
    }
}
void build(int p,int cl,int cr){
    if(cl==cr){
        tcnt[p]=0;
        tsum[p]=a[rnk[p]];
        return ;
    }
    int mid=(cl+cr)/2;
    build(p*2,cl,mid);
    build(p*2+1,mid+1,cr);
    tcnt[p]=std::min(tcnt[p*2],tcnt[p*2+1]);
    tsum[p]=tsum[p*2]+tsum[p*2+1];
}
void update(int p,int cl,int cr,int l,int r,int d){
    if(cl>=l&&cr<=r){
        tcnt[p]+=d;
        tag[p]+=d;
    }
    if(cl!=cr){
        int mid=(cl+cr)/2;
        pushdown
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>q;
    int u,v;
    for(int i{1};i<n;i++){
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    for(int i{1};i<=n;i++){
        cin>>a[i];
    }
    dfs(1,0);
    return 0;
}