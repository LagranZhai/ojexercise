#include<iostream>
using namespace std;
const int maxn=1e6+6;
int a[maxn],root[maxn],l[maxn];
int cnt=0;
struct Node{
	int l,r,num;
}hjt[maxn*50];
void update(int cl,int cr,int pre,int &now,int cur,int p,int v){
	hjt[cur]=hjt[pre];
	now=cur;
	hjt[now].num+=v;
	if(cl==cr)return;
	int mid=(cl+cr)>>1;
	++cnt;
	if(p<=mid)update(cl,mid,hjt[pre].l,hjt[now].l,cnt,p,v);
	else  update(mid+1,cr,hjt[pre].r,hjt[now].r,cnt,p,v);
	return;
}
int query(int cl,int cr,int l,int r,int now){
	if(cl>=cr||now==0)return 0;
	if(cl>=l&&cr<=r)return hjt[now].num;
	int mid=(cl+cr)>>1;
	int la=0,ra=0;
	if(hjt[now].l!=0)la=query(cl,mid,l,r,hjt[now].l);
	if(hjt[now].r!=0)ra=query(mid+1,cr,l,r,hjt[now].r);
	return la+ra;
} 
int n,m;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(l[a[i]]!=0){
			update(1,n,root[i-1],root[i],++cnt,l[a[i]],-1);
			update(1,n,root[i],root[i],cnt,i,1);
		}
		else update(1,n,root[i-1],root[i],++cnt,i,1);
	}
	cin>>m;
	int l,r;
	while(m--){
		cin>>l>>r;
		cout<<query(1,n,l,r,root[r])<<'\n';
	}
	return 0;
} 
