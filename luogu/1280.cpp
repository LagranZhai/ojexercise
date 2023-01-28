#include<iostream>
#include<vector>
#include<string>
#include<string.h>
using namespace std;
int dp[10003];
vector< int > s[10003]; 
//vector< int > e[10003];
int main(){
	ios::sync_with_stdio(false);
	int n,k,p,t;
	cin>>n>>k;
	for(int i=0;i<k;i++){	
		cin>>p>>t;
		s[p-1].push_back(p+t-1);
		//e[p+t-1].push_back(p);
	}
	memset(dp,128,sizeof(dp)); 
	dp[0]=0;
	for(int i=0;i<n;i++){
		if(s[i].empty()){
			dp[i+1]=max(dp[i+1],dp[i]+1); 
		}
		else{
			for(auto a:s[i]){
				dp[a]=max(dp[a],dp[i]);
			}
		}		
	}
	cout<<dp[n]<<"\n";
	return 0;
}
