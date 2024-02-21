//PC
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=3e5,maxm=2e6;
const int inf{std::numeric_limits<int>::min()};
int p{114514};
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
    int dis[maxn],v[maxn],mcnt[maxn]{};
    bool inq[maxn]{};
    bool spfa(int n,int s){
        std::fill(dis,dis+maxn,inf);
        std::fill(inq,inq+maxn,false);
        std::fill(mcnt,mcnt+maxn,0);
        std::queue<int > q{};
        dis[s]=0;
        inq[s]=true;
        mcnt[s]=1;
        q.push(s);
        while(!q.empty()){
            int cur{q.front()};
            q.pop();
            inq[cur]=0;
            for(int e{head[cur]};e;e=edg[e].nxt){
                int to{edg[e].v};
                if(dis[cur]!=inf&&dis[to]<dis[cur]+v[to]){
                    dis[to]=dis[cur]+v[to];
                    mcnt[to]=mcnt[cur]+1;
                    if(mcnt[to]>n)return true;
                    if(!inq[to]){
                        q.push(to);
                        inq[to]=1;
                    }
                }
            }
        }
        return false;
    }
    G(){
        for(int* a:{head,dfn,low,scci,v}){
            std::fill(a,a+maxn,0);
        }
    }
}g1{},g2{},g3{};
int n,m;
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
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
            g3.addedge(g1.scci[a.second],g1.scci[a.first]);
        }
    }
    for(int i{1};i<=n;i++){
        g2.v[g1.scci[i]]++;
        g3.v[g1.scci[i]]++;
    }
    int s{g1.scci[1]};
    g2.spfa(g1.scnt,s);
    g3.spfa(g1.scnt,s);
    int ans{0};
    for(auto a:e){
        if(g1.scci[a.first]!=g1.scci[a.second]){
            if(g3.dis[g1.scci[a.first]]!=inf&&g2.dis[g1.scci[a.second]]!=inf){
                ans=std::max(ans,g3.dis[g1.scci[a.first]]+g2.dis[g1.scci[a.second]]);
            }
        }
    }
    cout<<ans+g2.v[s];
    cout<<std::endl;
    return 0;
}