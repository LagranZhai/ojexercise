#include<algorithm>
#include<string>
#include<iostream>
#include<typeinfo>
using namespace std;
const int maxn=1e6,maxm=127;
int rk[maxn*2+20],sa[maxn],tmp[maxn*2+20],cnt[maxn*2+20];
string s;
void solvesa(string &s){
	int n=s.size(),m=maxm;
	s=" "+s;
	for(int i=1;i<=n;i++){ 
		++cnt[rk[i]=s[i]];
	}
	for(int i=1;i<=m;i++){
		cnt[i]+=cnt[i-1];
	}
	for(int i=n;i>=1;i--){
		sa[cnt[rk[i]]--]=i;
	}
	for(int w=1;;w*=2){
		for(int i=n;i>n-w;i--){
			tmp[n-i+1]=i;
		}
		for(int i=1,p=w;i<=n;i++){
			if(sa[i]>w)tmp[++p]=sa[i]-w;
		}
		fill(cnt+1,cnt+2+m,0);
		for(int i=1;i<=n;i++){
			cnt[rk[tmp[i]]]++;
		}
		for(int i=1;i<=m;i++){
			cnt[i]+=cnt[i-1];
		}
		for(int i=n;i>=1;i--){
			sa[cnt[rk[tmp[i]]]--]=tmp[i];
		}
		auto& oldrk=tmp; 
		copy(rk+1,rk+n+1,oldrk+1);
		auto rp=[&](int x){return make_pair(oldrk[x],oldrk[x+w]);};
        m=0;
		for(int i=1;i<=n;i++){
			rk[sa[i]]=(rp(sa[i-1])==rp(sa[i]))?m:++m;
		}
		if(n==m)break;
	}
	for(int i=1;i<=n;i++){
		cout<<sa[i]<<' ';
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>s;
	solvesa(s);
	return 0;
}
