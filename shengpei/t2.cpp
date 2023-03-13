#include<set>
#include<iostream>
using namespace std;
using ll=long long;
const int maxn=8000;
ll a[maxn*8];
int scnt,rcnt;
struct Seg;
struct Rel{
    int mmin=0;
    Seg *l,*r;
    Rel(int _mmin,Seg* _l,Seg* _r){
        mmin=_mmin,l=_l,r=_r;
    }
    Rel(){
    	mmin=0;
	}
    bool operator<(Rel other)const{
        return a[mmin]>a[other.mmin];
    }
}rel[maxn*8];
struct Seg{
	int l,r;
	Rel* pre;Rel *suf;
	int mmax=0;
}seg[maxn*8];
set<Rel> r;
int n;
ll s[maxn*2]={0};
//int findf(int x){
//	return fa[x]=(fa[x]==x)?x:findf(fa[x]);
//}
//void merge(int u,int v){
//	int uf=findf(u),vf=findf(v);
//	if(uf!=vf){
//		fa[uf]=vf;
//	}
//	return;
//}
int main(){
//	freopen("late.in","r",stdin);
//	freopen("late.out","w",stdout);
    ios::sync_with_stdio(false);
    cin>>n;
//	for(int i=1;i<=n;i++){
//		fa[i]=i;
//	}
    for(int i=1;i<=n;i++){
        cin>>a[i];
        s[n]+=a[i];
        seg[i].l=i;seg[i].r=i;seg[i].mmax=i;
    }
    scnt=n+2;
    for(int i=1;i<n;i++){
		int _min=0;
		if(a[seg[i].mmax]<a[seg[i+1].mmax]){
			_min=seg[i].mmax;
		}
		else{
			_min=seg[i+1].mmax;
		}
		rel[i].mmin=_min;rel[i].l=&seg[i];rel[i].r=&seg[i+1];
        r.insert(rel[i]);
    }
    rcnt=n+2;
    seg[1].pre=&rel[0];seg[n].suf=&rel[0];
    for(int i=1;i<=n;i++){
    	if(i>=2)seg[i].pre=&rel[i-1];
    	if(i<=n-1)seg[i].suf=&rel[i];
	}
    for(int i=n-1;i>=1;i--){
		Rel rmax=*r.begin();
		int mmax=rmax.mmin;
		s[i]=s[i+1]-a[mmax];
		r.erase(r.begin());
		if(rmax.l->pre!=&rel[0])r.erase(*(rmax.l->pre));
		if(rmax.r->suf!=&rel[0])r.erase(*(rmax.r->suf));
		//merge(rmax.l->mmax,rmax.l->mmax);
		seg[++scnt].mmax=(a[rmax.l->mmax]>a[rmax.r->mmax])?rmax.l->mmax:rmax.r->mmax;
		seg[scnt].l=rmax.l->l;seg[scnt].r=rmax.r->r;
		if(rmax.r->suf!=&rel[0]){
			rel[++rcnt].l=&seg[scnt];rel[rcnt].r=rmax.r->suf->r;
			rel[rcnt].mmin=(a[rel[rcnt].l->mmax]<a[rel[rcnt].r->mmax])?rel[rcnt].l->mmax:rel[rcnt].r->mmax;
			seg[scnt].suf=&rel[rcnt];r.insert(rel[rcnt]);
		}
		else seg[scnt].suf=&rel[0];
		if(rmax.l->pre!=&rel[0]){
			rel[++rcnt].l=rmax.l->pre->l;rel[rcnt].r=&seg[scnt];
			rel[rcnt].mmin=(a[rel[rcnt].l->mmax]<a[rel[rcnt].r->mmax])?rel[rcnt].l->mmax:rel[rcnt].r->mmax;
			seg[scnt].pre=&rel[rcnt];r.insert(rel[rcnt]);
		}
		else seg[scnt].pre=&rel[0];
    }
    // priority_queue<>
	for(int i=1;i<=n;i++)cout<<s[i]<<' ';
	cout.flush();
    return 0;
}
