#include<iostream>
//#include<algorithm>
using namespace std;

int a[102][102],dp[102][102];
int maxL;
void findway(int m,int n){
	if(dp[m][n]>0)return;
	int cur=a[m][n];
	int e=0,b=0,c=0,d=0;
	//dp[m][n]=-100000;
	if(cur<a[m-1][n]){
		if(dp[m-1][n]>0){
			e=dp[m-1][n];
			//flag=1;
		}
		else if(dp[m-1][n]==0){
			findway(m-1,n);
			e=dp[m-1][n];
			//flag=1;
		}
	}
	if(cur<a[m+1][n]){
		if(dp[m+1][n]>0){
			b=dp[m+1][n];
			//flag=1;
		}
		else if(dp[m+1][n]==0){
			findway(m+1,n);
			b=dp[m+1][n];
			//flag=1;
		}
	}
	if(cur<a[m][n-1]){
		if(dp[m][n-1]>0){
			c=dp[m][n-1];
			//flag=1;
		}
		else if(dp[m][n-1]==0){
			findway(m,n-1);
			c=dp[m][n-1];
			//flag=1;
		}
	}
	if(cur<a[m][n+1]){
		if(dp[m][n+1]>0){
			d=dp[m][n+1];
			//flag=1;
		}
		else if(dp[m][n+1]==0){
			findway(m,n+1);
			d=dp[m][n+1];
			//flag=1;
		}
	}
		dp[m][n]=max(max(e,b),max(c,d))+1;
		return;
}
int main(){
	ios::sync_with_stdio(false);
	int r,c;
	cin>>r>>c;
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			cin>>a[i][j];
		}
	}
	for(int i=0;i<=c+1;i++){
		a[0][i]=0;
		a[r+1][i]=0;
	}
	for(int i=0;i<=r+1;i++){
		a[i][0]=0;
		a[i][c+1]=0;
	}
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			findway(i,j);
			maxL=(maxL>dp[i][j]?maxL:dp[i][j]);
			//cout<<dp[i][j]<<" ";
		}
		//cout<<"\n";
	}
	cout<<maxL;
	return 0;
}
