#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
constexpr int maxn=1e5;
int fa[maxn*2],ch[maxn*2][2],siz[maxn*2],val[maxn*2];
bool rev[maxn*2];
int reserv1,reserv2;
int rt{0},tot{0};
int n,m;
void apply(int x,bool flag){
    if(flag){
        std::swap(ch[x][0],ch[x][1]);
        rev[x]^=flag;    
    }
}
void pushdown(int x){
    if(rev[x]){
        if(ch[x][0]){
            apply(ch[x][0],rev[x]);
        }
        if(ch[x][1]){
            apply(ch[x][1],rev[x]);
        }
        rev[x]=0;
    }
}
int chk(int x){
    return x==ch[fa[x]][1];
}
void pushup(int x){
    siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1;
}
void spin(int x){
    int f{fa[x]},ff{fa[f]},dir=chk(x);
    if(ff)ch[ff][chk(f)]=x;
    fa[x]=ff;fa[f]=x;ch[f][dir]=ch[x][dir^1];
    if(ch[x][dir^1])fa[ch[x][dir^1]]=f;
    ch[x][dir^1]=f;
    pushup(f);pushup(x);
}
void pushdownall(int x){
    if(fa[x]!=0)pushdownall(fa[x]);
    pushdown(x);
}
void splay(int x,int des=0){
    pushdownall(x);
    int f{fa[x]};
    while(f!=des){
        if(fa[f]!=des)spin((chk(f)==chk(x))?f:x);
        spin(x);
        f=fa[x];
    }
    if(des==0)rt=x;
}
int kth(int k){
    int x{rt};
    while(1){
        pushdown(x);
        if(k<=siz[ch[x][0]]){
            x=ch[x][0];
        }
        else{
            k-=siz[ch[x][0]]+1;
            if(k<=0){
                splay(x);
                return x;
            }
            x=ch[x][1];
        }
    }
}
int* expose(int x,int y){
    splay(x);
    splay(y,x);
    return &ch[y][chk(y)^1];
}
int ins(int cpos,int v){
    if(rt==0){
        rt=++tot;val[tot]=v;
        pushup(tot);
        return tot;
    }
    if(cpos==0){
        kth(1);
        ch[rt][0]=++tot;
        fa[tot]=rt;
        val[tot]=v;
        pushup(tot);pushup(rt);
        splay(tot);
        return tot;
    }
    kth(cpos);
    ch[++tot][0]=rt;ch[tot][1]=ch[rt][1];ch[rt][1]=0;
    fa[rt]=tot;val[tot]=v;
    if(ch[tot][1])fa[ch[tot][1]]=tot;
    pushup(rt);pushup(tot);rt=tot;
    return tot;
}
void dfs(int x){
    pushdown(x);
    if(ch[x][0])dfs(ch[x][0]);
    if(x!=reserv1&&reserv2!=x)cout<<val[x]<<" ";
    if(ch[x][1])dfs(ch[x][1]);
}

void reverse(int l,int r){
    apply(expose(findbypos(l-1),findbypos(r+1)),1);
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    int p,t;
    reserv1=ins(0,114514);
    // std::cerr<<0;
    reserv2=ins(n+1,114514);
    for(int i{1};i<=n;i++){
        // cin>>t;
        ins(i,i);
    }
    for(int i{1};i<=m;i++){
        cin>>p>>t;
        reverse(p,t);
    }
    dfs(rt);
    cout<<std::flush;
    return 0;
}