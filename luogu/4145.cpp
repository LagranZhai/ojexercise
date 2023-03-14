#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int maxn=1e5;
ll a[maxn*2],tree[maxn*4];
void build(int cl,int cr,int p){
    if(cl==cr){
        tree[p]=a[cl];
        return;
    }
    int mid=(cl+cr)/2;
    build(cl,mid,p*2);
    build(mid+1,cr,p*2+1);
    tree[p]=tree[p*2]+tree[p*2+1];
    return;
}
void update(int cl,int cr,int p,int l,int r){
    if(tree[p]==cr-cl+1)return;
    if(cl==cr){
        tree[p]=sqrt(tree[p]);
        return;
    }
    int mid=(cl+cr)/2;
    if(l<=mid&&tree[p*2]>mid-cl+1)update(cl,mid,p*2,l,r);
    if(r>mid&&tree[p*2+1]>cr-mid)update(mid+1,cr,p*2+1,l,r);
    tree[p]=tree[p*2]+tree[p*2+1];
}
void query(int cl,int cr,int p,int l,int r,ll &ans){
    if(cl>=l&&cr<=r){
        ans+=tree[p];
        return;
    }
    int mid=(cl+cr)/2;
    if(l<=mid)query(cl,mid,p*2,l,r,ans);
    if(r>mid)query(mid+1,cr,p*2+1,l,r,ans);
}
int main(){
    ios::sync_with_stdio(false);
    int n,m;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    build(1,n,1);
    cin>>m;
    int opt,l,r;
    for(int i=1;i<=m;i++){
        cin>>opt>>l>>r;
        if(l>r)swap(l,r);
        if(opt==0){
            update(1,n,1,l,r);
        }
        if(opt==1){
            ll ans=0;
            query(1,n,1,l,r,ans);
            cout<<ans<<'\n';
        }
    }
    return 0;
}
