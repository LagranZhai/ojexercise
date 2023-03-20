#include<iostream>
#include<vector>
#include<ctime>
#include<algorithm>
using namespace std;
const int maxn=8e3;
int a[maxn+100],n,dp[maxn+100];
//bool mi(int n,int m,vector<int> &a){
//	if(n==1){
//		a.push_back(m);
//		int c=0,mmin=1e9;
//		for(int i=0;i<a.size();i++){
//			c^=a[i];
//			mmin=min(mmin,a[i]);
//		}
//		if(c<mmin)return 1;
//		a.pop_back();
//		return 0;
//	}
//	for(int i=1;i<m;i++){
//		a.push_back(i);
//		if(mi(n-1,m-i,a)){
//			return 1;
//		}
//		else{
//			a.pop_back();
//		}
//	}
//	return 0;
//}
void odd1(int n,int m){
	for(int i=1;i<=n-2;i++){
		cout<<1<<' ';
	}
	m-=(n-2);
	cout<<m/2<<' '<<m/2<<' ';
	cout<<'\n';
}
void odd2(int n,int m){
	for(int i=1;i<=n-2;i++){
		cout<<2<<' ';
	}
	m-=(n-2)*2;
	cout<<m/2<<' '<<m/2<<' ';
	cout<<'\n';
}
int main(){
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	int n,m;
	srand(time(0));
	while(t--){
		cin>>n>>m;
		if(n==1){
			cout<<"NO"<<'\n';
		}
		else if(n>m){
			cout<<"NO"<<'\n';
		}
		else if(n==2){	
			int flag=0;int i=1;
			for(;i<m;i++){
				if((i^(m-i))<min(i,m-i)){
					flag=1;
					break;
				}
			}
			if(flag){
				cout<<"YES\n";
				cout<<i<<' '<<m-i<<'\n';
			}
			else{
				cout<<"NO\n";
			}
		}
		else if(n==3){		
			for(int i=1;i<=m-2;i++){
				for(int j=i;j<=(m-i)/2;j++){
					int mmin=min(i,min(j,m-i-j));
					if((i^j^(m-i-j))<mmin){
						cout<<"YES\n";
						cout<<i<<' '<<j<<' '<<m-i-j<<'\n';
						goto xx;		
					}
				}
			}
			cout<<"NO\n";
			xx:;
		}
		else if((n%2==0)&&(m%2==0)){
			cout<<"YES\n";
			odd1(n,m);
		}
		else if((n%2==1)&&(m%2==0)){
			if(m-6<n-3)cout<<"NO\n";
			else{
				cout<<"YES\n";
				cout<<1<<' '<<2<<' '<<3<<' ';
				odd1(n-3,m-6);
			}
		}
		else if((n%2==0)&&(m%2==1)){
			if(m-5<2*(n-2))cout<<"NO\n";
			else{
				cout<<"YES\n";
				cout<<2<<' '<<3<<' ';			
				odd2(n-2,m-5);
			}
		}
		else if((n%2==1)&&(m%2==1)){
			if(m-13<2*(n-3))cout<<"NO\n";
			else{
				cout<<"YES\n";
				cout<<3<<' '<<4<<' '<<6<<' ';
				odd2(n-3,m-13);
			}
		}
	}
	return 0;
}
