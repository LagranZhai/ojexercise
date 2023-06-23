#include <iostream>
#include <sstream>
#include <algorithm>
#include<functional>
using std::cin;
using std::ios;
template<typename T>
struct Myos{
    T mys;
    Myos(T&& s_)noexcept:mys(std::forward<T>(s_)) {}
    ~Myos()noexcept {
        std::cout<<std::flush;
    }
};
template<> Myos<std::stringstream>::~Myos()noexcept {
    std::cout<<mys.str()<<std::flush;
}
//Myos<std::ostream&> t{std::cout};
Myos<std::stringstream> t{std::stringstream()};
auto& cout=t.mys;
//auto& cout1=t1.mys;

constexpr int maxn=300000,maxk=50;
constexpr int p{998244353};
int head[maxn*3],cnt=0;

struct Edge{
    int v=0,nxt=0;
}edg[maxn*3];
void addedge(int u_,int v_) {
    edg[++cnt].v=v_;
    edg[cnt].nxt=head[u_];
    head[u_]=cnt;
}
struct modint{
    int val{0};
    modint(int a=0):val(a) {}
    //modint(long long a=0):val(a) {}
    modint operator+(const modint a)const {
        return (0ll+val+a.val)%p;
    }
    modint operator-(const modint a)const {
        return (0ll+val-a.val+p)%p;
    }
    modint operator*(const modint a)const {
        return 1ll*val*a.val%p;
    }
    void operator+=(const modint a) {
        this->val=*this+a;
        return ;
    }
    void operator-=(const modint a) {
        this->val=*this-a;
        return ;
    }
    operator int()const {
        return val;
    }
    operator bool()const {
        return (bool)val;
    }
};
modint qpow(modint a,int b) {
    modint c{1};
    while(b){
        if(b&1)c=c*a;
        a=a*a;
        b>>=1;
    }
    return c;
}
namespace tcd {
    int siz[maxn*2],depth[maxn*2],hson[maxn*2],fa[maxn*2]
        ,dfn[maxn*2],cur=0,rnk[maxn*2],top[maxn*2];
    modint sum[maxk+2][maxn*2];
    void dfs1(int x,int f) {
        siz[x]=1;
        fa[x]=f;
        depth[x]=depth[f]+1;
        for(int i{1};i<=50;i++){
            sum[i][x]=sum[i][f]+qpow(depth[x]-1,i);
        }
        for(int e{head[x]};e;e=edg[e].nxt) {
            int to=edg[e].v;
            if(to==f)continue;
            dfs1(to,x);
            siz[x]+=siz[to];
            if(siz[to]>siz[hson[x]])hson[x]=to;
        }
    }
    void dfs2(int x,int f,int ctop) {
        dfn[x]=++cur;
        rnk[cur]=x;
        top[x]=ctop;
        if(hson[x]){
            dfs2(hson[x],x,ctop);
        }
        for(int e{head[x]};e;e=edg[e].nxt){
            int to=edg[e].v;
            if(to!=hson[x]&&to!=f){
                dfs2(to,x,to);
            }
        }
    }
    void lca(int x,int y,modint& v,std::function<void(int,modint&)> func){
        while(top[x]!=top[y]){
            if(depth[top[x]]<depth[top[y]]){
                std::swap(x,y);
            }
            x=fa[top[x]];
        }
        if(depth[x]<depth[y]){
            std::swap(x,y);
        }
        func(y,v);
        return ;
    }
}
int n,m;
void getsum(int x,int y,int k,modint& z) {
    using tcd::sum,tcd::fa;
    z+=sum[k][x]+sum[k][y];
    tcd::lca(x,y,z,[&](int a,modint& c) {
         c-=sum[k][fa[a]]+sum[k][a];
    });
    return ;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n;
{   
    int u,v;
    for(int i{1};i<n;i++){
        cin>>u>>v;
        addedge(u,v);addedge(v,u);
    }
}
    tcd::dfs1(1,0);
    tcd::dfs2(1,0,1);
    cin>>m;
{
    int x,y,z;
    for(int i{1};i<=m;i++){
        cin>>x>>y>>z;
        modint ans{0};
        getsum(x,y,z,ans);
        cout<<(int)ans<<"\n";
    }
}
    return 0;
}
