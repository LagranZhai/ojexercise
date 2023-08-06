#include <iostream>
#include <sstream>
#include <algorithm>
#include<functional>
using std::cin;
using std::ios;
using std::max;
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

int head[maxn*3],cnt=0,cnt1=0;
using modint=int;
struct Edge{
    int u=0,v=0,nxt=0,w=0;
}edg[maxn*3];
struct Edge1{
    int u=0,v=0,w=0;
}edg1[maxn*2];
void addedge(int u_,int v_,int w_) {
    edg[++cnt].v=v_;
    edg[cnt].u=u_;
    edg[cnt].w=w_;
    edg[cnt].nxt=head[u_];
    head[u_]=cnt;
}
void addedge1(int u_,int v_,int w_) {
    edg1[++cnt1].u=u_;
    edg1[cnt1].v=v_;
    edg1[cnt1].w=w_;
}
namespace tcd {
    int siz[maxn*2],depth[maxn*2],hson[maxn*2],fa[maxn*2]
        ,dfn[maxn*2],cur=0,rnk[maxn*2],top[maxn*2];
    void dfs1(int fe,int f) {
        int x=edg[fe].v;
        siz[x]=1;
        fa[x]=fe;
        depth[x]=depth[f]+1;
        for(int e{head[x]};e;e=edg[e].nxt) {
            int to=edg[e].v;
            if(to==f)continue;
            dfs1(e,to);
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
            if(to!=hson[x]&&to!=edg[fa[x]].u){
                dfs2(to,to);
            }
        }
    }
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
        if(depth[x]!=depth[y])func(dfn[y],dfn[x]-1,v);
        return ;
    }
}

namespace segtree {
    modint tree[maxn*5],a[maxn*2],tag[maxn*5],tag1[maxn*5];
    void build(int cl,int cr,int p) {
        if(cl==cr){
            tree[p]=a[cl];
            tag[p]=-1;tag1[p]=0;
            return ;
        }
        int mid=(cl+cr)/2;
        build(cl,mid,p*2);
        build(mid+1,cr,p*2+1);
        tree[p]=std::max(tree[p*2],tree[p*2+1]);
        tag[p]=-1;tag1[p]=0;
        return ;
    }
    void pushdown(int p,int len){
        if(tag[p]!=-1){
            tag[p*2]=tag[p];
            tag1[p*2]=0;
            tag[p*2+1]=tag[p];
            tag1[p*2+1]=0;
            tree[p*2]=tag[p];
            tree[p*2+1]=tag[p];
            tag[p]=-1;tag1[p]=0;
        }
        if(tag1[p]){
            if(tag[p*2]!=-1){
                tag[p*2]+=tag[p];
                tree[p*2]=tag[p*2];
            }
            else{
                tag1[p*2]+=tag1[p];
                tree[p*2]+=tag1[p];
            }
            if(tag[p*2+1]!=-1){
                tag[p*2+1]+=tag[p];
                tree[p*2+1]=tag[p*2];
            }
            else{
                tag1[p*2+1]+=tag1[p];
                tree[p*2+1]+=tag1[p];
            }
            tag1[p]=0;tag[p]=-1;
        }
        return ;
    }
    void query(int cl,int cr,int p,int l,int r,modint& ans) {
        if(cl>=l&&cr<=r){
            ans=max(tree[p],ans);
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
            tree[p]=d;
            tag[p]=d;
            tag1[p]=0;
            return ;
        }
        if(cl<cr){
            pushdown(p,cr-cl+1);
            int mid=(cl+cr)/2;
            if(l<=mid)update(cl,mid,p*2,l,r,d);
            if(r>mid)update(mid+1,cr,p*2+1,l,r,d);
            tree[p]=max(tree[p*2],tree[p*2+1]);
            return ;
        }
        return ;
    }
    void update1(int cl,int cr,int p,int l,int r,modint d) {
        if(cl>=l&&cr<=r){
            if(tag[p]!=-1){
                tree[p]+=d;
                tag[p]+=d;
            }
            else{
                tree[p]+=d;
                tag1[p]+=d;
            }
            return ;
        }
        if(cl<cr){
            pushdown(p,cr-cl+1);
            int mid=(cl+cr)/2;
            if(l<=mid)update(cl,mid,p*2,l,r,d);
            if(r>mid)update(mid+1,cr,p*2+1,l,r,d);
            tree[p]=max(tree[p*2],tree[p*2+1]);
            return ;
        }
        return ;
    }
}
int n;
void cup(int x,int y,modint& z) {
    auto l=[&](int a,int b,modint& c) {segtree::update(1,n,1,a,b,c);};
    tcd::lca(x,y,z,l);
    return ;
}
void cup1(int x,int y,modint& z) {
    auto l=[&](int a,int b,modint& c) {segtree::update1(1,n,1,a,b,c);};
    //auto l1=[&](int a,int b,modint& c) {segtree::update(1,n,1,a,b-1,c);}
    tcd::lca(x,y,z,l);
    return ;
}
void cqu(int x,int y,modint& z) {
    tcd::lca(x,y,z,[&](int a,int b,modint &c) {
            segtree::query(1,n,1,a,b,c);
            });
    return ;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n;
{   
    int u,v,w;
    for(int i{1};i<n;i++){
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
        addedge1(u,v,w);
    }
}
    addedge(0,1,0);
    tcd::dfs1(cnt,0);
    tcd::dfs2(1,1);
    for(int i{1};i<=n;i++){
        segtree::a[i]=edg[tcd::fa[tcd::rnk[i]]].w;
    }
    segtree::build(1,n,1);
{
    int u,v,w;
    std::string s;
    while(true){
        if(s=="Stop")break;
        else if(s=="Change"){
            cin>>u>>w;
            int u_=edg1[u].u,v_=edg1[u].v;
            if(tcd::depth[v_]<tcd::depth[u_])std::swap(u_,v_);
            cup(v_,v_,w);
        }
        else if(s=="Cover"){
            cin>>u>>v>>w;
            cup(u,v,w);
        }
        else if(s=="Add"){
            cin>>u>>v;
            int ans{0};
            cqu(u,v,ans);
            cout<<ans<<"\n";
        }
    }
    /*for(int i{1};i<=m;i++){
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
            using namespace tcd;
            cin>>x;
            modint ans{0};
            segtree::query(1,n,1,dfn[x],dfn[x]+siz[x]-1,ans);
            cout<<(int)ans<<"\n";
        }
    }*/
}
    cout.flush();
    return 0;
}
