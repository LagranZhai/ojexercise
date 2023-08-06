#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<set>
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
constexpr int maxn=1e5;
struct Edge{
    int v{0},nxt{0};
}edg[maxn*3];
int head[maxn*2],cnt=0;
void addedge(int u,int v){
    edg[++cnt].v=v;
    edg[cnt].nxt=head[u];
    head[u]=cnt;
    return ;
}
int n,q;
namespace tcd{
    int fa[maxn*2],hson[maxn*2],siz[maxn*2],depth[maxn*2],
        dfn[maxn*2],rnk[maxn*2],top[maxn*2],cur{0};
    void dfs1(int x,int f){
        fa[x]=f;
        depth[x]=depth[f]+1;
        siz[x]=1;
        for(int e{head[x]};e;e=edg[e].nxt){
            int to=edg[e].v;
            if(to!=f){
                dfs1(to,x);
                siz[x]+=siz[to];
                if(siz[to]>siz[hson[x]])hson[x]=to;
            }
        }
        return ;
    }
    void dfs2(int x,int ctop){
        dfn[x]=++cur;
        rnk[cur]=x;
        top[x]=ctop;
        if(hson[x]){
            dfs2(hson[x],ctop);
        }
        for(int e{head[x]};e;e=edg[e].nxt){
            int to=edg[e].v;
            if(to!=fa[x]&&to!=hson[x]){
                dfs2(to,to);
            }
        }
    }
}
namespace segtree {
    int tree[maxn*5];
    bool a[maxn*2];
    void build(int cl,int cr,int p) {
        if(cl==cr){
            tree[p]=a[cl];
            return ;
        }
        int mid=(cl+cr)/2;
        build(cl,mid,p*2);
        build(mid+1,cr,p*2+1);
        tree[p]=tree[p*2]+tree[p*2+1];
        return ;
    }
    int query(int cl,int cr,int p,int l,int r) {
        if(cl>=l&&cr<=r){
            return tree[p];
        }
        if(cl<cr){
            int mid=(cl+cr)/2;
            int ans=0;
            if(l<=mid)ans+=query(cl,mid,p*2,l,r);
            if(r>mid)ans+=query(mid+1,cr,p*2+1,l,r);
            return ans;
        }
        return 0;
    }
    void update(int cl,int cr,int p,int l,int d) {
        if(cl==l&&cr==l){
            tree[p]=d;
            return ;
        }
        if(cl<cr){
            int mid=(cl+cr)/2;
            if(l<=mid)update(cl,mid,p*2,l,d);
            if(l>mid)update(mid+1,cr,p*2+1,l,d);
            tree[p]=tree[p*2]+tree[p*2+1];
            return ;
        }
        return ;
    }
    int find(int cl,int cr,int p,int l,int r){
        if(cl==cr){
            if(tree[p]==1&&cl>=l&&cr<=r)return cl;
            else return 0;
        }
        int mid=(cl+cr)/2;
        if(r>mid&&tree[p*2+1]>0){
            int x=find(mid+1,cr,p*2+1,l,r);
            if(x>0)return x;
        }
        if(l<=mid&&tree[p*2]>0){
            int x=find(cl,mid,p*2,l,r);
            if(x>0)return x;
        }
        return 0;
    }
    int lcm(int p){
        using namespace tcd;
        // if(!query(1,n,1,dfn[top[p]],dfn[p])){
        //     p=fa[top[p]];
        //     while(p!=0){
        //         if(!query(1,n,1,dfn[top[p]],dfn[p]))p=fa[top[p]];
        //         else return rnk[std::upper_bound(dfn[top[p]],dfn[p]+1,0)];
        //     }
        // }
        // else{
        //     return rnk[*(--chain[cset[p]].upper_bound(dfn[p]))];
        // }
        while(p!=0){
            if(!query(1,n,1,dfn[top[p]],dfn[p]))p=fa[top[p]];
            else return rnk[find(1,n,1,dfn[top[p]],dfn[p])];
        }
    }
    void mark(int p){
        using namespace tcd;
        if(!a[dfn[p]]){
            a[dfn[p]]=1;
            segtree::update(1,n,1,dfn[p],1);
        }
        return ;
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>q;
    {
        int u,v;
        for(int i{1};i<n;i++){
            cin>>u>>v;
            addedge(u,v);addedge(v,u);
        }
    }
    tcd::dfs1(1,0);
    tcd::dfs2(1,1);
    segtree::build(1,n,1);
    segtree::mark(1);
    {
        char opt;
        int num;
        for(int i{1};i<=q;i++){
            cin>>opt>>num;
            if(opt=='C'){
                segtree::mark(num);
            }
            else if(opt=='Q'){
                cout<<segtree::lcm(num)<<"\n";
            }
        }
    }
    return 0;
}