#include<iostream>
using namespace std;
#define max(x,y) (x)>(y)?(x):(y)
int r=0,a[1000][1000],dp[1000][1000];
int main(){
	freopen("1.in","r",stdin);
	scanf("%d",&r);
	for(int i=0;i<r;i++){
		for(int j=0;j<=i;j++){
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=0;i<r;i++){
		dp[r-1][i]=a[r-1][i];
	}
	for(int i=r-2;i>=0;i--){
		for(int j=0;j<=i;j++){
			dp[i][j]=(max(dp[i+1][j],dp[i+1][j+1]))+a[i][j];
		}
	}
	cout<<dp[0][0]<<endl;
	fclose(stdin);
	return 0;
}
