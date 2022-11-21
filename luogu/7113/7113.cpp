#include<bits/stdc++.h>
using namespace std;
const long long maxn=1e5+10;
long long n,m,eend[15],cnt=0,deg[maxn];
vector<long long> edg[maxn];
queue<long long> q;
long long gcd(long long a,long long b){
	return b>0?gcd(b,a%b):a;
}
struct Frac{
	long long p=0,q=1;
	void yf(){
		long long gg=gcd(p,q);
		if(!gg)return; 
		p/=gg;
		q/=gg; 
	}
	Frac(long long _p=0,long long _q=1):p(_p),q(_q){yf();}
	Frac add(const Frac &A)const{
		return Frac(this->p*A.q+this->q*A.p,this->q*A.q);
	}
	Frac times(const Frac &A)const{
		return Frac(this->p*A.p,this->q*A.q);
	}
}v[maxn];
void solve(long long p){
	Frac tt=v[p].times(Frac(1,edg[p].size()));
	for(long long to:edg[p]){
		v[to]=v[to].add(tt);
	}
	v[p]=Frac(0,1);
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	long long num,tmp;
	for(long long i=1;i<=n;i++){
		cin>>num;
		if(num==0){
			eend[++cnt]=i;
		}
		else{
			for(long long j=0;j<num;j++){
				cin>>tmp;
				deg[tmp]++;
				edg[i].push_back(tmp);
			}
		}
	}
	for(long long i=1;i<=m;i++){
		q.push(i);
		v[i]=Frac(1,1);
	}
	while(!q.empty()){
		long long fr=q.front();
		if(edg[fr].empty()){
			q.pop();continue;
		}
		solve(fr);
		for(long long to:edg[fr]){
			deg[to]--;
			if(!deg[to])q.push(to);
		}
		q.pop();
	}
	for(long long i=1;i<=cnt;i++){
		v[eend[i]].yf();
		cout<<v[eend[i]].p<<' '<<v[eend[i]].q<<'\n';
	}
	//return 0;
}
