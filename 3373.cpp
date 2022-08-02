#include<iostream>
#include<vector>
using namespace std;
const int MAXN=1e5;
using ll=long long;
ll tree[MAXN*4];
ll mark[MAXN*4];
ll kram[MAXN*4];
ll a[MAXN];
int pp;
void build(int p,int cl,int cr){
    kram[p]=1;
    if(cl==cr){
        tree[p]=a[cl];
        return;
    }
    int mid=(cl+cr)/2;
    build(p*2,cl,mid);
    build(p*2+1,mid+1,cr);
    tree[p]=tree[p*2]+tree[p*2+1];
}
void pushdown(int p,int len){
    kram[p*2]*=kram[p];
    kram[p*2]%=pp;
    tree[p*2]=tree[p*2]*kram[p]+mark[p]*(len-len/2);
    tree[p*2]%=pp;
    mark[p*2]=mark[p*2]*kram[p]+mark[p];
    mark[p*2]%=pp;
    kram[p*2+1]*=kram[p];
    kram[p*2+1]%=pp;
    mark[p*2+1]=mark[p*2]*kram[p]+mark[p];
    mark[p*2+1]%=pp;
    tree[p*2+1]=tree[p*2+1]*kram[p]+mark[p]*(len/2);
    tree[p*2+1]%=pp;
    mark[p]=0;
    kram[p]=1;
}
void ask(const int l,const int r,int cl,int cr,int p,ll& ans){
    if(cl>=l&&cr<=r){
        ans+=tree[p];
        ans%=pp;
        return;
    }
    int mid=(cl+cr)/2;
    if(cl!=cr){
        pushdown(p,cr-cl+1);
        if(mid>=l)ask(l,r,cl,mid,p*2,ans);
        if(mid<r)ask(l,r,mid+1,cr,p*2+1,ans);
    }
}
void update(const int l,const int r,int cl,int cr,int p,ll d,int opt){
    if(cl>=l&&cr<=r){
        if(opt==2){
            mark[p]+=d;
            mark[p]%=pp;
            tree[p]+=d*(cr-cl+1);
            tree[p]%=pp;
            return;
        }
        else if(opt==1){
            kram[p]*=d;
            kram[p]%=pp;
            mark[p]*=d;
            mark[p]%=pp;
            tree[p]*=d;
            tree[p]%=pp;
            return;
        }
    }
    int mid=(cl+cr)/2;
    if(cl!=cr){
        pushdown(p,cr-cl+1);
        if(mid>=l)update(l,r,cl,mid,p*2,d,opt);
        if(mid<r)update(l,r,mid+1,cr,p*2+1,d,opt);
        tree[p]=tree[p*2]+tree[p*2+1];
        tree[p]%=pp;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    vector<ll> arr;
    int n,m;
    cin>>n>>m>>pp;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1,1,n);
    int opt,x,y,d;
    for(int i=0;i<m;i++){
        cin>>opt;
        if(opt==1){
            cin>>x>>y>>d;
            update(x,y,1,n,1,d,1);
        }
        else if(opt==2){
            cin>>x>>y>>d;
            update(x,y,1,n,1,d,2);
        }
        else if(opt==3){
            cin>>x>>y;
            ll ans=0;
            ask(x,y,1,n,1,ans);
            arr.push_back(ans);
        }
    }
    for(auto& aaa:arr)cout<<aaa<<endl;
    return 0;
}
