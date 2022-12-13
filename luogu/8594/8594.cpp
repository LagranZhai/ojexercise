#include<bits/stdc++.h>
using namespace std;
const int maxn=2e7;
const int p=998244353;
int n,k;
//int dp[1010][1010];
template<typename T>
T fr(){
	T w=0,f=1;
	char c=cin.get();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=cin.get();
	}
	while(c>='0'&&c<='9')w=w*10+c-'0',c=cin.get();
	return w*f;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>k;
	if(k==2*n){
		cout<<1<<endl;		
	}
	else if(k==3){
		cout<<n*2ll%p<<endl;
	}
	else if(k==2){
		cout<<1<<endl;
	}
//	else{
//		dp[1][1]=1;dp[1][2]=1;
//		for(int i=2;i<=n;i++){
//			for(int j=2;j<=2*n;j++){
//				for(int k=1;k<=i;k++){
//					
//				}
//			}
//		}
//	}
	return 0;
}
