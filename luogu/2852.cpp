#include<iostream>
#include<map>
#include<unordered_map>
using namespace std;
//using ull=unsigned long long;
using ll=long long;
using pll=pair<ll,ll>;
const int maxn=2e4,base=131,P=1e9+7,P2=1e9+9;
int n,k,a[maxn+10];
ll p[maxn+10],mhash[maxn+10],p2[maxn+10],mhash2[maxn+10];
//string s;
void init(){
	p[0]=1;p2[0]=1;
	for(int i=1;i<=maxn+1;i++){
		p[i]=p[i-1]*base%P;
		p2[i]=p2[i-1]*base%P2;
	}
}
void inithash(){
	ll ans=0,ans2=0;
	for(int i=0;i<n;i++){
		ans=((ans*base)%P+a[i])%P;
		mhash[i]=ans;
		ans2=((ans2*base)%P2+a[i])%P2;
		mhash2[i]=ans2;
	}
}
ll gethash(int l,int r){
	ll res=mhash[r]-(p[r-l+1]*mhash[l-1])%P;
	res=(res%P+P)%P;
	ll res2=mhash2[r]-(p2[r-l+1]*mhash2[l-1])%P2;
	res2=(res2%P2+P2)%P2;
	return res;
}
bool chck(int k,int m){
	unordered_map<ll,int> h;
	for(int i=0;i+k-1<n;i++){
		if(h.find(gethash(i,i+k-1))==h.end()){
			h.insert(make_pair(gethash(i,i+k-1),1));
		}
		else{
			h[gethash(i,i+k-1)]++;
		}
		if(h[gethash(i,i+k-1)]>=m){
			return true;
		}
	}
	return false;
}
int main(){
	ios::sync_with_stdio(false);
	init();
	cin>>n>>k;
	int x;
	for(int i=1;i<=n;i++){
		cin>>x;
		a[i-1]=x;
	}
	//cout<<s<<endl;
	inithash();
	int l=1,r=n,mid;
	while(l<r-1){
		mid=(l+r)/2;
		if(chck(mid,k)){
			l=mid;
		}
		else{
			r=mid;
		}
	}
	cout<<l<<endl;
	return 0;
} 
