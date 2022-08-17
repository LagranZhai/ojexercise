#include<iostream>
using namespace std;
//最多开20e8个int
const int MAXN=10e7;
int tot=0,rt=0;
int fa[MAXN],ch[MAXN][2],siz[MAXN],cnt[MAXN];
int val[MAXN];
inline void upsiz(int x){
    siz[x]=cnt[x]+ch[x][0]+ch[x][1];
}
inline bool chk(int x){
    return x==ch[fa[x]][1];
}
inline void clean(int x){
    fa[x]=ch[x][0]=ch[x][1]=siz[x]=cnt[x]=val[x]=0;
}
void spin(int x){
    int f=fa[x],dir=chk(x),ff=fa[f];
    fa[ch[x][dir^1]]=fa[x],ch[fa[]][dir]=ch[x][dir^1];
    if(ff)ch[ff][chk(f)]=x;
    fa[f]=x,ch[x][dir^1]=f,fa[x]=ff;
    upsiz(f),upsiz(x);
}
