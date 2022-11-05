#include<cstdio>
using namespace std;
const int maxn=1e6+6;
int a[maxn],root[maxn],l[maxn];
int cnt=0;
int n,m;
inline int rd(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
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
int query(int cl,int cr,int ql,int qr,int now){
	if(cl>=ql&&cr<=qr)return hjt[now].num;
	if(cl>qr||cr<ql)return 0;
	if(cl==cr||now==0)return 0;
	int mid=(cl+cr)/2;
	int la=0,ra=0;
	if(hjt[now].l!=0&&ql<=mid)la=query(cl,mid,ql,qr,hjt[now].l);
	if(hjt[now].r!=0&&qr>mid)ra=query(mid+1,cr,ql,qr,hjt[now].r);
	return la+ra;
}
int main(){
	//ios::sync_with_stdio(false);
	//cin.tie(0);
	n=rd();
	for(int i=1;i<=n;i++){
		a[i]=rd();
		if(l[a[i]]!=0){
			update(1,n,root[i-1],root[i],++cnt,l[a[i]],-1);
			update(1,n,root[i],root[i],root[i],i,1);
		}
		else update(1,n,root[i-1],root[i],++cnt,i,1);
		l[a[i]]=i;
	}
	scanf("%d",&m);
	int l,r;
//	for(int i=1;i<=n;i++){
//		cout<<hjt[root[i]].num<<' ';
//	} 
	while(m--){
		l=rd();r=rd();
		printf("%d\n",query(1,n,l,r,root[r]));
	}
	return 0;
} 
