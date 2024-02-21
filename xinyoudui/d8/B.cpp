//PB
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=3e5,maxm=2e6;
int p;
struct G{
    struct Edge{
        int v,nxt;
    }edg[maxm*2];
    int head[maxn],cnt{0};
    void addedge(int u,int v){
        edg[++cnt]={v,head[u]};
        head[u]=cnt;
    }
    int dfx{0},low[maxn],dfn[maxn],scci[maxn],scnt{0};
    bool ins[maxn]{};
    std::stack<int> s{};
    void tarjan(int x){
        low[x]=dfn[x]=++dfx;
        s.push(x);
        ins[x]=1;
        for(int e{head[x]};e;e=edg[e].nxt){
            int to{edg[e].v};
            if(dfn[to]==0){
                tarjan(to);
                low[x]=std::min(low[x],low[to]);
            }
            else if(!scci[to]){
                low[x]=std::min(low[x],low[to]);
            }
        }
        if(low[x]==dfn[x]){
            ++scnt;
            while(s.top()!=x){
                ins[s.top()]=0;scci[s.top()]=scnt;
                s.pop();
            }
            ins[x]=0;scci[x]=scnt;
            s.pop();
        }
    }
    std::queue<int> q{};
    int in[maxn]{},v[maxn]{},dp[maxn]{},c[maxn]{},f[maxn]{};
    void topo(int mn){
        for(int i{1};i<=mn;i++){
            if(!in[i]){
                q.push(i);c[i]=1;
            }
        }
        while(!q.empty()){
            int cur{q.front()};q.pop();
            // dp[cur]+=v[cur];
            for(int e{head[cur]};e;e=edg[e].nxt){
                int to{edg[e].v};
                if(f[to]==cur){
                    in[to]--;
                    if(!in[to])q.push(to);
                    continue;
                }
                f[to]=cur;
                if(dp[to]<dp[cur]+v[to]){
                    dp[to]=dp[cur]+v[to];c[to]=c[cur];
                }
                else if(dp[to]==dp[cur]+v[to]){
                    c[to]=(c[to]+c[cur])%p;
                }
                in[to]--;
                if(!in[to])q.push(to);
            }
        }
    }
    G(){
        for(int* a:{head,dfn,low,in,v,dp,c,scci,f}){
            std::fill(a,a+maxn,0);
        }
    }
}g1{},g2{};
int n,m;
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m>>p;
    int x,y;
    using pii=std::pair<int,int>;
    std::vector<pii> e;
    for(int i{1};i<=m;i++){
        cin>>x>>y;
        g1.addedge(x,y);
        e.push_back({x,y});
    }
    for(int i{1};i<=n;i++){
        if(!g1.dfn[i])g1.tarjan(i);
    }
    for(auto a:e){
        if(g1.scci[a.first]!=g1.scci[a.second]){
            g2.addedge(g1.scci[a.first],g1.scci[a.second]);
            g2.in[g1.scci[a.second]]++;
        }
    }
    for(int i{1};i<=n;i++){
        g2.dp[g1.scci[i]]++;
        g2.v[g1.scci[i]]++;
    }
    g2.topo(g1.scnt);
    int k{0},c{0};
    for(int i{1};i<=g1.scnt;i++){
        if(g2.dp[i]>k){
            k=g2.dp[i];c=g2.c[i];
        }
        else if(g2.dp[i]==k){
            c=(c+g2.c[i])%p;
        }
    }
    cout<<k<<"\n"<<c;
    cout<<std::endl;
    return 0;
}