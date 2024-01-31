#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e5;
#define int long long
int a[maxn*2];
int n,m;
struct Data{
    int sum{0},max{0},len{0};
    Data merge(Data A){
        return {sum+A.sum,std::max(A.max,max),len+A.len};
    }
};
struct Tag{
    int add{};
    Tag compose(Tag A){
        Tag B{add+A.add};
        return B;
    }
    Data apply(Data A){
        Data B{add*A.len+A.sum,add+A.max,A.len};
        return B;
    }
};
struct dm{
    Data d{};Tag t{};
}tree[maxn*4];
// bool have[maxn*2];
void pushdown(int p){
    // if(tree[p].t.a1!=0||tree[p].t.a2>inf||tree[p].t.a3>inf||tree[p].t.a4>inf){
    if(tree[p].t.add!=0){
        tree[p*2].d=tree[p].t.apply(tree[p*2].d);
        tree[p*2].t=tree[p].t.compose(tree[p*2].t);
        tree[p*2+1].d=tree[p].t.apply(tree[p*2+1].d);
        tree[p*2+1].t=tree[p].t.compose(tree[p*2+1].t);
        tree[p].t={0};
    }
}
void build(int p,int cl,int cr){
    tree[p].t={0};
    if(cl==cr){
        tree[p].d={a[cl],a[cl],1};
        return ;
    }
    int mid=(cl+cr)/2;
    build(p*2,cl,mid);
    build(p*2+1,mid+1,cr);
    tree[p].d=tree[p*2].d.merge(tree[p*2+1].d);
}
void update(int p,int cl,int cr,int l,int r,Tag w){
    if(cl>=l&&cr<=r){
        tree[p].d=w.apply(tree[p].d);
        tree[p].t=w.compose(tree[p].t);
        return ;
    }
    if(cl!=cr){
        pushdown(p);
        int mid=(cl+cr)/2;
        if(l<=mid)update(p*2,cl,mid,l,r,w);
        if(r>mid)update(p*2+1,mid+1,cr,l,r,w);
        tree[p].d=tree[p*2].d.merge(tree[p*2+1].d);
    }
}
void query(int p,int cl,int cr,int l,int r,Data& ans){
    if(cl>=l&&cr<=r){
        ans=(ans.merge(tree[p].d));
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
	ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1,1,n);
    int opt,x,y,d;
    for(int i=0;i<m;i++){
        cin>>opt;
        if(opt==1){
            cin>>x>>y>>d;
            update(1,1,n,x,y,{d});
        }
        else{
            cin>>x>>y;
            Data ans{0,0};
            query(1,1,n,x,y,ans);
            cout<<ans.sum<<"\n";
        }
    }
	cout.flush();
	return 0;
}