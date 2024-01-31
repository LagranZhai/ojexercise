//P4219
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=4e5;
int n,q;
int a[maxn+10];
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
int getlow(int x){
    int cur{x};
    pushdown(cur);
    while(ch[cur][0]){
        cur=ch[cur][0];
        pushdown(cur);
    }
    splay(cur);
    return cur;
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
void makeroot(int x){
    access(x);
    splay(x);
    rev(x);
}
void split(int x,int y){
    makeroot(x);
    access(y);
    splay(y);
}
void link(int x,int y){
    makeroot(x);
    access(y);
    splay(y);
    fa[x]=y;
    msiz[y]+=siz[x];
    upval(y);
}
int getans(int x,int y){
    makeroot(x);
    access(y);
    splay(y);
    // if(ch[x][0])cout<<"A";
    // if(ch[x][1])cout<<"B";
    // if(ch[y][0]!=x)cout<<"C";

    return (msiz[x]+1)*(msiz[y]+1+siz[ch[y][1]]);
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>q;
    char opt;int x,y;
    for(int i{1};i<=n;i++){
        siz[i]=1;
        msiz[i]=0;
    }
    for(int i{1};i<=q;i++){
        cin>>opt;
        if(opt=='A'){
            cin>>x>>y;
            link(x,y);
        }
        else if(opt=='Q'){
            cin>>x>>y;
            cout<<getans(x,y)<<"\n";
        }
    }
    cout.flush();
    return 0;
}