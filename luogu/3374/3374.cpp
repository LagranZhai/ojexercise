#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+5;
int a[maxn],bit[maxn];
int n,m;
template<typename T>
inline T fr(){
	T w=0,f=1;
	char c=cin.get();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=cin.get();
	}
	while(c>='0'&&c<='9')w=w*10+c-'0',c=cin.get();
	return w*f;
}
inline int lowbit(int x){return x&-x;}
void update(int x,int k){
	while(x<=n){
		bit[x]+=k;
		x+=lowbit(x);
	}
}
int query(int x){
	int ans=0;
	while(x!=0){
		ans+=bit[x];
		x-=lowbit(x);
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		a[i]=fr<int>();
		update(i,a[i]);
	}
	int opt;
	while(m--){
		opt=fr<int>();
		if(opt==1){
			int x=fr<int>(),k=fr<int>();
			update(x,k);
		}
		if(opt==2){
			int x=fr<int>(),y=fr<int>();
			cout<<query(y)-query(x-1)<<"\n";
		}
	}
	return 0;
}
