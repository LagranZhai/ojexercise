#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
using std::cin,std::ios,std::max,std::min;
template<typename T>
struct Myos{
    T mys;
    Myos(T&& _s)noexcept:mys(
        std::forward<T>(_s)
    ) {}
    Myos<T>& flush() {
        mys<<std::flush;
        return *this;
    }
    template<typename Traits>
    Myos<T>& operator<<(Traits&& value)noexcept {
        mys<<std::forward<Traits>(value);
        return *this;
    }
    ~Myos() {
        flush();
    }
};
template<> Myos<std::ostringstream>& Myos<std::ostringstream>::flush() {
        std::cout<<mys.str()<<std::flush;
        mys.str("");
        return *this;
}
//Myos<std::ostream&> cout{std::cout};
Myos<std::ostringstream> cout{std::ostringstream()};
constexpr int maxn=5e4;
int n,k;
struct Edge {
    int v=0,nxt=0;
}edg[maxn*3];
int head[maxn*2],cnt=0;
void addedge(int u_,int v_) {
    edg[++cnt].v=v_;
    edg[cnt].nxt=head[u_];
    head[u_]=cnt;
}
namespace tcd {
    int siz[maxn*2],depth[maxn*2],hson[maxn*2],fa[maxn*2]
        ,dfn[maxn*2],cur=0,rnk[maxn*2],top[maxn*2],d[maxn*2];
    void dfs1(int x,int f) {
        siz[x]=1;
        fa[x]=f;
        depth[x]=depth[f]+1;
        d[x]=0;
        for(int e{head[x]};e;e=edg[e].nxt) {
            int to=edg[e].v;
            if(to==f)continue;
            dfs1(to,x);
            siz[x]+=siz[to];
            if(siz[to]>siz[hson[x]])hson[x]=to;
        }
    }
    void dfs2(int x,int ctop) {
        dfn[x]=++cur;
        rnk[cur]=x;
        top[x]=ctop;
        if(hson[x]){
            dfs2(hson[x],ctop);
        }
        for(int e{head[x]};e;e=edg[e].nxt){
            int to=edg[e].v;
            if(to!=hson[x]&&to!=fa[x]){
                dfs2(to,to);
            }
        }
    }
    void lca(int x,int y,int& v,std::function<void(int,int,int&)> func) {
        while(top[x]!=top[y]){
            if(depth[top[x]]<depth[top[y]]){
                std::swap(x,y);
            }
            func(top[x],x,v);
            x=fa[top[x]];
        }
        if(depth[x]<depth[y]){
            std::swap(x,y);
        }
        func(y,x,v);
        return ;
    }
    int lca(int x,int y,std::function<void(int,int,int&)> func) {
        int t=0;
        lca(x,y,t,func);
        return t;
    }
    int dfs3(int x,int f,int &m) {
        int sum=d[x];
        for(int e{head[x]};e;e=edg[e].nxt) {
            int to=edg[e].v;
            if(to==f)continue;
            sum+=dfs3(to,x,m);
        }
        m=max(m,sum);
        return sum;
    }
}
void modify(int s,int t) {
    int lca=tcd::lca(s,t,[](int a,int b,int& c){
        c=a;
    });    
    tcd::d[s]++;
    tcd::d[t]++;
    tcd::d[lca]--;
    tcd::d[tcd::fa[lca]]--;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>k;
{
    int a,b;
    for(int i{1};i<n;i++){
        cin>>a>>b;
        addedge(a,b);
        addedge(b,a);
    }
}
    tcd::dfs1(1,0);
    tcd::dfs2(1,1);
{
    int s,t;
    for(int i{1};i<=k;i++){
        cin>>s>>t;
        modify(s,t);
    }
}
    int ans=0;
    tcd::dfs3(1,0,ans);
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}
