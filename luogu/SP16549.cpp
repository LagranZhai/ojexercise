//SP16549
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=4e5;
int n,q;
int a[maxn+10];
struct Lct{
    int ch[maxn+10][2],fa[maxn+10],siz[maxn+10],msiz[maxn+10];
    bool tag[maxn+10];
    inline int chk(int x){
        if(ch[fa[x]][1]==x)return 1;
        if(ch[fa[x]][0]==x)return 0;
        return -1;
    }
    inline void upval(int x){
        siz[x]=siz[ch[x][1]]+msiz[x]+1+siz[ch[x][0]];
    }
    inline void rev(int x){
        if(x){
            tag[x]^=1;
            std::swap(ch[x][0],ch[x][1]);
            // upval(x);
        }
    }
    inline void pushdown(int x){
        if(tag[x]){
            rev(ch[x][0]);
            rev(ch[x][1]);
            tag[x]=0;
        }
    }
    void reverse_pushdown(int x){
        if(chk(x)!=-1)reverse_pushdown(fa[x]);
        pushdown(x);
    }
    void spin(int x){
        int f=fa[x],dir=chk(x),ff=fa[f];
        if(chk(f)!=-1)ch[ff][chk(f)]=x;
        if(ch[x][dir^1])fa[ch[x][dir^1]]=f;
        ch[f][dir]=ch[x][dir^1];
        fa[f]=x;ch[x][dir^1]=f;fa[x]=ff;
        upval(f);upval(x);
    }
    void splay(int x){
        reverse_pushdown(x);
        int f=fa[x];
        while(chk(x)!=-1){
            if(chk(f)!=-1)spin(chk(f)==chk(x)?f:x);
            spin(x);
            f=fa[x];
        }
    }
    void access(int x){
        int son=0;
        while(x){
            splay(x);
            if(son){
                msiz[x]-=siz[son];
            }
            if(ch[x][1]){
                msiz[x]+=siz[ch[x][1]];
            }
            ch[x][1]=son;
            upval(x);
            son=x;
            x=fa[x];
        }
    }
    int findroot(int x){
        pushdown(x);
        while(ch[x][0]){
            x=ch[x][0];
            pushdown(x);
        }
        splay(x);
        return x;
    }
    void link(int x,int y){
        access(x);splay(x);
        access(y);
        splay(y);
        fa[x]=y;
        msiz[y]+=siz[x];
        upval(y);
    }
    void cut(int x,int y){
        access(y);
        splay(y);
        access(x);
        splay(x);
        fa[y]=0;
        ch[x][0]=0;
        upval(x);
    }
    int getans(int x){
        access(x);splay(x);
        int rt{findroot(x)};
        splay(rt);
        return siz[ch[rt][1]];
    }
}tree[2];
struct Edge{
    int v,nxt;
}edg[maxn*4];
int head[maxn],cnt{0};
void addedge(int u,int v){
    edg[++cnt]={v,head[u]};
    head[u]=cnt;
}
int fa[maxn],col[maxn]{0};
void dfs(int x,int f){
    fa[x]=f;
    if(f){
        tree[0].link(x,f);
    }
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            dfs(to,x);
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n;
    int x,y;
    for(int i{1};i<n;i++){
        cin>>x>>y;
        addedge(x,y);addedge(y,x);
    }
    addedge(1,n+1);addedge(n+1,1);
    dfs(n+1,0);
    cin>>q;
    int opt;
    for(int i{1};i<=q;i++){
        cin>>opt;
        if(opt==0){
            cin>>x;
            cout<<tree[col[x]].getans(x)<<"\n";
        }
        else if(opt==1){
            cin>>x;
            tree[col[x]].cut(x,fa[x]);
            col[x]^=1;
            tree[col[x]].link(x,fa[x]);
        }
    }
    cout.flush();
    return 0;
}