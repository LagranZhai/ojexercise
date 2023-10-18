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

constexpr int maxn=1e5;
int p;
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
    operator int()const {
        return val;
    }
    operator bool()const {
        return (bool)val;
    }
};
namespace tcd {
    int siz[maxn*2],depth[maxn*2],hson[maxn*2],fa[maxn*2]
        ,dfn[maxn*2],cur=0,rnk[maxn*2],top[maxn*2];
   void lca(int x,int y,modint& v,std::function<void(int,int,modint&)> func){
        while(top[x]!=top[y]){
            if(depth[top[x]]<depth[top[y]]){
                std::swap(x,y);
            }
            func(dfn[top[x]],dfn[x],v);
            x=fa[top[x]];
        }
        if(depth[x]<depth[y]){
            std::swap(x,y);
        }
        func(dfn[y],dfn[x],v);
        return ;
    }
}
namespace segtree {
    modint tree[maxn*5],a[maxn*2],tag[maxn*5];
    void build(int cl,int cr,int p) {
        if(cl==cr){
            tree[p]=a[cl];
            tag[p]=0;
            return ;
        }
        int mid=(cl+cr)/2;
        build(cl,mid,p*2);
        build(mid+1,cr,p*2+1);
        tree[p]=tree[p*2]+tree[p*2+1];
        tag[p]=0;
        return ;
    }
    void pushdown(int p,int len){
        if(tag[p]){
            tag[p*2]+=tag[p];
            tag[p*2+1]+=tag[p];
            tree[p*2]+=tag[p]*(modint)(len-len/2);
            tree[p*2+1]+=tag[p]*(modint)(len/2);
            tag[p]=0;
            return ;
        }
        return ;
    }
    void query(int cl,int cr,int p,int l,int r,modint& ans) {
        if(cl>=l&&cr<=r){
            ans+=tree[p];
            return ;
        }
        if(cl<cr){
            pushdown(p,cr-cl+1);
            int mid=(cl+cr)/2;
            if(l<=mid)query(cl,mid,p*2,l,r,ans);
            if(r>mid)query(mid+1,cr,p*2+1,l,r,ans);
            return ;
        }
        return ;
    }
    void update(int cl,int cr,int p,int l,int r,modint d) {
        if(cl>=l&&cr<=r){
            tree[p]+=d*(modint)(cr-cl+1);
            tag[p]+=d;
            return ;
        }
        if(cl<cr){
            pushdown(p,cr-cl+1);
            int mid=(cl+cr)/2;
            if(l<=mid)update(cl,mid,p*2,l,r,d);
            if(r>mid)update(mid+1,cr,p*2+1,l,r,d);
            tree[p]=tree[p*2]+tree[p*2+1];
            return ;
        }
        return ;
    }
}
int n,m,r;
void cup(int x,int y,modint& z) {
    tcd::lca(x,y,z,[&](int a,int b,modint& c) {
            segtree::update(1,n,1,a,b,c);
            });
    return ;
}
void cqu(int x,int y,modint& z) {
    tcd::lca(x,y,z,[&](int a,int b,modint &c) {
            segtree::query(1,n,1,a,b,c);
            });
    return ;
}
int a[maxn*2];
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>m>>r>>p;
    for(int i{1};i<=n;i++)cin>>a[i];
{   
    int u,v;
    for(int i{1};i<n;i++){
        cin>>u>>v;
        addedge(u,v);addedge(v,u);
    }
}
using namespace tcd;
    auto dfs1=[&](int x,int f,auto&& self)->void {
        siz[x]=1;
        fa[x]=f;
        depth[x]=depth[f]+1;
        for(int e{head[x]};e;e=edg[e].nxt) {
            int to=edg[e].v;
            if(to==f)continue;
            self(to,x,self);
            siz[x]+=siz[to];
            if(siz[to]>siz[hson[x]])hson[x]=to;
        }
    };
    auto dfs2=[&](int x,int ctop,auto&& self)->void {
        dfn[x]=++cur;
        rnk[cur]=x;
        top[x]=ctop;
        if(hson[x]){
            self(hson[x],ctop,self);
        }
        for(int e{head[x]};e;e=edg[e].nxt){
            int to=edg[e].v;
            if(to!=hson[x]&&to!=fa[x]){
                self(to,to,self);
            }
        }
    };
 
    dfs1(r,0,dfs1);
    dfs2(r,r,dfs2);
    for(int i{1};i<=n;i++){
        segtree::a[i]=a[rnk[i]];
    }
    segtree::build(1,n,1);
{
    int opt,x,y,z;
    for(int i{1};i<=m;i++){
        cin>>opt;
        if(opt==1){
            cin>>x>>y>>z;
            cup(x,y,(modint&)z);
        }
        else if(opt==2){
            cin>>x>>y;
            modint ans{0};
            cqu(x,y,ans);
            cout<<(int)ans<<"\n";
        }
        else if(opt==3){
            using namespace tcd;
            cin>>x>>y;
            segtree::update(1,n,1,dfn[x],dfn[x]+siz[x]-1,y);
        }
        else if(opt==4){
            
            cin>>x;
            modint ans{0};
            segtree::query(1,n,1,dfn[x],dfn[x]+siz[x]-1,ans);
            cout<<(int)ans<<"\n";
        }
    }
}
    return 0;
}
