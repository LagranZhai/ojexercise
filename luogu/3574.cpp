#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
using std::cin,std::cout,std::ios,std::max;
constexpr int maxn=5e5;
#define int long long
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
int c[maxn+100];
int siz[maxn+100];
int dp[maxn+100];
auto Cmp=[](int a,int b){return dp[b]-siz[b]>dp[a]-siz[a];};
void dfs(int x,int f){
    std::priority_queue<int,std::vector<int >,decltype(Cmp) > q(Cmp);
    for(int e{head[x]};e;e=edg[e].nxt){
        int to=edg[e].v;
        if(to==f)continue;
        dfs(to,x);
        siz[x]+=siz[to]+2;
        q.push(to);
    }
    int sum=1;
    dp[x]=c[x];
    while(!q.empty()){
        int p=q.top();q.pop();
        // cout<<p<<" ";
        dp[x]=max(dp[x],dp[p]+sum);
        sum+=siz[p]+2;
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i{1};i<=n;i++){
        cin>>c[i];
    }
{
    int u,v;
    for(int i{1};i<n;i++){
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
}
    dfs(1,0);
    cout<<max(dp[1],c[1]+siz[1])<<"\n";
    return 0;
}