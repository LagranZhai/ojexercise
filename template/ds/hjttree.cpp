#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
const int maxn=10e5+5;
int a[maxn],root[maxn];
int cnt=0;
vector<int> v;
struct Node{
	int l,r,sum;
}hjt[maxn*40];
inline int getid(int x){return lower_bound(v.begin(),v.end(),x)-v.begin()+1;}
void insert(int cl,int cr,int pre,int& now,int p){
	hjt[++cnt]=hjt[pre];
	now=cnt;
	hjt[now].sum++;
	if(cl==cr)return;
	int mid=(cl+cr)>>1;
	if(p<=mid)insert(cl,mid,hjt[pre].l,hjt[now].l,p);
	else insert(mid+1,cr,hjt[pre].r,hjt[now].r,p);
}
int query(int cl,int cr,int l,int r,int k){
	if(cl==cr)return cl;
	int siz=hjt[hjt[r].l].sum-hjt[hjt[l].l].sum;
	int mid=(cl+cr)>>1;
	if(k<=siz)return query(cl,mid,hjt[l].l,hjt[r].l,k);
	else return query(mid+1,cr,hjt[l].r,hjt[r].r,k-siz);
}
int main(){
	ios::sync_with_stdio(false);
	//freopen("hjttree.txt","r",stdin);
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++){
		cin>>a[i];
		v.push_back(a[i]);
	}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	int nn=v.size();//+5
	for(int i=1;i<=n;i++){
		//root[i]=cnt+1;
		insert(1,n,root[i-1],root[i],getid(a[i-1]));
	}
	int ll,rr,k;
	for(int i=0;i<m;i++){
		cin>>ll>>rr>>k;
		cout<<v[query(1,n,root[ll-1],root[rr],k)-1]<<"\n";
	}
	//fclose(stdin);
	return 0;
}
