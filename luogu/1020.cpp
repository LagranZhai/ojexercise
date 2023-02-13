#include<iostream>
#include<cstring>
using namespace std;
int a[100003],dp[100003];
int main(){
	//ios::sync_with_stdio(false);
	int t=0; 
	while(~scanf("%d",&a[t])){
		++t;
	}
	//cout<<1;
	//memset(dp,128,sizeof(dp)); 
	int tail=0;
	dp[0]=9999999;
	for(int i=0;i<t;i++){
		bool flag=0;
		if(a[i]<=dp[tail]){
			tail++;
			dp[tail]=a[i];
			continue;
		}
		for(int j=tail;j>=1;j--){
			if(a[i]<=dp[j]){
				dp[j+1]=a[i];
				flag=1;
				break;
			}
		}
		if(!flag){
			dp[1]=a[i];	
		}
		
	}
	cout<<tail<<"\n";
	memset(dp,0,sizeof(dp));
	tail=0;
	dp[0]=-9999999;
	for(int i=0;i<t;i++){
		bool flag=0;
		if(a[i]>dp[tail]){
			tail++;
			dp[tail]=a[i];
			continue;
		}
		for(int j=tail;j>=1;j--){
			if(a[i]>dp[j]){
				dp[j+1]=a[i];
				flag=1;
				break;
			}
		}
		if(!flag){
			dp[1]=a[i];	
		}
		
	}
	cout<<tail;
	return 0;
}
