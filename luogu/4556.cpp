#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e5;
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
int n,m;
int fa[maxn*2],dep[maxn*2],siz[maxn*2],hson[maxn*2];
void dfs1(int x,int f){
    dep[x]=dep[f]+1;
    fa[x]=f;
    siz[x]=1;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(f!=to){
            dfs1(to,x);
            siz[x]+=siz[to];
            if(siz[to]>siz[hson[x]]){
                hson[x]=to;
            }
        }
    }
}
int dfn[maxn*2],rnk[maxn*2],tot{0},top[maxn*2];
void dfs2(int x,int f,int ctop){
    dfn[x]=++tot;
    rnk[tot]=x;
    top[x]=ctop;
    if(hson[x]){
        dfs2(hson[x],x,ctop);
    }
    for(int e{head[x]};e;edg[e].nxt){
        int to{edg[e].v};
        if(to!=f&&to!=hson[x]){
            dfs2(to,x,to);
        }
    }
}
int lca(int u,int v){
    while(dep[top[u]]!=dep[top[v]]){
        if(dep[top[u]]<dep[top[v]]){
            std::swap(u,v);
        }
        u=fa[top[u]];
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n;
    int u,v;
    for(int i{1};i<n;i++){
        cin>>u>>v;
        addedge(u,v);addedge(v,u);
    }

    cout<<std::flush;
    return 0;
}