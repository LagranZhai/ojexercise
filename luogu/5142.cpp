#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int maxn=2e5+5;
const int P=1000000007;
ll tree_sum[maxn*4];
ll tree_sqr[maxn*4];
ll mark[maxn*4];
ll a[maxn];
int n,m;
inline void pushdown(int p,int len){
	mark[p*2]+=mark[p];mark[p*2]%=P;
    tree_sqr[p*2]+=((((mark[p]*mark[p])%P)*(len-len/2))%P+(2ll*mark[p]*tree_sum[p*2])%P)%P;
    tree_sqr[p*2]%=P;
	tree_sum[p*2]+=(mark[p]*(len-len/2))%P;tree_sum[p*2]%=P;
	mark[p*2+1]+=mark[p];mark[p*2+1]%=P;
    tree_sqr[p*2+1]+=((mark[p]*mark[p]%P*(len/2)%P+2ll*mark[p]*tree_sum[p*2+1]%P)%P)%P;
	tree_sqr[p*2+1]%=P;
	tree_sum[p*2+1]+=mark[p]*(len/2)%P;tree_sum[p*2+1]%=P;
	mark[p]=0;
} 
void build(int p,int cl,int cr){
	if(cl==cr){
		tree_sum[p]=a[cl];
        tree_sqr[p]=a[cl]*a[cl]%P;
		return;
	}
	int mid=cl+(cr-cl)/2;
	build(p*2,cl,mid);build(p*2+1,mid+1,cr);
	tree_sum[p]=(tree_sum[p*2]+tree_sum[p*2+1])%P;
    tree_sqr[p]=(tree_sqr[p*2]+tree_sqr[p*2+1])%P;
}
void ask_sum(const int l,const int r,int cl,int cr,int p,ll &ans){
	if(cl>=l&&cr<=r){
		ans+=tree_sum[p];ans%=P;
		return;
	}
	int mid=cl+(cr-cl)/2;
	if(cl!=cr){
		pushdown(p,cr-cl+1);
		if(l<=mid)ask_sum(l,r,cl,mid,p*2,ans);
		if(r>mid)ask_sum(l,r,mid+1,cr,p*2+1,ans);
	}
}
void ask_sqr(const int l,const int r,int cl,int cr,int p,ll &ans){
	if(cl>=l&&cr<=r){
		ans+=tree_sqr[p];ans%=P;
		return;
	}
	int mid=cl+(cr-cl)/2;
	if(cl!=cr){
		pushdown(p,cr-cl+1);
		if(l<=mid)ask_sqr(l,r,cl,mid,p*2,ans);
		if(r>mid)ask_sqr(l,r,mid+1,cr,p*2+1,ans);
	}
}
void update(const int l,const int r,int cl,int cr,int p,ll d){
	if(cl>=l&&cr<=r){
		mark[p]+=d;mark[p]%=P;
		//tree_sum[p]+=d*(cr-cl+1);
        tree_sqr[p]+=(d*d%P*(cr-cl+1)%P+2ll*d*tree_sum[p]%P)%P;tree_sqr[p]%=P;
        tree_sum[p]+=d*(cr-cl+1)%P;tree_sum[p]%=P;
		return;
	}
	int mid=cl+(cr-cl)/2;
	if(cl!=cr){
		pushdown(p,cr-cl+1);
		if(l<=mid)update(l,r,cl,mid,p*2,d);
		if(r>mid)update(l,r,mid+1,cr,p*2+1,d);
		tree_sum[p]=(tree_sum[p*2]+tree_sum[p*2+1])%P;
        tree_sqr[p]=(tree_sqr[p*2]+tree_sqr[p*2+1])%P;
	}
}
inline ll qpow(ll a,ll b){
    ll ans=1;
    while(b>0){
        if(b&1)ans=ans*a%P;
        b>>=1;
        a=a*a%P;
    }
    return ans;
} 
int main(){
	ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1,1,n);
    ll opt,x,y;
    ll d;
    for(int i=0;i<m;i++){
        cin>>opt;
        if(opt==1){
            cin>>x>>d;
            update(x,x,1,n,1,d);
        }
        else{
            cin>>x>>y;
            ll ans1=0,ans2=0,len=y-x+1;
            ask_sum(x,y,1,n,1,ans1);
            ask_sqr(x,y,1,n,1,ans2);
            ll ny=qpow(len,P-2);
			ans1=ans1*ny%P;ans2=ans2*ny%P;
            cout<<(ans2-ans1*ans1%P)%P<<endl;
			//cout<<ans2<<endl;
        }
    }
	cout.flush();
	return 0;
}
