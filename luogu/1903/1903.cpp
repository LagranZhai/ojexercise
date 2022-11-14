#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn=134000;
const int maxc=1e6+6;
int a[maxn],b[maxn],cnt[maxc],aans[maxn];
int n,m,cntq=0,cntr=0,ans=0,cl=0,cr=0,t=0;
struct Res{
    int p,col,lst;
}r[maxn];
struct Que{
    int ii,ll,rr,pre;
}q[maxn];
//inline int rd(){
//    int w=0;
//    char c=getchar();
//    while(c<'0'||c>'9')c=getchar();
//    while(c>='0'&&c<='9')w=w*10+c-'0',c=getchar();
//    return w;
//}
//inline int rdch(){
//    char c=getchar();
//    while(c!='R'&&c!='Q')c=getchar();
//    if(c=='R')return 0;
//    if(c=='Q')return 1;
//}
inline void add(int c){
 	ans+=!(cnt[c]++);
}
inline void del(int c){
	ans-=!(--cnt[c]);
}
inline void dot(int tt){
	if(r[tt].p>=cl&&r[tt].p<=cr){
		ans-=!(--cnt[a[r[tt].p]]);
		a[r[tt].p]=r[tt].col;
		ans+=!(cnt[r[tt].col]++);
		return;
	}
	a[r[tt].p]=r[tt].col;
	return;	
}
inline void undot(int tt){
	if(r[tt].p>=cl&&r[tt].p<=cr){
		ans-=!(--cnt[a[r[tt].p]]);
		a[r[tt].p]=r[tt].lst;
		ans+=!(cnt[r[tt].lst]++);
		return;
	}
	a[r[tt].p]=r[tt].lst;
	return;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
    	cin>>a[i];
    	b[i]=a[i];
	}
    char typ;
    for(int i=1;i<=m;++i){
    	cin>>typ;
    	//printf("%d\n",typ);
        if(typ=='Q'){
        	++cntq;
            q[cntq].ii=cntq;
            q[cntq].pre=cntr;
            cin>>q[cntq].ll;
            cin>>q[cntq].rr;
        }
        else{
            cin>>r[++cntr].p;
            cin>>r[cntr].col;
            r[cntr].lst=b[r[cntr].p];
            b[r[cntr].p]=r[cntr].col;
        }
    }
    long long bb=1ll*n*n;
    int block=pow(n,2/3.0);
    sort(q+1,q+cntq+1,[block](const Que &a,const Que &b){
    	return a.ll/block!=b.ll/block?a.ll<b.ll:(a.rr/block!=b.rr/block?a.rr<b.rr:a.pre<b.pre);
	});
	for(int i=1;i<=cntq;++i){
		while(t<q[i].pre){
			dot(++t);
//			++t;
//			if(r[t].p>=cl&&r[t].p<=cr)del(a[r[t].p]);
//			a[r[t].p]=r[t].col;
//			if(r[t].p>=cl&&r[t].p<=cr)add(a[r[t].col]);
		}
		while(t>q[i].pre){
			undot(t--);
//			if(r[t].p>=cl&&r[t].p<=cr)del(a[r[t].p]);
//			a[r[t].p]=r[t].col;
//			if(r[t].p>=cl&&r[t].p<=cr)del(r[t].col);
//			t--;
		}
		while(cl>q[i].ll)add(a[--cl]);
		while(cr<q[i].rr)add(a[++cr]);
		while(cl<q[i].ll)del(a[cl++]);
		while(cr>q[i].rr)del(a[cr--]);
		aans[q[i].ii]=ans;
	}
	for(int i=1;i<=cntq;++i)cout<<aans[i]<<'\n';
	return 0;
}
