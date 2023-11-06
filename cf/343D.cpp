#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
constexpr int maxn=5e5;
struct Edge{
    int v{},nxt{};
}edg[maxn*3];
int head[maxn*2],cnt{0};
void addedge(int u,int v){
    edg[++cnt].v=v;
    edg[cnt].nxt=head[u];
    head[u]=cnt;
    return ;
}
int n,q;
int a[maxn*2]{};
int fa[maxn*2],dep[maxn*2],siz[maxn*2],hson[maxn*2];
void dfs1(int x,int f){
    fa[x]=f;
    dep[x]=dep[f]+1;
    siz[x]=1;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            dfs1(to,x);
            siz[x]+=siz[to];
            if(siz[to]>siz[hson[x]])hson[x]=to;
        }
    }
}
int dfn[maxn*2],rnk[maxn*2],top[maxn*2],tot{0};
void dfs2(int x,int f,int ctop){
    dfn[x]=++tot;
    rnk[tot]=x;
    top[x]=ctop;
    if(hson[x]){
        dfs2(hson[x],x,ctop);
    }
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f&&to!=hson[x]){
            dfs2(to,x,to);
        }
    }
}
struct Tag{
    int cov{};
    void compose(Tag A){
        cov=A.cov;
    }
};
struct Data{
    int val{},len{};
    Data operator+(Data A){
        return {0,len+A.len};
    }
    void apply(Tag A){
        if(len==1){
            val=A.cov;
        }
    }
};
struct dm{
    Data d{};Tag t{};
}tree[maxn*4];
void pushdown(int p){
    if(tree[p].t.cov!=-1){
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
        return tree[p].d.val;
    }
    if(cl!=cr){
        pushdown(p);
        int mid=(cl+cr)/2;
        if(d<=mid)return query(p*2,cl,mid,d);
        if(d>mid)return query(p*2+1,mid+1,cr,d);
    }
    return 0;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n;
    int u,v;
    for(int i{1};i<n;i++){
        cin>>u>>v;
        addedge(u,v);addedge(v,u);
    }
    dfs1(1,0);
    dfs2(1,0,1);
    build(1,1,n);
    cin>>q;
    int c;
    for(int i{1};i<=q;i++){
        cin>>c;
        if(c==1){
            cin>>u;
            update(1,1,n,dfn[u],dfn[u]+siz[u]-1,{1});
        }
        if(c==2){
            cin>>u;
            while(top[u]!=1){
                update(1,1,n,dfn[top[u]],dfn[u],{0});
                u=fa[top[u]];
            }
            update(1,1,n,dfn[top[u]],dfn[u],{0});
        }
        if(c==3){
            cin>>u;
            cout<<query(1,1,n,dfn[u])<<"\n";
        }
    }
    cout<<std::flush;
    return 0;
}