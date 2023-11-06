#include<iostream>
using namespace std;
const int MAXN=1e5;
using ll=long long;
ll tree[MAXN*4];
ll tree2[MAXN*4];
ll mark[MAXN*4];
ll a[MAXN];
void build(int p,int cl,int cr){
    if(cl==cr){
        tree[p]=a[cl];
        tree2[p]=a[cl];
        return;
    }
    int mid=(cl+cr)/2;
    build(p*2,cl,mid);
    build(p*2+1,mid+1,cr);
    tree[p]=tree[p*2]+tree[p*2+1];
    tree2[p]=max(tree2[p*2],tree2[p*2+1]);
}
void ask(const int l,const int r,int cl,int cr,int p,ll& ans){
    if(cl>=l&&cr<=r){
        ans+=tree[p];
        return;
    }
    int mid=(cl+cr)/2;
    if(cl!=cr){
        int len=cr-cl+1;    
        mark[p*2]+=mark[p];
        tree[p*2]+=mark[p]*(len-len/2);
        mark[p*2+1]+=mark[p];
        tree[p*2+1]+=mark[p]*(len/2);
        mark[p]=0;
        if(mid>=l)ask(l,r,cl,mid,p*2,ans);
        if(mid<r)ask(l,r,mid+1,cr,p*2+1,ans);
    }
}
void ask2(const int l,const int r,int cl,int cr,int p,ll& ans){
    if(cl>=l&&cr<=r){
        ans=max(ans,tree2[p]);
        return;
    }
    int mid=(cl+cr)/2;
    if(cl!=cr){
        int len=cr-cl+1;    
        mark[p*2]+=mark[p];
        tree[p*2]+=mark[p]*(len-len/2);
        mark[p*2+1]+=mark[p];
        tree[p*2+1]+=mark[p]*(len/2);
        mark[p]=0;
        if(mid>=l)ask2(l,r,cl,mid,p*2,ans);
        if(mid<r)ask2(l,r,mid+1,cr,p*2+1,ans);
    }
}
void update(const int l,const int r,int cl,int cr,int p,ll d){
    if(cl>=l&&cr<=r){
        mark[p]+=d;
        tree[p]+=d*(cr-cl+1);
        tree2[p]+=d;
        return;
    }
    int mid=(cl+cr)/2;
    if(cl!=cr){
        int len=cr-cl+1;    
        mark[p*2]+=mark[p];
        tree[p*2]+=mark[p]*(len-len/2);
        mark[p*2+1]+=mark[p];
        tree[p*2+1]+=mark[p]*(len/2);
        mark[p]=0;
        if(mid>=l)update(l,r,cl,mid,p*2,d);
        if(mid<r)update(l,r,mid+1,cr,p*2+1,d);
        tree[p]=tree[p*2]+tree[p*2+1];
        tree2[p]=max(tree2[p*2],tree2[p*2+1]);
    }
}
int main()
{
    ios::sync_with_stdio(false);
    int n,m;
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
            update(x,y,1,n,1,d);
        }
        else{
            cin>>x>>y;
            ll ans=0;
            ask(x,y,1,n,1,ans);
            cout << ans << endl;
        }
    }    
    return 0;
}