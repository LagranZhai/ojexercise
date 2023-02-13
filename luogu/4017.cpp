#include<iostream>
#include<vector>
using namespace std;
struct animal{
	vector< int > eat;
	vector< int > eaten;
}a[5001];
int dp[5001];
int sum; 
int n,m;
void showshowway(int t){
	if(!a[t].eat.empty()){
		for(int i=0;i<a[t].eat.size();i++){
			if(dp[a[t].eat[i]]==0){
				showshowway(a[t].eat[i]);
				dp[t]=(dp[t]+dp[a[t].eat[i]])%80112002;
			}
			else{
				dp[t]=(dp[t]+dp[a[t].eat[i]])%80112002;
			}
		}
	}
	else{
		dp[t]=1;
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	int er,ee;
	for(int i=0;i<m;i++){
		cin>>ee>>er;
		a[ee].eaten.push_back(er);
		a[er].eat.push_back(ee);
	}
	for(int i=1;i<=n;i++){
		if(dp[i]==0){
			showshowway(i);
		}
		if(a[i].eaten.empty()){
			if(dp[i]){
				sum=(sum+dp[i])%80112002;
			}
			else{
				sum+=1;
			}
		}
	}
	int ans=sum%80112002;
	cout<<ans;
	
	
	return 0;
}
