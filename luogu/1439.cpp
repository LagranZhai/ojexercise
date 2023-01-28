#include<iostream>
using namespace std;
int a[100003],b[100003],dp[100003];
int main(){
	ios::sync_with_stdio(false);
	int n=0;
	cin>>n;
//	int **dp=new int*[n];
//	for(int i=0;i<n;i++){
//		dp[i]= new int[n]{};
//	}
	int tmpa,tmpb;
	for(int i=1;i<=n;i++){
		//int tmp;
		cin>>tmpa;
		a[tmpa]=i;
	}
	for(int i=0;i<n;i++){
		cin>>tmpb;
		b[i]=a[tmpb];
	}
	int cnt=0;
	dp[0]=-342;
	for(int i=0;i<n;i++){
		for(int j=cnt;j>=0;j--){
			if(dp[j]<b[i]){
				dp[j+1]=b[i];
				if(j+1>cnt)cnt++;
				break;
			}
		}
	}
	cout<<cnt;
////	for(int i=0;i<n;i++){
////		if(a[0][i]==a[1][0])dp[i][0]=1;
////		if(a[1][i]==a[0][0])dp[0][i]=1;
////	}
//	if(a[1][0]==a[0][0])dp[0]=1;
//	
//	for(int i=0;i<n;i++){
//		for(int j=1;j<n;j++){
//			dp[j]=max(dp[j],dp[j-1])+(a[0][i]==a[1][j]);			
//		}
//	}
//	cout<<dp[n-1];
	
//	for(int i=0;i<n;i++){
//		delete[] dp[i];
//	}
	return 0;
}
