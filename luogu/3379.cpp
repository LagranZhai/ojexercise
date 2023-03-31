#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5;
int n,m,s,head[maxn+10],cnt=0,lg[maxn+10],dep[maxn+10];
int fa[20][maxn];
struct Edge{
    int u,v,nxt;
}edg[maxn*2+10];
void addedge(int u,int v){
    edg[++cnt].u=u;
    edg[cnt].v=v;
    edg[cnt].nxt=head[u];
    head[u]=cnt;
}
void dfs(int x,int f){
    fa[0][x]=f;
    dep[x]=dep[f]+1;
    for(int i=1;i<=lg[dep[x]];i++){
        fa[i][x]=fa[i-1][fa[i-1][x]];
    }
    for(int e=head[x];e;e=edg[e].nxt){
        if(edg[e].v!=f){
            dfs(edg[e].v,x);
        }
    }
    return;
}
void init(){
    lg[0]=0;lg[1]=0;
    for(int i=2;i<=n;i++)lg[i]=lg[i/2]+1;
    dfs(s,0);
}
int lca(int u,int v){
    if(dep[u]<dep[v]){
        swap(u,v);
    }
    while(dep[u]>dep[v]){
        u=fa[lg[dep[u]-dep[v]-1]][u];
    }
    if(u==v)return v;
    for(int i=lg[dep[u]];i>=0;i--){
        if(fa[i][u]!=fa[i][v]){
            u=fa[i][u];v=fa[i][v];
        }
    }
    return fa[0][u];
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m>>s;
    int x,y;
    for(int i=1;i<=n-1;i++){
        cin>>x>>y;
        addedge(x,y);
        addedge(y,x);
    }
    init();
    for(int i=1;i<=m;i++){
        cin>>x>>y;
        cout<<lca(x,y)<<endl;
    }
    return 0;
}