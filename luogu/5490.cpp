#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
using ll=long long;
ll len[maxn*4];
ll mark[maxn*4];
ll a[maxn];
int n,tot;
struct Scanline
{
	ll x,y1,y2,mark;//y1<y2
	Scanline(ll _x,ll _y1,ll _y2,ll _mark):x(_x),y1(_y1),y2(_y2),mark(_mark){}
}sl[maxn];
vector<ll> arry;
inline void pushdown(int p,int len){
	mark[p*2]+=mark[p];
	tree[p*2]+=mark[p]*(len-len/2);
	mark[p*2+1]+=mark[p];
	tree[p*2+1]+=mark[p]*(len/2);
	mark[p]=0;
}
void build(int p,int cl,int cr){
	if(cl==cr){
		tree[p]=a[cl];
		return;
	}
	int mid=cl+(cr-cl)/2;
	build(p*2,cl,mid);build(p*2+1,mid+1,cr);
	tree[p]=tree[p*2]+tree[p*2+1];
}
void ask(const int l,const int r,int cl,int cr,int p,ll &ans){
	if(cl>=l&&cr<=r){
		ans+=tree[p];
		return;
	}
	int mid=cl+(cr-cl)/2;
	if(cl!=cr){
		pushdown(p,cr-cl+1);
		if(l<=mid)ask(l,r,cl,mid,p*2,ans);
		if(r>mid)ask(l,r,mid+1,cr,p*2+1,ans);
	}
}
void update(const int l,const int r,int cl,int cr,int p,ll d){
	if(cl>=l&&cr<=r){
		mark[p]+=d;
		tree[p]+=d*(cr-cl+1);
		return;
	}
	int mid=cl+(cr-cl)/2;
	if(cl!=cr){
		pushdown(p,cr-cl+1);
		if(l<=mid)update(l,r,cl,mid,p*2,d);
		if(r>mid)update(l,r,mid+1,cr,p*2+1,d);
		tree[p]=tree[p*2]+tree[p*2+1];
	}
}
int main(){
	ios::sync_with_stdio(false);
    cin>>n;
	int x1,x2,y1,y2;
    for(int i=1;i<=n;i++){
        cin>>x1>>y1>>x2>>y2;
		arry.push_back(y1);arry.push_back(y2);
		if(y1>y2)swap(y1,y2);
		if(x1>x2)swap(x1,x2);
		sl[++tot]=Scanline(x1,y1,y2,1);
		sl[++tot]=Scanline(x2,y1,y2,-1);
    }
	sort(arry.begin(),arry.end());
	arry.erase(unique(arry.begin(),arry.end()),arry.end());
	int nn=arry.size();//0-index
    build(1,1,nn);
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
            cout<<ans<<endl;
        }
    }
	cout.flush();
	return 0;
}
