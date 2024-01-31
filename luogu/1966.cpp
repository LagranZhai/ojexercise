#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::ios;
constexpr int maxn=1e5,P=1e8-3;
#define int long long
int n;
struct Node{
	int h,index,rindex;
}a[maxn*2],b[maxn*2];
int oa[maxn*2];
int bit[maxn*2];
int lowbit(int x){
	return x&(-x);
}
int query(int x){
	int res{0};
	while(x>0){
		res+=bit[x];
		x-=lowbit(x);
	}
	return res;
}
void update(int x,int d){
	if(x==0)return ;
	while(x<=n){
		bit[x]+=d;
		x+=lowbit(x);
	}
	return ;
}
signed main(){
	freopen("1966.in","r",stdin);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n;
	int tmp;
	for(int i{1};i<=n;i++){
		cin>>a[i].h;
		a[i].index=i;
	}
	for(int i{1};i<=n;i++){
		cin>>b[i].h;
		b[i].index=i;
	}
	auto lam=[](const Node &a,const Node &b){
		return a.h<b.h;
	};
	std::sort(a+1,a+n+1,lam);
	std::sort(b+1,b+n+1,lam);
	for(int i{1};i<=n;i++){
		b[i].rindex=a[i].index;
	}
	std::sort(b+1,b+n+1,[](const Node &a,const Node &b){
		return a.index<b.index;
	});
	int ans{0};
//	for(int i{1};i<=n;i++){
//		cout<<b[i].rindex<<" ";
//	}
	for(int i{n};i>=1;i--){
		ans=(ans+query(b[i].rindex-1))%P;
		update(b[i].rindex,1);
	}
//	cout<<n<<"\n";
	cout<<ans<<"\n";
	cout.flush();
	return 0;
}