#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=2e5;
#define int long long
int n,m;
// double tsin[maxn*4],tcos[maxn*4];
int a[maxn*2]/*,tag[maxn*2]*/;
struct _T{
    int addtag{0};
    void compose(const _T& a){
        addtag+=a.addtag;
    }
};
struct _D{
    double sin{0},cos{0};
    static _D merge(_D a,_D b){
        return {a.sin+b.sin,a.cos+b.cos};
    }
    void apply(const _T& a){
        _D od=*this;
        sin=std::cos(a.addtag)*od.sin+std::sin(a.addtag)*od.cos;
        cos=std::cos(a.addtag)*od.cos-std::sin(a.addtag)*od.sin;
    }
};
struct double_monoid{
    _D D;_T T;
    void pushdown(double_monoid& a,double_monoid& b);
}tree[maxn*4];
void double_monoid::pushdown(double_monoid& a,double_monoid& b){
    a.D.apply(this->T);
    b.D.apply(this->T);
    a.T.compose(this->T);
    b.T.compose(this->T);
    this->T=_T{};
}
void build(int p,int cl,int cr){
    if(cl==cr){
        tree[p].D={std::sin(a[cl]),std::cos(a[cl])};
        return ;
    }
    int mid=(cl+cr)/2;
    build(p*2,cl,mid);
    build(p*2+1,mid+1,cr);
    tree[p].D=_D::merge(tree[p*2].D,tree[p*2+1].D);
    return ;
}
void update(int p,int cl,int cr,int l,int r,const int w){
    if(cl>=l&&cr<=r){
        tree[p].D.apply({w});
        tree[p].T.compose({w});
        return ;
    }
    if(cl!=cr){
        tree[p].pushdown(tree[p*2],tree[p*2+1]);
        int mid=(cl+cr)/2;
        if(l<=mid)update(p*2,cl,mid,l,r,w);
        if(r>mid)update(p*2+1,mid+1,cr,l,r,w);
        tree[p].D=_D::merge(tree[p*2].D,tree[p*2+1].D);
    }
}
void query(int p,int cl,int cr,int l,int r,double &ans){
    if(cl>=l&&cr<=r){
        ans+=tree[p].D.sin;
        return ;
    }
    if(cl!=cr){
        tree[p].pushdown(tree[p*2],tree[p*2+1]);
        int mid=(cl+cr)/2;
        if(l<=mid)query(p*2,cl,mid,l,r,ans);
        if(r>mid)query(p*2+1,mid+1,cr,l,r,ans);
        return ;
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i{1};i<=n;i++){
        cin>>a[i];
    }
    build(1,1,n);
    cin>>m;
    int OPT,L,R,V;
    cout<<std::fixed<<std::setprecision(1);
    for(int i{1};i<=m;i++){
        cin>>OPT;
        if(OPT==1){
            cin>>L>>R>>V;
            update(1,1,n,L,R,V);
        }
        if(OPT==2){
            cin>>L>>R;
            double ans=0;
            query(1,1,n,L,R,ans);
            cout<<ans<<"\n";
        }
    }
    cout.flush();
    return 0;
}