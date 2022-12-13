#include<iostream>
using namespace std;
const int maxn=2e5+5;
double tree_sum[maxn*4];
double tree_sqr[maxn*4];
double mark[maxn*4];
double a[maxn];
int n,m;
inline void pushdown(int p,int len){
	mark[p*2]+=mark[p];
    tree_sqr[p*2]+=mark[p]*mark[p]*(double)(len-len/2)+2.0*mark[p]*tree_sum[p*2];
	tree_sum[p*2]+=mark[p]*(len-len/2);
	mark[p*2+1]+=mark[p];
    tree_sqr[p*2+1]+=mark[p]*mark[p]*(double)(len/2)+2.0*mark[p]*tree_sum[p*2+1];
	tree_sum[p*2+1]+=mark[p]*(len/2);
	mark[p]=0;
}
void build(int p,int cl,int cr){
	if(cl==cr){
		tree_sum[p]=a[cl];
        tree_sqr[p]=a[cl]*a[cl];
		return;
	}
	int mid=cl+(cr-cl)/2;
	build(p*2,cl,mid);build(p*2+1,mid+1,cr);
	tree_sum[p]=tree_sum[p*2]+tree_sum[p*2+1];
    tree_sqr[p]=tree_sqr[p*2]+tree_sqr[p*2+1];
}
void ask_sum(const int l,const int r,int cl,int cr,int p,double &ans){
	if(cl>=l&&cr<=r){
		ans+=tree_sum[p];
		return;
	}
	int mid=cl+(cr-cl)/2;
	if(cl!=cr){
		pushdown(p,cr-cl+1);
		if(l<=mid)ask_sum(l,r,cl,mid,p*2,ans);
		if(r>mid)ask_sum(l,r,mid+1,cr,p*2+1,ans);
	}
}
void ask_sqr(const int l,const int r,int cl,int cr,int p,double &ans){
	if(cl>=l&&cr<=r){
		ans+=tree_sum[p];
		return;
	}
	int mid=cl+(cr-cl)/2;
	if(cl!=cr){
		pushdown(p,cr-cl+1);
		if(l<=mid)ask_sqr(l,r,cl,mid,p*2,ans);
		if(r>mid)ask_sqr(l,r,mid+1,cr,p*2+1,ans);
	}
}
void update(const int l,const int r,int cl,int cr,int p,int d){
	if(cl>=l&&cr<=r){
		mark[p]+=d;
		//tree_sum[p]+=d*(cr-cl+1);
        tree_sqr[p]+=d*d*(double)(cr-cl+1)+2.0*d*tree_sum[p];
        tree_sum[p]+=d*(cr-cl+1);
		return;
	}
	int mid=cl+(cr-cl)/2;
	if(cl!=cr){
		pushdown(p,cr-cl+1);
		if(l<=mid)update(l,r,cl,mid,p*2,d);
		if(r>mid)update(l,r,mid+1,cr,p*2+1,d);
		tree_sum[p]=tree_sum[p*2]+tree_sum[p*2+1];
        tree_sqr[p]=tree_sqr[p*2]+tree_sqr[p    *2+1];
	}
}
int main(){
	ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1,1,n);
    int opt,x,y;
    double d;
    for(int i=0;i<m;i++){
        cin>>opt;
        if(opt==1){
            cin>>x>>y>>d;
            update(x,y,1,n,1,d);
        }
        else if(opt==2){
            cin>>x>>y;
            double ans=0;
            ask_sum(x,y,1,n,1,ans);
            cout<<ans/(double)((y-x+1))<<endl;
        }
        else{
            cin>>x>>y;
            double ans1=0,ans2=0;
            ask_sum(x,y,1,n,1,ans1);
            ask_sqr(x,y,1,n,1,ans2);
            cout<< -ans1*ans1/(double)((y-x+1)*(y-x+1))+ans2/(double)(y-x+1)<<endl;
        }
    }
	cout.flush();
	return 0;
}
