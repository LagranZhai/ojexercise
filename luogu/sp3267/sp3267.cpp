#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=3e4+4;
const int maxm=2e5+5;
const int maxa=1e6+6;
int n,m,l=0,r=0,ans=0;
int a[maxn],cnt[maxa],aans[maxm];
struct Que{
	int ii,ll,rr;
}q[maxm];
inline void add(int p){
	if(cnt[p]==0)ans++;
	cnt[p]++;
	return;
}
inline void del(int p){
	if(cnt[p]==1)ans--;
	cnt[p]--;
	return;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	cin>>m;
	for(int i=0;i<m;i++){
		cin>>q[i].ll>>q[i].rr;
		q[i].ii=i;
	}
	int block=n/sqrt(2*m/3);
	sort(q,q+m,[block](const Que &a,const Que &b){
		return a.ll/block!=b.ll/block?a.ll<b.ll:((a.ll/block)&1?a.rr<b.rr:a.rr>b.rr);
	});
	for(int i=0;i<m;i++){
		//int lll=,rrr=q[i].rr;
		while(l>q[i].ll)add(a[--l]);
		while(r<q[i].rr)add(a[++r]);
		while(l<q[i].ll)del(a[l++]);
		while(r>q[i].rr)del(a[r--]);
		aans[q[i].ii]=ans;
	}
	for(int i=0;i<m;i++)cout<<aans[i]<<'\n';
	
	return 0;
}
