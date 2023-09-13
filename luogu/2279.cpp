#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
using std::cin,std::cout,std::ios,std::min;
constexpr int maxn=1e3;
int head[maxn+100],cnt=0;
struct Edge{
    int v=0,nxt=0;
}edg[maxn*3];
void addedge(int u,int v){
    edg[++cnt].v=v;
    edg[cnt].nxt=head[u];
    head[u]=cnt;
}
int n;
int dep[maxn+10],fa[maxn+10];
void dfs1(int x,int f){
    fa[x]=f;
    dep[x]=dep[f]+1;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to=edg[e].v;
        if(to!=f)dfs1(to,x);
    }
    return ;
}
auto Cmp=[](int a,int b){return dep[a]<dep[b];};
std::priority_queue<int,std::vector<int >,decltype(Cmp) > q(Cmp);
int dis[maxn+100];
int main(){
    ios::sync_with_stdio(false);
    cin>>n;
    int u;
    for(int i{2};i<=n;i++){
        cin>>u;
        addedge(u,i);
        addedge(i,u);
    }
    dfs1(1,0);
    std::fill(dis,dis+maxn+100,maxn*2);
    for(int i{1};i<=n;i++){
        // cout<<dep[i]<<" ";
        q.push(i);
    }
    int ans=0;
    while(!q.empty()){
        int p=q.top();q.pop();
        // cout<<p;
        if(dis[p]<=2||dis[fa[p]]<=1||dis[fa[fa[p]]]<=0){
            // dis[p]=min({dis[p],dis[fa[p]]+1,dis[fa[fa[p]]]+2});
            // dis[fa[p]]=min({dis[p]+1,dis[fa[p]],dis[fa[fa[p]]]+1});
            dis[fa[fa[p]]]=min({dis[p]+2,dis[fa[p]]+1,dis[fa[fa[p]]]});
            continue;
        }
        if(fa[p]==0){
            ans++;
            dis[p]=0;
            continue;
        }
        if(fa[fa[p]]==0){
            ans++;
            dis[fa[p]]=0;
            dis[p]=1;
            continue;
        }
        ans++;
        dis[fa[fa[p]]]=0;dis[fa[p]]=1;dis[p]=2;
    }
    std::cout<<ans<<"\n";
    return 0;
}