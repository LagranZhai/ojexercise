#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
#define int long long
constexpr int maxn=2e5;
constexpr int inf=(std::numeric_limits<int>::lowest()>>20);
int a[maxn*2];
int n,m;
struct Data{
    int max{},hmax{};
    Data operator+(Data A){
        return {std::max(max,A.max),std::max(hmax,A.hmax)};
    }
    static Data identity(){
        return {inf,inf};
    }
};
struct Tag{
    int a1{},a2{},a3{},a4{};
    Tag operator+(Tag A){
        Tag B{};
        B.a1=A.a1+a1;
        B.a2=std::max(a1+A.a2,a2);
        B.a3=std::max(a3+A.a1,A.a3);
        B.a4=std::max({a3+A.a2,A.a4,a4});
        // a1=B.a1;a2=B.a2;a3=B.a3;a4=B.a4;
        return B;
    }
    Data operator*(Data A){
        Data B{};
        B.max=std::max(a1+A.max,a2);
        B.hmax=std::max({A.max+a3,A.hmax,a4});
        return B;
    }
    static Tag identity(){
        return {0,inf,inf,inf};
    }
};
struct dm{
    Data d{};Tag t{};
}tree[maxn*4];
// bool have[maxn*2];
void pushdown(int p){
    // if(tree[p].t.a1!=0||tree[p].t.a2>inf||tree[p].t.a3>inf||tree[p].t.a4>inf){
    if(tree[p].t.a1!=0||tree[p].t.a2>inf||tree[p].t.a3>inf||tree[p].t.a4>inf){
        tree[p*2].d=tree[p].t*tree[p*2].d;
        tree[p*2].t=tree[p].t+tree[p*2].t;
        tree[p*2+1].d=tree[p].t*tree[p*2+1].d;
        tree[p*2+1].t=tree[p].t+tree[p*2+1].t;
        // tree[p*2].d.apply(tree[p].t);
        // tree[p*2].t.compose(tree[p].t);have[p*2]=1;
        // tree[p*2+1].d.apply(tree[p].t);
        // tree[p*2+1].t.compose(tree[p].t);have[p*2+1]=1;
        tree[p].t=Tag::identity();
        // have[p]=0;
    }
}
void build(int p,int cl,int cr){
    tree[p].t=Tag::identity();
    if(cl==cr){
        // tree[p].d.len=1;
        tree[p].d={a[cl],a[cl]};
        return ;
    }
    int mid=(cl+cr)/2;
    build(p*2,cl,mid);
    build(p*2+1,mid+1,cr);
    tree[p].d=tree[p*2].d+tree[p*2+1].d;
}
void update(int p,int cl,int cr,int l,int r,Tag w){
    if(cl>=l&&cr<=r){
        tree[p].d=w*tree[p].d;
        tree[p].t=w+tree[p].t;
        // have[p]=1;
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
void query(int p,int cl,int cr,int l,int r,Data& ans){
    if(cl>=l&&cr<=r){
        ans=(ans+tree[p].d);
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
// int query1(int p,int cl,int cr,int l,int r){
//     if(cl>=l&&cr<=r){
//         // ans=(ans+tree[p].d);
//         return tree[p].d.hmax;
//     }
//     if(cl!=cr){
//         pushdown(p);
//         int mid=(cl+cr)/2;
//         int ans{inf};
//         if(l<=mid)ans=std::max(query1(p*2,cl,mid,l,r),ans);
//         if(r>mid)ans=std::max(query1(p*2+1,mid+1,cr,l,r),ans);
//         return ans;
//     }
//     // return inf;
// }
// int query2(int p,int cl,int cr,int l,int r){
//     if(cl>=l&&cr<=r){
//         // ans=(ans+tree[p].d);
//         return tree[p].d.max;
//     }
//     if(cl!=cr){
//         pushdown(p);
//         int mid=(cl+cr)/2;
//         int ans{inf};
//         if(l<=mid)ans=std::max(query2(p*2,cl,mid,l,r),ans);
//         if(r>mid)ans=std::max(query2(p*2+1,mid+1,cr,l,r),ans);
//         return ans;
//     }
//     // return inf;
// }
signed main(){
    // freopen("P4314_1.in","r",stdin);
    // freopen("4314.in","r",stdin);
    // freopen("4314.out","w",stdout);
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n;
    for(int i{1};i<=n;i++)cin>>a[i];
    build(1,1,n);
    cin>>m;
    char c;
    int x,y,z;
    for(int i{1};i<=m;i++){
        cin>>c;
        if(c=='Q'){
            cin>>x>>y;
            Data ans{inf,inf};
            query(1,1,n,x,y,ans);
            cout<<ans.max<<"\n";
            // cout<<query2(1,1,n,x,y)<<"\n";
        }
        if(c=='A'){
            cin>>x>>y;
            Data ans{inf,inf};
            query(1,1,n,x,y,ans);
            cout<<ans.hmax<<"\n";
            // cout<<query1(1,1,n,x,y)<<"\n";
        }
        if(c=='P'){
            cin>>x>>y>>z;
            update(1,1,n,x,y,{z,inf,z,inf});
        }
        if(c=='C'){
            cin>>x>>y>>z;
            update(1,1,n,x,y,{inf,z,inf,z});
        }
        // update(1,1,n,1,n,{0,inf,0,inf});
    }
    cout<<std::flush;
    return 0;
}