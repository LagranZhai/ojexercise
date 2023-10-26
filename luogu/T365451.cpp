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
constexpr int maxn=500;
struct tree{    
    using modint=int;
    int head[maxn*3]={0},cnt=0;
    struct Edge{
        int v=0,nxt=0;
    }edg[maxn*3];
    void addedge(int u_,int v_) {
        edg[++cnt].v=v_;
        edg[cnt].nxt=head[u_];
        head[u_]=cnt;
    }
        int siz[maxn*2]={0},depth[maxn*2]={0},hson[maxn*2]={0},fa[maxn*2]={0}
            ,dfn[maxn*2]={0},cur=0,rnk[maxn*2]={0},top[maxn*2]={0};
        void dfs1(int x,int f) {
            siz[x]=1;
            fa[x]=f;
            depth[x]=depth[f]+1;
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
        void lca(int x,int y,int* v,std::function<void(int,int,int*,tree*)> func){
            while(top[x]!=top[y]){
                if(depth[top[x]]<depth[top[y]]){
                    std::swap(x,y);
                }
                func(dfn[top[x]],dfn[x],v,this);
                x=fa[top[x]];
            }
            if(depth[x]<depth[y]){
                std::swap(x,y);
            }
            func(dfn[y],dfn[x],v,this);
            return ;
        }
}trees[maxn+10];
int n,k;
int cnt[maxn+10];
int solve(int u,int v){
    std::fill(cnt,cnt+maxn+10,0);
    for(int i=1;i<=k;i++){
        trees[i].lca(u,v,cnt,[](int x,int y,int* v,tree* t){
            for(int j{x};j<=y;j++){
                v[t->rnk[j]]++;
            }
        });
    }
    int ans=0;
    for(int i{1};i<=n;i++){
        if(cnt[i]==k)ans++;
    }
    return ans;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>k;
    int u,v;
    for(int i{1};i<=k;i++){
        for(int j{1};j<n;j++){
            cin>>u>>v;
            trees[i].addedge(u,v);
            trees[i].addedge(v,u);
        }
    }
    for(int i{1};i<=k;i++){
        trees[i].dfs1(1,0);
    }
    for(int i{1};i<=k;i++){
        trees[i].dfs2(1,1);
    }
    for(int i{1};i<=n;i++){
        for(int j{1};j<=n;j++){
            cout<<solve(i,j)<<" ";
        }
        cout<<"\n";
    }
    cout.flush();
    return 0;
}
