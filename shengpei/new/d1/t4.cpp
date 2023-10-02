#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e5,p=998244353;
struct Edge{
    int nxt{0},v{0};
}edg[maxn*3];
int head[maxn*2],cnt=0,c[maxn*2],f1[maxn*2],val[maxn*2],sv[maxn*2];
void addedge(int u,int v){
    edg[++cnt].nxt=head[u];
    edg[cnt].v=v;
    head[u]=cnt;
}
int n,q,opt;
int fa[maxn*2],tot=0;
void dfs1(int u,int f){
    fa[u]=f;
    val[u]=c[u];
    for(int e{head[u]};e;e=edg[e].nxt){
        int to=edg[e].v;
        if(to!=f){
            dfs1(to,u);
            val[u]=std::max(val[u],val[to]);
            sv[u]=std::max(sv[u],val[to]);
            f1[u]+=f1[to];
            f1[u]%=p;
        }
    }
    f1[u]+=val[u];
    f1[u]%=p;
}
void solve(int u){
    val[u]=c[u];
    f1[u]=0;
    for(int e{head[u]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=fa[u]){
            val[u]=std::max(val[u],val[to]);
            f1[u]+=f1[to];
            f1[u]%=p;
        }
    }
    f1[u]+=val[u];
    f1[u]%=p;
    if(fa[u])solve(fa[u]);
}
int calc(int a,int l,int r){
    int res{0};
    int oc=c[a];
    for(int i{l};i<=r;i++){
        c[a]=i;
        solve(a);
        res+=f1[1];
        res%=p;
    }
    c[a]=oc;
    solve(a);
    return res;
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>q>>opt;
    for(int i{1};i<=n;i++){
        cin>>c[i];
    }
    int u,v;
    for(int i{1};i<n;i++){
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0);
    int l,r,a;
    for(int i{1};i<=q;i++){
        cin>>l>>r>>a;
        cout<<calc(a%n+1,l%n+1,r%n+1)<<"\n";
    }
    return 0;
}