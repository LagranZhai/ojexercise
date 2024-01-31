#include<bits/stdc++.h>
using std::cin,std::cout;
#define int long long
constexpr int maxn=1e6;
struct Edge{
    int v,nxt;
}edg[maxn*5];
int head[maxn*2],cnt{0};
void addedge(int u,int v){
    edg[++cnt]={v,head[u]};
    head[u]=cnt;
}
char str[maxn*10];
int n{0};
int a[maxn*2];
int dp[maxn*2][2];
void dfs(int x,int f){
    dp[x][0]=dp[x][1]=std::numeric_limits<int>::max();
    int child{0};
    int tsum{0};
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            child++;
            dfs(to,x);
            tsum+=dp[to][0];
        }
    }
    if(child==0){
        dp[x][0]=a[x];
        dp[x][1]=0;
    }
    else{
        dp[x][0]=tsum;
        for(int e{head[x]};e;e=edg[e].nxt){
            int to{edg[e].v};
            if(to!=f){
                dp[x][0]=std::min(dp[x][0],tsum-dp[to][0]+dp[to][1]+a[x]);
            }
        }
        for(int e{head[x]};e;e=edg[e].nxt){
            int to{edg[e].v};
            if(to!=f){
                dp[x][1]=std::min(dp[x][1],tsum-dp[to][0]+dp[to][1]);
            }
        }
    }

}
signed main(){
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.getline(str,maxn*2);
    std::istringstream ss(str);
    int t;
    while(ss>>t){
        a[++n]=t;
    }
    // for(int i{1};i<=n;i++){
    //     cout<<a[i]<<" ";
    // }
    int x,y;
    for(int i{1};i<n;i++){
        cin>>x>>y;
        addedge(x,y);
        addedge(y,x);
    }
    dfs(1,0);
    cout<<dp[1][0]<<"\n";
    cout.flush();
    return 0;
}