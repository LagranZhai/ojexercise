#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
#define int long long
constexpr int maxn=1e5;
// constexpr int inf=std::numeric_limits<int>::lowest();
int a[maxn*2],b[maxn*2];
int n,m;
struct Data{
    int a{},b{},ab{},sum{},hissum{},len{};
    Data operator+(Data A){
        return {sum+A.sum,hissum+A.hissum,len+A.len};
    }
    static Data identity(){
        return {0,0,0};
    }
};
struct Tag{
    int a1{},a2{},a3{},a4{};
    Tag operator+(Tag A){
        Tag B{};
        B.a1=a1*A.a1;
        B.a2=a1*A.a2+a2;
        B.a3=a3*A.a1+A.a3;
        B.a4=a3*A.a2+A.a4+a4;
        return B;
    }
    Data operator*(Data A){
        Data B{};
        B.sum=a1*A.sum+a2*A.len;
        B.hissum=a3*A.sum+A.hissum+a4*A.len;
        B.len=A.len;
        return B;
    }
    static Tag identity(){
        return {1,0,0,0};
    }
};
struct dm{
    Data d{};Tag t{};
}tree[maxn*4];
// bool have[maxn*2];
void pushdown(int p){
    // if(tree[p].t.a1!=0||tree[p].t.a2>inf||tree[p].t.a3>inf||tree[p].t.a4>inf){
    if(tree[p].t.a1!=1||tree[p].t.a2!=0||tree[p].t.a3!=0||tree[p].t.a4!=0){
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
        tree[p].d={0,0,1};
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
struct Que{
    int l{},r{},num{},ans{};
}q[maxn*2];
std::vector<int> lis;
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    for(int i{1};i<=n;i++)cin>>a[i];
    build(1,1,n);
    for(int i{1};i<=m;i++){
        cin>>q[i].l>>q[i].r;
        q[i].num=i;
    }
    std::sort(q+1,q+m+1,[](const Que A,const Que B)->bool{return (A.r==B.r)?(A.l<B.l):(A.r<B.r);});
    int p{1};
    for(int i{1};i<=m;i++){
        int cur{q[i].r};
        while(p<=q[i].r){
            while(!lis.empty()&&a[lis.back()]>a[p])lis.pop_back();
            if(lis.empty())cur=0;
            else cur=lis.back();
            if(cur+1<=p)update(1,1,n,cur+1,p,{0,a[p],0,0});
            lis.push_back(p);
            p++;
            update(1,1,n,1,p,{1,0,1,0});
        }
        Data ans{0,0,0};
        query(1,1,n,q[i].l,q[i].r,ans);
        q[i].ans=ans.hissum;
    }
    std::sort(q+1,q+m+1,[](const Que A,const Que B){return A.num<B.num;});
    for(int i{1};i<=m;i++){
        cout<<q[i].ans<<"\n";
    }
    cout<<std::flush;
    return 0;
}