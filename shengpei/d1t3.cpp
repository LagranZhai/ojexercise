#include<iostream>
#include<deque>
using namespace std;
using ll=long long;
const int maxn=1e5;
const int P=998244353;
ll a[maxn+100];
namespace seg1{
ll tag1[maxn*2],tag2[maxn*2];
struct Node{
	deque<ll> ctz;
	ll sum=0;
}tree[maxn<<2];
ll lowbit(ll x){
	return x&(-x);
}
void pushup(int cl,int cr,int p){
	tree[p].sum=tree[p*2].sum+tree[p*2+1].sum;
	tree[p].sum%=P;
//	tree[p].ctz=tree[p*2].ctz+tree[p*2+1].ctz;
	int i=0;
	if(!tree[p*2].ctz.empty()&&!tree[p*2+1].ctz.empty()){
		for(int i=0;i<min(tree[p*2].ctz.size(),tree[p*2+1].ctz.size());i++){
			tree[p].ctz.push_back((tree[p*2].ctz[i]+tree[p*2+1].ctz[i])%P);
		}
	}	
	if(!tree[p*2].ctz.empty())while(i<tree[p*2].ctz.size())tree[p].ctz.push_back(tree[p*2].ctz[i]);
	if(!tree[p*2+1].ctz.empty())while(i<tree[p*2+1].ctz.size())tree[p].ctz.push_back(tree[p*2+1].ctz[i]);
//	for(int i=0;i<min(tree[p*2].clz.size(),tree[p*2+1].clz.size());i++){
//		tree[p].clz.push_back(tree[p*2].clz[i],tree[p*2+1].clz[i]);
//	}
}
void build(int cl,int cr,int p){
	if(cl==cr){
		tag1[p]=0;
		tree[p].sum=a[cl];
		ll x=a[cl];
		while(x>0ll){
			tree[p].ctz.push_back(lowbit(x));
			x-=lowbit(x);
		}
//		tree[p].ctz=lowbit(x)
//		for(int i=tree[p].ctz.size()-1;i>=0;i--){
//			tree[p].clz.push_back(tree[p].ctz[i]);
//		}
		return;
	}
	int mid=(cl+cr)/2;
	build(cl,mid,p*2);
	build(mid+1,cr,p*2+1);
	pushup(cl,cr,p);
}
void ope1(int p,int d){
	while(!tree[p].ctz.empty()&&d>0){
		tree[p].sum-=tree[p].ctz[0];
		tree[p].ctz.pop_front();
		d--;
	}
	return;
}
void pushdown(int cl,int cr,int p){
	tag1[p*2]=tag1[p];tag1[p*2+1]=tag1[p];
	ope1(p*2,tag1[p]);ope1(p*2+1,tag1[p]);
	tag1[p]=0;
}
void update1(int cl,int cr,int p,int l,int r){
	if(cl>=l&&cr<=r){
		if(!tree[p].ctz.empty()){
			tree[p].sum-=tree[p].ctz[0];
			tree[p].ctz.pop_front();
		}		
		tag1[p]+=1;
	}
	//pushdown(cl,cr,p);
//	if(cl==cr){
//		tree[p].sum-=tree[p].ctz[0];
//		tree[p].ctz=lowbit(tree[p].sum);
//		return;
//	}
	if(cl!=cr){
		pushdown(cl,cr,p);
		int mid=(l+r)/2;
		if(l<=mid)update1(cl,mid,p*2,l,r);
		if(r>mid)update1(mid+1,cr,p*2+1,l,r);
		pushup(cl,cr,p);
	}
}
void query(int cl,int cr,int p,int l,int r,ll &ans){
	if(cl>=l&&cr<=r){
		ans+=tree[p].sum;
		ans%=P;
		return;
	}
	if(cl!=cr){
		pushdown(cl,cr,p);
		int mid=(cl+cr)/2;
		if(l<=mid)query(cl,mid,p*2,l,r,ans);
		if(r>mid)query(mid+1,cr,p*2+1,l,r,ans);
	}
}
}
struct Que{
	int o,l,r;
}que[maxn*2];
void modify1(int l,int r){
	for(int i=l;i<=r;i++){
		a[i]-=(a[i])&(-a[i]);
		a[i]%=P;
	}
}
void modify2(int l,int r){
	for(int i=l;i<=r;i++){
		a[i]+=(1ll<<(63-__builtin_clzll(a[i])));
		a[i]%=P;
	}
}
ll ask(int l,int r){
	ll ans=0;
	for(int i=l;i<=r;i++){
		ans+=a[i];ans%=P;
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int q;
	cin>>q;
	int flag1=1,flag2=1;
	for(int i=1;i<=q;i++){
		cin>>que[i].o>>que[i].l>>que[i].r;
		if(que[i].o==2)flag1=0;
		if(que[i].o==1)flag2=0;
	}
	flag1=flag2=0;
	if(flag1==1){
		seg1::build(1,n,1);
		for(int i=1;i<=q;i++){
			if(que[i].o==1){
				seg1::update1(1,n,1,que[i].l,que[i].r);
                 			}
			if(que[i].o==3){
				ll ans=0;
				seg1::query(1,n,1,que[i].l,que[i].r,ans);
				cout<<ans<<'\n';
			}
		}
	}
	else if(flag2){
	}
	else{
		for(int i=1;i<=q;i++){
			if(que[i].o==1){
				modify1(que[i].l,que[i].r);
			}
			if(que[i].o==2){
				modify2(que[i].l,que[i].r);
			}
			if(que[i].o==3){
				cout<<ask(que[i].l,que[i].r)<<endl;
			}
		}
	}
	return 0;
}
