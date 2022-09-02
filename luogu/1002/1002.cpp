#include<iostream>
using namespace std;
long long dp[23][23];
int main(){
	ios::sync_with_stdio(false);
	int m,n,a,b,x[9],y[9];
	cin>>m>>n>>a>>b;
	x[0]=a;
	y[0]=b;
	x[1]=a+2;
	y[1]=b+1;
	x[2]=a+1;
	y[2]=b+2;
	x[3]=a-1,y[3]=b+2;
	x[4]=a-2,y[4]=b+1;
	x[5]=a-2,y[5]=b-1;
	x[6]=a-1,y[6]=b-2;
	x[7]=a+1,y[7]=b-2;
	x[8]=a+2,y[8]=b-1;
	dp[0][0]=1;
	for(int i=0;i<=m;i++){
		for(int j=0;j<=n;j++){
			int fflag=0;
			for(int l=0;l<9;l++){
				if(i==x[l]&&j==y[l]){
					fflag=1;
				}
			}
			if(fflag)continue;
			if(i-1>=0){
				bool flag=1;
				for(int l=0;l<9;l++){
					if(i-1==x[l]&&j==y[l]){
						flag=0;
					}
				}
				if(flag){
					dp[i][j]+=dp[i-1][j];
				}								
			}
			if(j-1>=0){
				bool flag=1;
				for(int l=0;l<9;l++){
					if(i==x[l]&&j-1==y[l]){
						flag=0;
					}
				}
				if(flag){
					dp[i][j]+=dp[i][j-1];
				}								
			}
		}
	}
	
	cout<<dp[m][n];
	
	return 0;
}
