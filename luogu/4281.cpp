//P4281
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=5e5+100;
int n,m;
struct Edge{
    int v,nxt;
}edg[maxn*3];
int head[maxn],cnt{0};
void addedge(int u,int v){
    edg[++cnt]={v,head[u]};
    head[u]=cnt;
}
int siz[maxn],dep[maxn],hson[maxn],fa[maxn];
void dfs1(int x,int f){
    fa[x]=f;dep[x]=dep[f]+1;
    siz[x]=1;hson[x]=0;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            dfs1(to,x);
            siz[x]+=siz[to];
            if(siz[to]>siz[hson[x]]){
                hson[x]=to;
            }
        }
    }
}
int dfn[maxn],rnk[maxn],dfx{0},top[maxn];
void dfs2(int x,int f,int ctop){
    top[x]=ctop;
    dfn[x]=++dfx;
    rnk[dfx]=x;
    if(hson[x]){
        dfs2(hson[x],x,ctop);
    }
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f&&to!=hson[x]){
            dfs2(to,x,to);
        }
    }
}
int lca(int x,int y){
    while(top[x]!=top[y]){
        if(dfn[top[x]]<dfn[top[y]]){
            std::swap(x,y);
        }
        x=fa[top[x]];
    }
    if(dfn[x]<dfn[y]){
        std::swap(x,y);
    }
    return y;
}
int getlen(int x,int y){
    int t{lca(x,y)};
    return dep[x]+dep[y]-2*dep[t];
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    int u,v,w;
    for(int i{1};i<n;i++){
        cin>>u>>v;
        addedge(u,v);addedge(v,u);
    }
    dfs1(1,0);dfs2(1,0,1);
    int x,y,z;
    for(int i{1};i<=m;i++){
        cin>>x>>y>>z;
        if(x==y&&y==z){
            cout<<x<<" 0\n";
            continue;
        }
        u=lca(x,y);v=lca(x,z);w=lca(y,z);
        if(u==v){
            cout<<w<<" "<<getlen(w,x)+getlen(w,y)+getlen(w,z)<<"\n";
        }
        else if(u==w){
            cout<<v<<" "<<getlen(v,x)+getlen(v,y)+getlen(v,z)<<"\n";
        }
        else if(w==v){
            cout<<u<<" "<<getlen(u,x)+getlen(u,y)+getlen(u,z)<<"\n";
        }
    }
    cout.flush();
    return 0;
}