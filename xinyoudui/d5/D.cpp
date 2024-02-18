//PD
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=1e6;
int n,m;
struct Edge{
    int v,nxt,l,a,u;
}edg[maxn];
int head[maxn],cnt{0};
void addedge(int u,int v,int l,int a){
    edg[++cnt]={v,head[u],l,a,u};
    head[u]=cnt;
}
int dis[maxn];
void dijkstra(int s=1){
    std::fill(dis,dis+n+1,std::numeric_limits<int>::max()>>2);
    using pii=std::pair<int,int>;
    auto cmp=[](const pii& A,const pii& B){return A.first>B.first;};
    std::priority_queue<pii,std::vector<pii> ,decltype(cmp)> q(cmp);
    dis[s]=0;q.push({0,s});
    while(!q.empty()){
        int cur{q.top().second};
        if(dis[cur]>=q.top().first){
            for(int e{head[cur]};e;e=edg[e].nxt){
                int to{edg[e].v};
                if(dis[to]>dis[cur]+edg[e].l){
                    dis[to]=dis[cur]+edg[e].l;
                    q.push({dis[to],to});
                }
            }
        }
        q.pop();
    }
}
namespace hpd{
    int n;
    int a[maxn],val[maxn];
    std::vector<int> g[maxn];
    int siz[maxn],fa[maxn],dep[maxn],hson[maxn],top[maxn],dfn[maxn],rnk[maxn];
    int tot{0};
    void init(){
        for(auto p:{siz,fa,dep,hson,top,dfn,val,rnk}){
            std::fill(p,p+n,0);
        }
        tot=0;
    }
    void dfs1(int x,int f){
        fa[x]=f;
        siz[x]=1;
        dep[x]=dep[f]+1;
        hson[x]=0;
        if(x>::n)val[x]=std::numeric_limits<int>::max();
        else{
            val[x]=dis[x];
            a[x]=std::numeric_limits<int>::max();
        }
        for(int to:g[x]){
            dfs1(to,x);
            val[x]=std::min(val[x],val[to]);
            siz[x]+=siz[to];
            if(siz[to]>siz[hson[x]]){
                hson[x]=to;
            }
        }
    }
    void dfs2(int x,int ctop){
        top[x]=ctop;
        dfn[x]=++tot;
        rnk[tot]=x;
        if(hson[x]){
            dfs2(hson[x],ctop);
        }
        for(int to:g[x]){
            if(to!=hson[x]){
                dfs2(to,to);
            }
        }
    }
    int getans(int x,int s){
        while(top[x]!=n&&a[fa[top[x]]]>s){
            x=fa[top[x]];
        }
        auto pos=std::lower_bound(rnk+dfn[top[x]],rnk+dfn[x]+1,s,[](const int &A,const int &B){
            return a[A]<=B;
        });
        return val[*pos];
    }
}
namespace dsu{
    int fa[maxn];
    int getf(int x){
        return fa[x]==x?x:fa[x]=getf(fa[x]);
    }
    void kruskal(){
        for(int i{1};i<=2*n;i++){
            fa[i]=i;
        }
        std::fill(hpd::g,hpd::g+n*2,std::vector<int>{});
        std::fill(hpd::a,hpd::a+n*2,0);
        hpd::n=n;
        std::sort(edg+1,edg+cnt+1,[](const Edge& A,const Edge& B){return A.a>B.a;});
        for(int i{1};i<=cnt;i++){
            int u{edg[i].u},v{edg[i].v};
            int fx{getf(u)},fy{getf(v)};
            if(fx!=fy){
                hpd::n++;
                fa[fx]=fa[fy]=hpd::n;
                hpd::a[hpd::n]=edg[i].a;
                hpd::g[hpd::n].push_back(fx);hpd::g[hpd::n].push_back(fy);
                if(hpd::n==2*n-1)break;
            }
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int T;cin>>T;
    while(T--){
        cin>>n>>m;
        int u,v,l,a;
        for(int i{};i<m;i++){
            cin>>u>>v>>l>>a;
            addedge(u,v,l,a);
            addedge(v,u,l,a);
        }
        dijkstra();
        dsu::kruskal();
        hpd::init();
        hpd::dfs1(hpd::n,0);
        hpd::dfs2(hpd::n,hpd::n);
        int Q,K,S;
        cin>>Q>>K>>S;
        l=0;
        for(int i{};i<Q;i++){
            cin>>u>>v;
            u=(u+K*l-1)%n+1;
            v=(v+K*l)%(S+1);
            cout<<(l=hpd::getans(u,v))<<"\n";
        }
        std::fill(edg,edg+cnt+1,Edge{});
        cnt=0;
        std::fill(head,head+n+1,0);
    }
    cout.flush(); 
    return 0;
}