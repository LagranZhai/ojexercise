#include<iostream>
#include<map>
#include<unordered_map>
using namespace std;
using ull=unsigned long long;
const int maxn=2e4,base=131,P=998244353;
int n,k;
ull p[maxn+10],mhash[maxn+10];
string s;
void init(){
	p[0]=1;
	for(int i=1;i<=maxn;i++){
		p[i]=p[i-1]*base%P;
	}
}
void inithash(){
	ull ans=0;
	for(int i=0;i<s.size();i++){
		ans=((ans*base)%P+s[i])%P;
		mhash[i]=ans;
	}
}
ull gethash(int l,int r){
	return (mhash[r]-(p[r-l+1]*mhash[l-1])%P)%P;
}
bool chck(int k,int m){
	unordered_map<ull,int> h;
	for(int i=0;i+k-1<s.size();i++){
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
	char c;
	for(int i=1;i<=n;i++){
		cin>>c;
		s+=c;
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
