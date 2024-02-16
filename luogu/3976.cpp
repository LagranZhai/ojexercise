//P3976
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=5e4*2;
int n,a[maxn];
struct Edge{
    int v,nxt;
}edg[maxn*2];
int head[maxn],cnt{0};
void addedge(int u,int v){
    edg[++cnt]={v,head[u]};
    head[u]=cnt;
}
int fa[maxn],dep[maxn],siz[maxn],hson[maxn],top[maxn],dfn[maxn],rnk[maxn],tot{0};
void dfs1(int x,int f){
    fa[x]=f;
    siz[x]=1;
    dep[x]=dep[f]+1;
    hson[x]=0;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            dfs1(to,x);
            siz[x]+=siz[to];
            if(siz[to]>siz[hson[x]])hson[x]=to;
        }
    }
}
void dfs2(int x,int f,int ctop){
    dfn[x]=++tot;
    rnk[tot]=x;
    top[x]=ctop;
    if(hson[x]){
        dfs2(hson[x],x,ctop);
    }
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=hson[x]&&to!=f){
            dfs2(to,x,to);
        }
    }
}
struct Node{
    int min,max,ans1,ans2;
    int tag;
    Node(const Node &A)=default;
    Node operator+(const Node &A){
        return (Node){std::min(min,A.min),std::max(max,A.max),std::max({ans1,A.ans1,max-A.min,0ll}),std::max({ans2,A.ans2,A.max-min,0ll}),0};
    }
    Node& operator=(Node &&A){
        min=A.min;max=A.max;ans1=A.ans1;ans2=A.ans2;tag=A.tag;
        return *this;
    }
    void apply(int t){
        min+=t;
        max+=t;
        tag+=t;
        return ;
    }
}C{std::numeric_limits<int>::max()/2,0,0,0,0},tree[maxn*4]{C};
void pushdown(int p){
    if(tree[p].tag!=0){
        tree[p*2].apply(tree[p].tag);
        tree[p*2+1].apply(tree[p].tag);
        tree[p].tag=0;
    }
}
void build(int p,int cl,int cr){
    if(cl==cr){
        tree[p]={a[rnk[cl]],a[rnk[cl]],0,0,0};
        return ;
    }
    int mid{(cl+cr)/2};
    build(p*2,cl,mid);build(p*2+1,mid+1,cr);
    tree[p]=tree[p*2]+tree[p*2+1];
}
Node query(int p,int cl,int cr,int l,int r){
    if(cl>=l&&cr<=r){
        return tree[p];
    }
    if(cl!=cr){
        pushdown(p);
        int mid{(cl+cr)/2};
        Node lans{C},rans{C};
        if(l<=mid)lans=query(p*2,cl,mid,l,r);
        if(mid<r)rans=query(p*2+1,mid+1,cr,l,r);
        return lans+rans;
    }
    return C;
}
void update(int p,int cl,int cr,int l,int r,int d){
    if(cl>=l&&cr<=r){
        tree[p].apply(d);
        return ;
    }
    if(cl!=cr){
        pushdown(p);
        int mid{(cl+cr)/2};
        if(l<=mid)update(p*2,cl,mid,l,r,d);
        if(r>mid)update(p*2+1,mid+1,cr,l,r,d);
        tree[p]=tree[p*2]+tree[p*2+1];
    }
}
int modifyandask(int x,int y,int w){
    bool now{0};
    Node ans[2]={C,C};
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            now^=1;
            std::swap(x,y);
        }
        ans[now]=query(1,1,n,dfn[top[x]],dfn[x])+ans[now];
        update(1,1,n,dfn[top[x]],dfn[x],w);
        x=fa[top[x]];
    }
    if(dep[x]<dep[y]){
        now^=1;
        std::swap(x,y);
    }
    ans[now]=query(1,1,n,dfn[y],dfn[x])+ans[now];
    update(1,1,n,dfn[y],dfn[x],w);
    return std::max({ans[0].ans1,ans[1].ans2,ans[1].max-ans[0].min});
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n;
    for(int i{1};i<=n;i++){
        cin>>a[i];
    }
    int x,y;
    for(int i{1};i<n;i++){
        cin>>x>>y;
        addedge(x,y);addedge(y,x);
    }
    dfs1(1,0);dfs2(1,0,1);
    build(1,1,n);
    // cout<<tree[1].max<<"\n";
    int q,w;
    cin>>q;
    for(int i{1};i<=q;i++){
        cin>>x>>y>>w;
        cout<<modifyandask(x,y,w)<<"\n";
    }
    cout.flush();
    return 0;
}