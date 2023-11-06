#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=3e5,P=1e9+9;
int f[maxn*3],sumf[maxn*3];
int n,m;
int a[maxn*2];
void init(){
    f[0]=0;f[1]=1;
    sumf[0]=0;sumf[1]=1;
    for(int i{2};i<=maxn*2;i++){
        f[i]=(f[i-1]+f[i-2])%P;
        sumf[i]=(sumf[i-1]+f[i])%P;
    }
}
int getsum(int l,int r){
    int suml=0,sumr=0;
    if(l>=0){
        suml=sumf[l];
    }
    else if(l==-1){
        suml=0;
    }
    else{
        suml=-1;
    }
    if(r>=0){
        sumr=sumf[r];
    }
    else if(r==-1){
        sumr=0;
    }
    else{
        sumr=-1;
    }
    return (sumr-suml+P)%P;
}
struct Tag{
    int a1{0},a2{0},l{0};
    void compose(Tag A){
        // l=A.l;
        // a1=(a1+A.a1)%P;
        // a2=(a2+A.a2)%P;
        Tag B{};
        B.l=std::max(l,A.l);
        if(A.l>=l){
            B.a1=((A.a1+f[A.l-l]*a2%P)%P+((A.l>l)?(f[A.l-l-1]*a1%P):a1))%P;
            B.a2=((A.a2+f[A.l-l+1]*a2%P)%P+f[A.l-l]*a1%P)%P;
        }
        else{
            B.a1=((a1+f[l-A.l]*A.a2%P)%P+f[l-A.l-1]*A.a1%P)%P;
            B.a2=((a2+f[l-A.l+1]*A.a2%P)%P+f[l-A.l]*A.a1%P)%P;
        }
        a1=B.a1;a2=B.a2;l=B.l;
        return ;
    }
};
struct Data{
    int sum{0},cl{0},cr{0};
    Data operator+(Data A){
        return {(sum+A.sum)%P,cl,A.cr};
    }
    void apply(Tag A){
        if(cr-cl>=0)sum=(((sum+getsum(cl-A.l-1,cr-A.l)*A.a2%P)%P+getsum(cl-A.l-2,cr-A.l-1)*A.a1%P))%P;
    }
};
struct dm{
    Data d{};Tag t{};
}tree[maxn*4];
void pushdown(int p){
    if(tree[p].t.a1!=0||tree[p].t.a2!=0){
        tree[p*2].d.apply(tree[p].t);
        tree[p*2].t.compose(tree[p].t);
        tree[p*2+1].d.apply(tree[p].t);
        tree[p*2+1].t.compose(tree[p].t);
        tree[p].t=Tag{};
    }
}
void build(int p,int cl,int cr){
    if(cl==cr){
        // tree[p].d.len=1;
        tree[p].d.cl=tree[p].d.cr=cl;
        tree[p].d.sum=a[cl];
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
void query(int p,int cl,int cr,int l,int r,int& ans){
    if(cl>=l&&cr<=r){
        ans=(ans+tree[p].d.sum)%P;
        return ;
    }
    if(cl!=cr){
        pushdown(p);
        int mid=(cl+cr)/2;
        if(l<=mid)query(p*2,cl,mid,l,r,ans);
        if(r>mid)query(p*2+1,mid+1,cr,l,r,ans);
        return ;
    }
    return ;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    init();
    cin>>n>>m;
    int u,v;
    init();
    for(int i{1};i<=n;i++){
        cin>>a[i];
    }
    build(1,1,n);
    int opt;
    for(int i{1};i<=m;i++){
        cin>>opt;
        if(opt==1){
            cin>>u>>v;
            update(1,1,n,u,v,{1,1,u});
        }
        if(opt==2){
            int ans{0};
            cin>>u>>v;
            query(1,1,n,u,v,ans);
            cout<<ans<<"\n";
        }
    }
    cout<<std::flush;
    return 0;
}