#include<iostream>
#include<algorithm>
using std::cin,std::cout,std::ios,std::min;
constexpr int maxn=2e4;
int head[maxn+10],cnt=0;
struct Edge{
    int v=0,nxt=0;
}edg[maxn*3];
void addedge(int u,int v){
    edg[++cnt].v=v;
    edg[cnt].nxt=head[u];
    head[u]=cnt;
    return ;
}
int n;
// int fa[maxn+10];
// void dfs(int x,int f){
//     fa[x]=f;
//     for(int e{head[x]};e;e=edg[e].nxt){
//         int to=edg[e].v;
//         if(to!=f)dfs(to,x);
//     }
// }
int dp[maxn+10][3];
void dfs(int x,int f){
    dp[x][2]=0;dp[x][1]=1;
    int t=0;
    int flag=0;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to=edg[e].v;
        if(to==f)continue;
        dfs(to,x);
        if(dp[to][0]>dp[to][1])flag=1;
        t+=dp[to][0];
        dp[x][1]+=min({dp[to][0],dp[to][1],dp[to][2]});
        dp[x][2]+=min(dp[to][0],dp[to][1]);
    }
    if(flag)dp[x][0]=dp[x][2];
    else{
        dp[x][0]=maxn*2;
        for(int e{head[x]};e;e=edg[e].nxt){
            int to=edg[e].v;
            if(to==f)continue;
            dp[x][0]=min(dp[x][0],t-dp[to][0]+dp[to][1]);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin>>n;
{
    int u,v;
    for(int i{1};i<n;i++){
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
}
    std::fill(dp[0],dp[0]+(maxn+10)*3,maxn*2);
    dfs(1,0);
    cout<<min(dp[1][0],dp[1][1])<<"\n";
    return 0;
}