#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::ios;
constexpr int maxn=600,maxm=1e5;
int n,m1,m2;
struct Edge{
    int v,nxt,w;
}edg[maxm*10];
int head[maxn*2],cnt{0};
void addedge(int u,int v,int w){
    edg[++cnt]={v,head[u],w};
    head[u]=cnt;
}
std::vector<int> scc[maxn*2];
int dfn[maxn*2],low[maxn*2],tot{0};
int scci[maxn*2],scccnt{0};
std::stack<int> s;
void tarjan(int x,int f){
    s.push(x);
    dfn[x]=low[x]=++tot;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(!dfn[to]){
            tarjan(to,x);
            low[x]=std::min(low[x],low[to]);
        }
        else if(!scci[to]){
            low[x]=std::min(low[x],dfn[to]);
        }
    }
    if(low[x]==dfn[x]){
        ++scccnt;
        while(1){
            scci[s.top()]=scccnt;
            scc[scccnt].push_back(s.top());
            if(s.top()==x){
                s.pop();
                break;
            }
            s.pop();
        }
    }
}
int dp[maxn*2][maxn*2];
bool floyd(){
    for(int i{1};i<=n;i++){
        dp[i][i]=0;
    }
    for(int k{1};k<=n;k++){
        for(int i{1};i<=n;i++){
            for(int j{1};j<=n;j++){
                dp[i][j]=std::min(dp[i][j],dp[i][k]+dp[k][j]);
            }
        }
    }
    bool flag{0};
    for(int i{1};i<=n;i++){
        if(dp[i][i]<0)flag=1;
    }
    return flag;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m1>>m2;
    int a,b;
    std::fill(dp[0],dp[0]+(maxn*2)*(maxn*2),std::numeric_limits<int>::max()>>4);
    for(int i{1};i<=m1;i++){
        cin>>a>>b;
        addedge(a,b,1);dp[a][b]=std::min(dp[a][b],1);
        addedge(b,a,-1);dp[b][a]=std::min(dp[b][a],-1);
    }
    for(int i{1};i<=m2;i++){
        cin>>a>>b;
        addedge(b,a,0);dp[b][a]=std::min(dp[b][a],0);
    }
    if(floyd()){
        cout<<"NIE"<<"\n";
    }
    else{
        for(int i{1};i<=n;i++){
            if(!scci[i]){
                tarjan(i,0);
            }
        }
        // for(int i{1};i<=n;i++){
        //     // cout<<scci[i]<<" ";
        // }
        int ans{0};
        for(int i{1};i<=scccnt;i++){
            int max{0};
            for(auto v1:scc[i]){
                for(auto v2:scc[i]){
                    max=std::max(max,dp[v1][v2]);
                }
            }
            ans+=max+1;
        }
        cout<<ans<<"\n";
    }
    cout.flush();
    return 0;
}