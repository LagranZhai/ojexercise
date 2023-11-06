#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
constexpr int maxn=5e5;
struct Edge{
    int v{0},nxt{0};
}edg[maxn*3];
int head[maxn*2],cnt{0};
void addedge(int u,int v){
    edg[++cnt].v=v;
    edg[cnt].nxt=head[u];
    head[u]=cnt;
    return ;
}
int n,m;
int a[maxn*2]{};
int siz[maxn*2],dfn[maxn*2],rnk[maxn*2],dep[maxn*2],tot{0};
void dfs(int x,int f){
    dep[x]=dep[f]+1;
    siz[x]=1;
    dfn[x]=++tot;
    rnk[tot]=x;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            dfs(to,x);
            siz[x]+=siz[to];
        }
    }
}
struct segt{
    struct Tag{
        int add{0};
        void compose(Tag A){
            add+=A.add;
        }
    };
    struct Data{
        int sum{0},len{0};
        Data operator+(Data A){
            return {sum+A.sum,len+A.len};
        }
        void apply(Tag A){
            sum+=A.add*len;
        }
    };
    struct dm{
        Data d{};Tag t{};
    }tree[maxn*4];
    void pushdown(int p){
        if(tree[p].t.add!=0){
            tree[p*2].d.apply(tree[p].t);
            tree[p*2].t.compose(tree[p].t);
            tree[p*2+1].d.apply(tree[p].t);
            tree[p*2+1].t.compose(tree[p].t);
            tree[p].t=Tag{};
        }
    }
    void build(int p,int cl,int cr){
        if(cl==cr){
            tree[p].d.len=1;
            tree[p].d.sum=a[rnk[cl]];
            return ;
        }
        int mid=(cl+cr)/2;
        build(p*2,cl,mid);
        build(p*2+1,mid+1,cr);
        tree[p].d=tree[p*2].d+tree[p*2+1].d;
    }
    void update(int p,int cl,int cr,int l,int r,Tag w){
        if(cl>=l&&cr<=r){
            tree[p].d.apply(w);
            tree[p].t.compose(w);
            return ;
        }
        if(cl!=cr){
            pushdown(p);
            int mid=(cl+cr)/2;
            if(l<=mid)update(p*2,cl,mid,l,r,w);
            if(r>mid)update(p*2+1,mid+1,cr,l,r,w);
            tree[p].d=tree[p*2].d+tree[p*2+1].d;
        }
    }
    int query(int p,int cl,int cr,int d){
        if(cl==d&&cr==d){
            return tree[p].d.sum;
        }
        if(cl!=cr){
            pushdown(p);
            int mid=(cl+cr)/2;
            if(d<=mid)return query(p*2,cl,mid,d);
            if(d>mid)return query(p*2+1,mid+1,cr,d);
        }
        return 0;
    }
}colt[2];
int col[maxn*2];
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    for(int i{1};i<=n;i++){
        cin>>a[i];
    }
    int u,v;
    for(int i{1};i<n;i++){
        cin>>u>>v;
        addedge(u,v);addedge(v,u);
    }
    dfs(1,0);
    colt[0].build(1,1,n);
    colt[1].build(1,1,n);
    int c;
    for(int i{1};i<=m;i++){
        cin>>c;
        if(c==1){
            cin>>u>>v;
            colt[dep[u]%2].update(1,1,n,dfn[u],dfn[u]+siz[u]-1,{v});
            colt[dep[u]%2^1].update(1,1,n,dfn[u],dfn[u]+siz[u]-1,{-v});
        }
        if(c==2){
            cin>>u;
            cout<<colt[dep[u]%2].query(1,1,n,dfn[u])<<"\n";
        }
    }
    cout<<std::flush;
    return 0;
}