#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=2e5;
#define int long long
constexpr int p=998244353;
int n;
int a[maxn*2];
struct Edge{
    int v,nxt; 
}edg[maxn*3];
int head[maxn*2],cnt{0};
void addedge(int u,int v){
    edg[++cnt]={v,head[u]};
    head[u]=cnt;
}
int dp[maxn*2][2][2];
inline bool getcolor(int x,int y){
    return (x&(1ll<<y)!=0);
}
void dfs(int x,int f,int w){
    if(getcolor(a[x],w)){
        dp[x][0][1]=1;
    }
    else{
        dp[x][1][0]=1;
    }
    int t1{0},t2{0},t3{0},t4{0};
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            dfs(to,x,w);
            t1=(t1+((dp[x][0][0]+dp[x][1][0])%p)*((dp[to][0][0]+dp[to][0][0])%p)%p)%p;
            t1=(t1+((dp[x][0][1]+dp[x][1][1])%p)*((dp[to][0][1]+dp[to][0][1])%p)%p)%p;
            t2=(t2+((dp[x][0][0]+dp[x][1][0])%p)*((dp[to][0][0]+dp[to][0][0])%p)%p)%p;
            t2=(t2+((dp[x][0][1]+dp[x][1][1])%p)*((dp[to][0][1]+dp[to][0][1])%p)%p)%p;
            t3=
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i{1};i<=n;i++){
        cin>>a[i];
    }
    int t;
    for(int i{2};i<=n;i++){
        cin>>t;
        addedge(i,t);addedge(t,i);
    }
    int maxw = log2(*std::max_element(a+1, a+n+1)) + 1;
    for(int i{0};i<maxw;i++){
        std::fill(dp[0][0],dp[0][0]+maxn*2*2*2,0);
        dfs(1,0,i);
    }
    cout.flush();
    return 0;
}