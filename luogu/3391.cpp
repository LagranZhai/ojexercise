#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::ios;
constexpr int maxn=1e5;
#define int long long
int fa[maxn*2],ch[maxn*2][2],val[maxn*2],cnt[maxn*2],siz[maxn*2];
int rt{},tot{};
bool rev[maxn*2];
int chk(int x){return x==ch[fa[x]][1];}
void apply(int x){
    if(x){
        rev[x]^=1;
        std::swap(ch[x][0],ch[x][1]);
    }
}
void pushdown(int x){
    if(rev[x]){
        apply(ch[x][0]);
        apply(ch[x][1]);
        rev[x]=0;
    }
}
void pushdownfromrt(int x){
    if(fa[x]){
        pushdownfromrt(fa[x]);
    }
    pushdown(x);
}
void pushup(int x){
    siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+cnt[x];
}
void spin(int x){
    int f{fa[x]},ff{fa[f]},dir{chk(x)};
    if(ff)ch[ff][chk(f)]=x;
    fa[x]=ff;fa[f]=x;
    ch[f][dir]=ch[x][dir^1];
    if(ch[x][dir^1])fa[ch[x][dir^1]]=f;
    ch[x][dir^1]=f;
    pushup(f);pushup(x);
}
void splay(int x,int des=0){
    int f{fa[x]};
    while(fa[x]!=des){
        if(fa[f]!=des)spin(chk(x)==chk(f)?f:x);
        spin(x);
        f=fa[x];
    }
    if(!des)rt=x;
}
int kth(int k){
    int x{rt};
    while(1){
        pushdown(x);
        if(k<=siz[ch[x][0]]){
            x=ch[x][0];
        }
        else{
            k-=siz[ch[x][0]]+cnt[x];
            if(k<=0){
                splay(x);
                return x;
            }
            x=ch[x][1];
        }
    }
}
int a[maxn*2];
void build(int &x,int f,int l,int r){
    x=++tot;
    cnt[x]++;
    fa[x]=f;
    int mid{(l+r)/2};
    val[x]=a[mid];
    if(l<=mid-1){
        build(ch[x][0],x,l,mid-1);
    }
    if(mid+1<=r){
        build(ch[x][1],x,mid+1,r);
    }
    pushup(x);
}
void expose(int x,int y){
    int a{kth(x)};
    int b{kth(y)};
    splay(a,b);
    apply(ch[a][chk(a)^1]);
}
void dfs(int x){
    pushdown(x);
    if(ch[x][0])dfs(ch[x][0]);
    if(val[x]!=-1)cout<<val[x]<<" ";
    if(ch[x][1])dfs(ch[x][1]);
}
int n,m;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    a[0]=-1;
    for(int i{1};i<=n;i++){
        a[i]=i;
    }
    a[n+1]=-1;
    build(rt,0,0,n+1);
    int x,y;
    for(int i{1};i<=m;i++){
        cin>>x>>y;
        expose(x,y+2);
    }
    dfs(rt);
    cout.flush();
    return 0;
}