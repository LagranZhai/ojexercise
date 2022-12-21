#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int tree[maxn*4];
int a[maxn];
int n,q;
struct Shift{
	int cnt=0,shift[100];
	Shift(string s){
		int w=0;
		int i=0;
		while(s[i]!='(')i++;
		while(s[i]!=')'){
			if(s[i]==','){
				shift[cnt++]=w;w=0;
			}
			else if(s[i]>='0'&&s[i]<='9'){
				w=w*10+(s[i]-'0');
			}
			i++;
		}
		shift[cnt++]=w;
	}
};
struct Que{
	int l,r;
	Que(string s){
		int w=0;
		int i=0;
		while(s[i]!='(')i++;
		while(s[i]!=')'){
			if(s[i]==','){
				l=w;w=0;
			}
			else if(s[i]>='0'&&s[i]<='9'){
				w=w*10+(s[i]-'0');
			}
			i++;
		}
		r=w;
	}
};
void build(int p,int cl,int cr){
	if(cl==cr){
		tree[p]=a[cl];
		return;
	}
	int mid=cl+(cr-cl)/2;
	build(p*2,cl,mid);build(p*2+1,mid+1,cr);
	tree[p]=min(tree[p*2],tree[p*2+1]);
}
void ask(const int l,const int r,int cl,int cr,int p,int &ans){
	if(cl>=l&&cr<=r){
		ans=min(ans,tree[p]);
		return;
	}
	int mid=cl+(cr-cl)/2;
	if(cl!=cr){
		if(l<=mid)ask(l,r,cl,mid,p*2,ans);
		if(r>mid)ask(l,r,mid+1,cr,p*2+1,ans);
	}
}
void update(const int l,int cl,int cr,int p,int d){
	if(cl==l&&cr==l){
		a[l]=d;
		tree[p]=d;
		return;
	}
	int mid=cl+(cr-cl)/2;
	if(cl!=cr){
		if(l<=mid)update(l,cl,mid,p*2,d);
		if(l>mid)update(l,mid+1,cr,p*2+1,d);
		tree[p]=min(tree[p*2],tree[p*2+1]);
	}
}
int main(){
	ios::sync_with_stdio(false);
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1,1,n);
    int x,y,d;
	string opt;
    for(int i=0;i<q;i++){
        cin>>opt;
        if(opt[0]=='s'){
            Shift t(opt);
			int a1=a[t.shift[0]];
			for(int i=0;i<t.cnt-1;i++){
				//cout<<t.shift[i]<<' ';
				update(t.shift[i],1,n,1,a[t.shift[i+1]]);
			}
            update(t.shift[t.cnt-1],1,n,1,a1);
        }
        else{
            Que t(opt);
			//cout<<t.l<<' '<<t.r<<endl;
            int ans=numeric_limits<int>::max();
            ask(t.l,t.r,1,n,1,ans);
            cout<<ans<<endl;
        }
    }
	cout.flush();
	return 0;
}
