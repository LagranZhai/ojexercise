#include<iostream>
using namespace std;
using ll=long long;
const int maxn=1e5;
const int P=998244353;
ll a[maxn+100];
ll tree1[maxn*4+100],tag1[maxn*4+100];
void pushup1(int p){
	tree1[p]=tree1[p*2]+tree1[p*2+1];tree1[p]%=P;
}
void build1(int cl,int cr,int p){
	if(cl==cr){
		tree1[p]=(1ll<<(63-__builtin_clzll(a[cl])));
		cout<<tree1[p]<<' ';
		tag1[p]=1ll;
		return;
	}
	int mid=(cl+cr)/2;
	build1(cl,mid,p*2);
	build1(mid+1,cr,p*2+1);
	pushup1(p);
}
void pushdown1(int p){
	tree1[p*2]*=tag1[p];tag1[p*2]*=tag1[p];
	tree1[p*2]%=P;
	tree1[p*2+1]*=tag1[p];tag1[p*2+1]*=tag1[p];
	tree1[p*2+1]%=P;
	tag1[p]=1ll;
}
void update1(int cl,int cr,int p,int l,int r,int d){
	if(cl>=l&&cr<=r){
		tree1[p]*=d;
		tree1[p]%=P;
		tag1[p]*=d;
	}
	if(cl!=cr){
		pushdown1(p);
		int mid=(cl+cr)/2;
		update1(cl,mid,p*2,l,r,d);
		update1(mid+1,cr,p*2+1,l,r,d);
		pushup1(p);
	}
}
void query1(int cl,int cr,int p,int l,int r,ll &ans){
	if(cl>=l&&cr<=r){
		ans+=tree1[p];
		ans%=P;
		return;
	}
	if(cl!=cr){
		pushdown1(p);
		int mid=(cl+cr)/2;
		query1(cl,mid,p*2,l,r,ans);
		query1(mid+1,cr,p*2+1,l,r,ans);
	}
}
ll tree2[maxn*4+100],tree3[maxn*4+100];
void pushup2(int p){
	tree2[p]=tree2[p*2]+tree2[p*2+1];tree2[p]%=P;
	tree3[p]=max(tree3[p*2],tree3[p*2+1]);tree3[p]%=P;
}
void build2(int cl,int cr,int p){
	if(cl==cr){
		tree2[p]=tree3[p]=a[cl]-(1ll<<(63-__builtin_clzll(a[cl])));
		cout<<tree2[p]<<endl;
		return;
	}
	int mid=(cl+cr)/2;
	build2(cl,mid,p*2);
	build2(mid+1,cr,p*2+1);
	pushup2(p);
}
void update2(int cl,int cr,int p,int l,int r){
	if(cl==cr){
		tree2[p]-=tree2[p]&(-tree2[p]);
		tree3[p]=tree2[p];
		return;
	}
	int mid=(cl+cr)/2;
	if(tree3[p*2]>0){
		update2(cl,mid,p*2,l,r);
	}
	else update1(cl,mid,p*2,l,r,0ll);
	if(tree3[p*2+1]>0){
		update2(mid+1,cr,p*2+1,l,r);
	}
	else update1(mid+1,cr,p*2+1,l,r,0ll);
	pushup2(p);
}
void query2(int cl,int cr,int p,int l,int r,ll &ans){
	if(cl>=l&&cr<=r){
		ans+=tree2[p];
		ans%=P;
		return;
	}
	if(cl!=cr){
		int mid=(cl+cr)/2;
		query2(cl,mid,p*2,l,r,ans);
		query2(mid+1,cr,p*2+1,l,r,ans);
	}
}
int main(){
	freopen("t3.txt","r",stdin);
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	build1(1,n,1);build2(1,n,1);
	fill(tag1,tag1+maxn*4,1);
	int q;
	cin>>q;
	int opt,l,r; 
	while(q--){
		cin>>opt;
		if(opt==1){
			cin>>l>>r;
			//cout<<1<<endl;
			update2(1,n,1,l,r);
		}
		if(opt==2){
			cin>>l>>r;
			//cout<<2<<endl;
			update1(1,n,1,l,r,2);
		}
		if(opt==3){
			cin>>l>>r;
			//cout<<3<<endl;
			ll ans1=0,ans2=0;
			query2(1,n,1,l,r,ans1);query1(1,n,1,l,r,ans2);
			cout<<ans1+ans2<<'\n';
		}
	}
	return 0;
}
