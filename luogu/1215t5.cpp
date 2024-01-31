#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
constexpr int maxn=1e6;
// #define int long long
int fa[maxn*2],ch[maxn*2][2],siz[maxn*2];
long long a[maxn*2];
struct Data{
    long long pre{},suf{},sum{},max{};
    Data(long long a=0){
        if(a>0){
            pre=suf=sum=max=a;
        }
        else{
            pre=suf=max=0;sum=a;
        }
    }
    Data mergel(Data x)const{//x *this
        Data A{0};
        A.pre=std::max({0ll,x.pre,x.sum+pre});
        A.suf=std::max({0ll,suf,x.suf+sum});
        A.sum=x.sum+sum;
        A.max=std::max({0ll,max,x.max,x.suf+pre});
        return A;
    }
}val[maxn*2];
void merge(int x){
    int ls{ch[x][0]},rs{ch[x][1]};
    val[x].pre=std::max({0ll,val[ls].pre,val[ls].sum+a[x]+val[rs].pre});
    val[x].suf=std::max({0ll,val[rs].suf,val[rs].sum+a[x]+val[ls].suf});
    val[x].sum=val[ls].sum+a[x]+val[rs].sum;
    val[x].max=std::max({0ll,val[ls].max,val[rs].max,val[ls].suf+a[x]+val[rs].pre});
}
struct Tag{
    bool rev{0};
}tag[maxn*2];
void clr(int x){
    fa[x]=ch[x][0]=ch[x][1]=siz[x]=a[x]=0;
    val[x]=Data(0);
    tag[x]=Tag{};
}
void pushup(int x){
    siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1;
    // val[x]=Data(a[x]);
    merge(x);
    // val[x]=val[x].mergel(val[ch[x][0]]);
    // val[x]=val[ch[x][1]].mergel(val[x]);
}
int reserv1,reserv2;
int rt{0},tot{0};
int n,m,q;
void apply(int x,bool flag){
    if(flag){
        std::swap(ch[x][0],ch[x][1]);
        std::swap(val[x].pre,val[x].suf);
        tag[x].rev^=flag;    
    }
}
void pushdown(int x){
    if(tag[x].rev){
        if(ch[x][0]){
            apply(ch[x][0],tag[x].rev);
        }
        if(ch[x][1]){
            apply(ch[x][1],tag[x].rev);
        }
        tag[x].rev=0;
        pushup(x);
    }
}
int chk(int x){
    return x==ch[fa[x]][1];
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
            if(ch[x][0]==0)return x;
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
int expose(int x,int y){
    splay(x);
    splay(y,x);
    return ch[y][chk(y)^1];
}
int ins(int cpos,int v){
    if(rt==0){
        rt=++tot;a[tot]=v;
        pushup(tot);
        return tot;
    }
    if(cpos==0){
        kth(1);
        ch[rt][0]=++tot;
        fa[tot]=rt;
        a[tot]=v;
        pushup(tot);pushup(rt);
        splay(tot);
        return tot;
    }
    kth(cpos);
    ch[++tot][0]=rt;ch[tot][1]=ch[rt][1];ch[rt][1]=0;
    fa[rt]=tot;a[tot]=v;
    if(ch[tot][1])fa[ch[tot][1]]=tot;
    pushup(rt);pushup(tot);rt=tot;
    return tot;
}
// void dfs(int x){
//     // pushdown(x);
//     if(ch[x][0])dfs(ch[x][0]);
//     if(x!=reserv1&&reserv2!=x)cout<<val[x]<<" ";
//     if(ch[x][1])dfs(ch[x][1]);
// }
void reverse(int l,int r){
    int y=kth(r+2);
    apply(expose(kth(l),y),1);
    pushup(y);
    pushup(rt);
}
void del(int cpos){
    int y{kth(cpos+2)};
    int p{expose(kth(cpos),y)};
    ch[y][0]=0;
    clr(p);
    pushup(y);
    pushup(rt);
}
signed main(){
    // freopen("b1.in","r",stdin);
    // freopen("1215t5.out","w",stdout);
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int T;
    cin>>n>>T;
    reserv1=ins(1,-1);
    // std::cerr<<0;
    reserv2=ins(1,-1);
    // cerr<<rt;
    int p,t;
    for(int i{1};i<=n;i++){
        cin>>t;
        ins(i,t);
    }
    // int x=expose(kth(5),kth(10+2));
    // cout<<val[x].max<<"\n";
    char opt;
    for(int i{1};i<=T;i++){
        cin>>opt;
        if(opt=='I'){
            cin>>p>>t;
            ins(p+1,t);
        }
        if(opt=='D'){
            cin>>p;
            del(p);
        }
        if(opt=='R'){
            cin>>p>>t;
            reverse(p,t);
        }
        if(opt=='Q'){
            cin>>p>>t;
            cout<<val[expose(kth(p),kth(t+2))].max<<"\n";
        }
    }
    // cerr<<rt;
    // cin>>q;
    // for(int i{1};i<=q;i++){
    //     cin>>p;
    //     cout<<val[kth(p+1)]<<"\n";
    // }
    // cout<<std::endl;
    cout<<std::flush;
    return 0;
}