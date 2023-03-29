//luogu2408
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5,maxm=127;
string s;
int n,cnt[maxn*2+20],sa[maxn+10],rk[maxn*2+20],tmp[maxn*2+20];
int h[maxn*2+100];
void sasolve(string &s,int &n){
	int m=maxm;
	s=" "+s;
	for(int i=1;i<=n;i++){
		cnt[rk[i]=s[i]]++;
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
		for(int i=1,j=w;i<=n;i++){
			if(sa[i]>w)tmp[++j]=sa[i]-w;
		}
		fill(cnt+1,cnt+1+m,0);
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
		copy(rk+1,rk+1+n,oldrk+1);
		auto rp=[&](int x){return make_pair(oldrk[x],oldrk[x+w]);};
		m=0;
		for(int i=1;i<=n;i++){
			rk[sa[i]]=(rp(sa[i])==rp(sa[i-1]))?m:++m;
		}
		if(n==m)break;
	}
}
auto heightsolve(string &s,int &n){
	int k=0;
	long long a=0;
	//h[1]=0;
	for(int i=1;i<=n;i++){
		if(k)k--;
		while(s[sa[rk[i]]+k]==s[sa[rk[i]-1]+k])k++;
		h[rk[i]]=k;
		a+=k;
	}
	return a;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>s;
	sasolve(s,n);
	cout<<1ll*n*(n+1)/2-heightsolve(s,n);
	return 0;
}
