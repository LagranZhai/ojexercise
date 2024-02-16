//PA
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=4e5;
struct Edge{
    int nxt,v,w;
}edg[maxn*2];
int head[maxn],cnt{0};
void addedge(int u,int v,int w){
    edg[++cnt]={head[u],v,w};
    head[u]=cnt;
}
int n;
int siz[maxn];
void getct(int x,int f,int &ct,int &csiz){
    siz[x]=1;
    int maxsonsiz{0};
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            getct(to,x,ct,csiz);
            siz[x]+=siz[to];
            maxsonsiz=std::max(siz[to],maxsonsiz);
        }
    }
    maxsonsiz=std::max(maxsonsiz,n-siz[x]);
    if(maxsonsiz<csiz){
        ct=x;
        csiz=maxsonsiz;
    }
    return ;
}
int dis[maxn];
void dfs(int x,int f){
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            dis[to]=dis[x]+edg[e].w;
            dfs(to,x);
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n;
    int u,v,w;
    for(int i{1};i<n;i++){
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
    }
    int ct{0},csiz{std::numeric_limits<int>::max()};
    getct(1,0,ct,csiz);
    dfs(ct,0);
    // cout<<ct<<"\n";
    int ans{0};
    for(int i{1};i<=n;i++){
        ans+=dis[i];
    }
    cout<<ans*2<<"\n";
    cout.flush();
    return 0;
}