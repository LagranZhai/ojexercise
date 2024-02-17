//PB
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=2e4,maxm=2e6;
struct Edge{
    int v,nxt;
}edg[maxm*2];
int head[maxn],cnt{0};
void addedge(int u,int v){
    edg[++cnt]={v,head[u]};
    head[u]=cnt;
}
int n;
int a[maxn],dp[maxn],in[maxn];
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n;
    int x;
    for(int i{1};i<=n;i++){
        cin>>x>>a[i];
        cin>>x;
        while(x!=0){
            addedge(x,i);in[i]++;
            cin>>x;
        }
    }
    std::queue<int> q;
    for(int i{1};i<=n;i++){
        if(in[i]==0){
            q.push(i);
            dp[i]=a[i];
        }
    }
    while(!q.empty()){
        int cur{q.front()};
        q.pop();
        for(int e{head[cur]};e;e=edg[e].nxt){
            int to{edg[e].v};
            dp[to]=std::max(dp[to],dp[cur]+a[to]);
            in[to]--;
            if(in[to]==0)q.push(to);
        }
    }
    cout<<(*std::max_element(dp+1,dp+n+1))<<"\n";
    cout.flush();
    return 0;
}