#include <bits/stdc++.h>
using namespace std;
const int maxn=1e4;
const int p=998244353;
int n,a[maxn],n[maxn];
int sum=0;
void solve(){
	if(sum%2==1){
		cout<<0<<endl;
		return;
	}
	if(n==1){
		cout<<0<<endl;
		return;
	}
	if(n==2){
		if(b[1]==b[2]){
			cout<<b[i]<<endl;
			return;
		}
		else{
			cout<<0<<endl;
			return;
		}
	}
	if(sum==n){
		if(n%2==0){
			int ans=1,t=n;
			for(int i=n;i>=1;i--){
				ans=ans*i%p;
				if(i%2==0)ans/=2;
			}
			cout
		}
		
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>b[i];
		sum+=b[i];
	}
	
	return 0;
}
