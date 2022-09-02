#include<iostream>
#include<string>
using namespace std;
int dp[2003][2003];
int main(){
	ios::sync_with_stdio(false);
	string a,b;
	cin>>a>>b;
	int al=a.size();
	int bl=b.size();
	if(a[0]!=b[0])dp[0][0]=1;
	for(int i=1;i<al;i++){
		if(a[i]!=b[0]){
			dp[i][0]=dp[i-1][0]+1;
		}
		else{
			dp[i][0]=dp[i-1][0];
		}
	}
	for(int j=1;j<bl;j++){
		if(b[j]!=a[0]){
			dp[0][j]=dp[0][j-1]+1;
		}
		else{
			dp[0][j]=dp[0][j-1];
		}
	}
	for(int i=1;i<al;i++){
		for(int j=1;j<bl;j++){
			if(a[i]==b[j]){
				dp[i][j]=dp[i-1][j-1];
			}
			else{
				dp[i][j]=min(min(dp[i-1][j],dp[i][j-1]),dp[i-1][j-1])+1;
			}	
		}
	}
	cout<<dp[al-1][bl-1];

	return 0;
}
