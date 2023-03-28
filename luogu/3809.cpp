#include<algorithm>
#include<string>
#include<iostream>
#include<typeinfo>
using namespace std;
const int maxn=1e6,maxm=127;
<<<<<<< HEAD
int rk[maxn*2+20],sa[maxn],tmp[maxn*2+20],cnt[128];
string s;
void solvesa(string &s){
	int n=s.size(),m=127;
=======
int rk[maxn*2+20],sa[maxn],tmp[maxn*2+20],cnt[maxn*2+20];
string s;
void solvesa(string &s){
	int n=s.size(),m=maxm;
>>>>>>> 69c3741 (a)
	s=" "+s;
	for(int i=1;i<=n;i++){ 
		++cnt[rk[i]=s[i]];
	}
<<<<<<< HEAD
	for(int i=1;i<=m;i++){//int i='a'?
=======
	for(int i=1;i<=m;i++){
>>>>>>> 69c3741 (a)
		cnt[i]+=cnt[i-1];
	}
	for(int i=n;i>=1;i--){
		sa[cnt[rk[i]]--]=i;
	}
	for(int w=1;;w*=2){
<<<<<<< HEAD
		int num=0;
=======
>>>>>>> 69c3741 (a)
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
<<<<<<< HEAD
		//auto& oldrk=tmp;
		//cout<<typeid(oldrk).name()<<endl; 
		//copy(rk+1,rk+n+1,oldrk+1);
		copy(rk+1,rk+n+2,tmp+1);
		num=1;
		rk[sa[1]]=1;
//		auto rp=[&](int x){return make_pair(oldrk[x],oldrk[x+w]);};
		auto rp=[&](int x){return make_pair(tmp[x],tmp[x+w]);};
		for(int i=2;i<=n;i++){
			rk[sa[i]]=(rp(sa[i-1])==rp(sa[i]))?num:++num;
		}
		if(n==num)break;
		m=num;
//		for(int i=1;i<=n;i++){
//			cout<<sa[i]<<' ';
//		}
//		cout<<endl;
//		getchar();
=======
		auto& oldrk=tmp; 
		copy(rk+1,rk+n+1,oldrk+1);
		auto rp=[&](int x){return make_pair(oldrk[x],oldrk[x+w]);};
        m=0;
		for(int i=1;i<=n;i++){
			rk[sa[i]]=(rp(sa[i-1])==rp(sa[i]))?m:++m;
		}
		if(n==m)break;
>>>>>>> 69c3741 (a)
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
