#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5;
using ll=long long;
ll tree[maxn*4];
ll mark[maxn*4];
ll a[maxn];
int m;
ll D;
// inline void pushdown(int p,int len){
// 	mark[p*2]+=mark[p];
// 	tree[p*2]+=mark[p]*(len-len/2);
// 	mark[p*2+1]+=mark[p];
// 	tree[p*2+1]+=mark[p]*(len/2);
// 	mark[p]=0;
// }
void build(int p,int cl,int cr){
	if(cl==cr){
		tree[p]=a[cl];
		return;
	}
	int mid=cl+(cr-cl)/2;
	build(p*2,cl,mid);build(p*2+1,mid+1,cr);
	tree[p]=max(tree[p*2],tree[p*2+1]);
}
void ask(const int l,const int r,int cl,int cr,int p,ll &ans){
	if(cl>=l&&cr<=r){
		ans=max(ans,tree[p]);
		return;
	}
	int mid=cl+(cr-cl)/2;
	if(cl!=cr){
		if(l<=mid)ask(l,r,cl,mid,p*2,ans);
		if(r>mid)ask(l,r,mid+1,cr,p*2+1,ans);
	}
}
void update(const int l,int cl,int cr,int p,ll d){
	if(cl==l&&cr==l){
		tree[p]=max(tree[p],d);
		return;
	}
	int mid=cl+(cr-cl)/2;
	if(cl!=cr){
		if(l<=mid)update(l,cl,mid,p*2,d);
		if(l>mid)update(l,mid+1,cr,p*2+1,d);
		tree[p]=max(tree[p*2],tree[p*2+1]);
	}
}
int main(){
	ios::sync_with_stdio(false);
    cin>>m>>D;
    for(int i=1;i<=m;i++)a[i]=numeric_limits<ll>::min();
    build(1,1,m);
	char opt;
	int len=0;
	ll t=0,x=0;
    for(int i=1;i<=m;i++){
        cin>>opt;
        if(opt=='Q'){
            cin>>x;
			t=numeric_limits<ll>::min();
            ask(len-x+1,len,1,m,1,t);
			cout<<t<<'\n';
        }
        else{
            cin>>x;
			x=(x+t)%D;
            update(++len,1,m,1,x);
        }
    }
	cout.flush();
	return 0;
}
