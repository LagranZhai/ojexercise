//P3703
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=4e5,maxm=4e5;
int n,m;
struct Edge{
    int v,nxt;
}edg[maxn*2];
int head[maxn],cnt{0};
void addedge(int u,int v){
    edg[++cnt]={v,head[u]};
    head[u]=cnt;
}
namespace Seg{
    int tree[maxn*4],tag[maxn];
    void build(int p,int cl,int cr);
    void pushdown(int p){
        if(tag[p]){
            tree[p*2]+=tag[p];
            tag[p*2]+=tag[p];
            tree[p*2+1]+=tag[p];
            tag[p*2+1]+=tag[p];
            tag[p]=0;
        }
    }
    void query(int p,int cl,int cr,int l,int r,int &ans){
        if(cl>=l&&cr<=r){
            ans=std::max(ans,tree[p]);
            return ;
        }
        if(cl!=cr){
            pushdown(p);
            int mid{(cl+cr)/2};
            if(l<=mid)query(p*2,cl,mid,l,r,ans);
            if(mid<r)query(p*2+1,mid+1,cr,l,r,ans);
        }
    }
    void update(int p,int cl,int cr,int l,int r,int d){
        if(cl>=l&&cr<=r){
            tree[p]+=d;
            tag[p]+=d;
            return ;
        }
        if(cl!=cr){
            pushdown(p);
            int mid{(cl+cr)/2};
            if(l<=mid)update(p*2,cl,mid,l,r,d);
            if(r>mid)update(p*2+1,mid+1,cr,l,r,d);
            tree[p]=std::max(tree[p*2],tree[p*2+1]);
        }
    }
}
namespace Lct{
    int fa[maxn],ch[maxn][2];
    bool tag[maxn];
    int chk(int x){
        if(x==ch[fa[x]][0])return 0;
        if(x==ch[fa[x]][1])return 1;
        return -1;
    }
    void func(int x){
        if(x){
            std::swap(ch[x][0],ch[x][1]);
            tag[x]^=1;
        }
    }
    void pushdown(int x){
        if(x&&tag[x]){
            func(ch[x][0]);
            func(ch[x][1]);
            tag[x]=0;
        }
    }
    void reverse_pushdown(int x){
        if(chk(x)!=-1)reverse_pushdown(fa[x]);
        pushdown(x);
    }
    void spin(int x){
        int f{fa[x]},dir{chk(x)},ff{fa[f]};
        if(dir==-1)return ;
        if(chk(f)!=-1)ch[ff][chk(f)]=x;
        if(ch[x][dir^1])fa[ch[x][dir^1]]=f;
        ch[f][dir]=ch[x][dir^1];ch[x][dir^1]=f;
        fa[f]=x;fa[x]=ff;
        return ;
    }
    void splay(int x,int des=0){
        reverse_pushdown(x);
        int f{fa[x]};
        while(chk(x)!=-1&&f!=des){
            if(chk(f)!=-1&&fa[f]!=des)spin(chk(f)==chk(x)?f:x);
            spin(x);
            f=fa[x];
        }
    }
    int access(int x);
    int findlow(int x){
        int cur{x};
        pushdown(x);
        while(ch[cur][0]){
            cur=ch[cur][0];
            pushdown(cur);
        }
        splay(cur);
        return cur;
    }
}
namespace Tcd{
    int fa[maxn],siz[maxn],dep[maxn],top[maxn],dfn[maxn],rnk[maxn],hson[maxn];
    int tot{0};
    void dfs1(int x,int f){
        fa[x]=f;Lct::fa[x]=f;
        dep[x]=dep[f]+1;
        siz[x]=1;
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
        top[x]=ctop;
        dfn[x]=++tot;
        rnk[tot]=dep[x];
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
    int lca(int x,int y){
        while(top[x]!=top[y]){
            if(dep[top[y]]>dep[top[x]]){
                std::swap(x,y);
            }
            x=fa[top[x]];
        }
        if(dep[y]<dep[x]){
            std::swap(x,y);
        }
        return x;
    }
}
void Seg::build(int p,int cl,int cr){
    if(cl==cr){
        tree[p]=Tcd::rnk[cl];
        tag[p]=0;
        return ;
    }
    int mid{(cl+cr)/2};
    build(p*2,cl,mid);
    build(p*2+1,mid+1,cr);
    tree[p]=std::max(tree[p*2],tree[p*2+1]);
    tag[p]=0;
}
int Lct::access(int x){
    int son{0};
    int cnt{0};
    while(x){
        splay(x);
        int od{ch[x][1]};
        ch[x][1]=son;
        if(od){
            int cur{findlow(od)};
            Seg::update(1,1,n,Tcd::dfn[cur],Tcd::dfn[cur]+Tcd::siz[cur]-1,1);
        }
        if(son){
            int cur{findlow(son)};
            Seg::update(1,1,n,Tcd::dfn[cur],Tcd::dfn[cur]+Tcd::siz[cur]-1,-1);
        }
        cnt++;
        son=x;
        splay(x);
        x=fa[x];
    }
    return cnt;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    int a,b;
    for(int i{1};i<n;i++){
        cin>>a>>b;
        addedge(a,b);addedge(b,a);
    }
    Tcd::dfs1(1,0);Tcd::dfs2(1,0,1);
    Seg::build(1,1,n);
    int opt;
    for(int i{1};i<=m;i++){
        cin>>opt;
        if(opt==1){
            cin>>a;
            Lct::access(a);
        }
        if(opt==2){
            using namespace Tcd;
            cin>>a>>b;
            int a1{0},a2{0},a3{0};
            Seg::query(1,1,n,dfn[a],dfn[a],a1);
            Seg::query(1,1,n,dfn[b],dfn[b],a2);
            Seg::query(1,1,n,dfn[lca(a,b)],dfn[lca(a,b)],a3);
            cout<<a1+a2-2*a3+1<<"\n";
        }
        if(opt==3){
            using namespace Tcd;
            cin>>a;
            int ans{0};
            Seg::query(1,1,n,dfn[a],dfn[a]+siz[a]-1,ans);
            cout<<ans<<"\n";
        }
    }
    cout.flush();
    return 0;
}