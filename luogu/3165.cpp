//P3165
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=1e6+100;
int n;
std::pair<int,int> a[maxn];
int v[maxn];
int fa[maxn],ch[maxn][2],siz[maxn],rt,tot{0};
bool rev[maxn];
void func(int x){
    if(x){
        rev[x]^=1;
        std::swap(ch[x][0],ch[x][1]);
    }
}
void pushdown(int x){
    if(rev[x]){
        func(ch[x][0]);func(ch[x][1]);
        rev[x]=0;
    }
}
void reverse_pushdown(int x){
    if(fa[x])reverse_pushdown(fa[x]);
    pushdown(x);
}
int chk(int x){
    return x==ch[fa[x]][1];
}
void upval(int x){
    siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1;
}
void spin(int x){
    int f{fa[x]},ff{fa[f]},dir{chk(x)};
    if(ff)ch[ff][chk(f)]=x;
    if(ch[x][dir^1])fa[ch[x][dir^1]]=f;
    fa[x]=ff;ch[f][dir]=ch[x][dir^1];
    ch[x][dir^1]=f;fa[f]=x;
    upval(f);upval(x);
    return ;
}
void splay(int x,int des=0){
    reverse_pushdown(x);
    int f{fa[x]};
    while(f!=des){
        if(fa[f]!=des)spin(chk(x)==chk(f)?f:x);
        spin(x);
        f=fa[x];
    }
    if(des==0)rt=x;
    return ;
}
int rton[maxn];
int ln,rn;
int build(int cl,int cr,int f){
    int mid{(cl+cr)/2};
    tot++;fa[tot]=f;
    if(mid==0){
        ln=tot;
    }
    else if(mid==n+1){
        rn=tot;
    }
    else rton[v[mid]]=tot;
    int cur{tot};
    if(cl<=mid-1)ch[cur][0]=build(cl,mid-1,cur);
    if(cr>=mid+1)ch[cur][1]=build(mid+1,cr,cur);
    upval(cur);
    return cur;
}
int kth(int k){
    int x{rt};
    while(1){
        pushdown(x);
        if(k>=siz[ch[x][0]]+1){
            k-=siz[ch[x][0]]+1;
            x=ch[x][1];
        }
        else{
            if(k-siz[ch[x][0]]==0){
                splay(x);
                return x;
            }
            x=ch[x][0];
        }
    }
}
void reverseq(int rank,int r){
    // cerr<<rank;
    int l=kth(rank-1);
    splay(r);
    int x{ch[r][1]};
    pushdown(x);
    while(ch[x][0]){
        x=ch[x][0];
        pushdown(x);
    }
    splay(x);
    splay(l,x);
    if(ch[l][chk(l)^1]){
        x=ch[l][chk(l)^1];
        func(x);
    }
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n;
    int t;
    for(int i{1};i<=n;i++){
        cin>>t;a[i].first=t*(1e6)+i-1;
        a[i].second=i;
    }
    std::sort(a+1,a+n+1);
    for(int i{1};i<=n;i++){
        v[a[i].second]=i;
    }
    rt=build(0,n+1,0);
    // cerr<<siz[rt];
    for(int i{1};i<=n;i++){
        // cerr<<i;
        splay(rton[i]);
        cout<<siz[ch[rt][0]]<<" ";
        reverseq(i,rton[i]);
    }
    cout<<"\n";
    cout.flush();
    return 0;
}