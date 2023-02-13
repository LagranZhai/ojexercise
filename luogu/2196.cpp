#include<iostream>
#include<cmath>
using namespace std;

int c[22][22],dp[22],a[21],nxt[22];
int n=0,maxA=999999;
void boom(int num){
	nxt[num]=999999;
	int maxN=0;
	int cur=0;
	for(int i=num+1;i<n;i++){
		if(c[num][i]){
			cur=dp[i];
			if(cur>maxN){
				maxN=cur;
				nxt[num]=i;
			}
		}
	}
	dp[num]+=a[num];
	dp[num]+=maxN;
}
//void moob(int num){
//	int maxN=dp[num]-a[num];
//	int cur=0;
//	for(int i=num-1;i>=0;i--){
//		if(c[i][num]){
//			cur=dp[i];
//			maxN=maxN>cur?maxN:cur;
//		}
//	}
//	dp[num]=a[num]+maxN;
//}
int main(){
	ios::sync_with_stdio(false);
	freopen("1.in","r",stdin);
	cin>>n;

	for(int i=0;i<n;i++){
		cin>>a[i];
		//cout<<a[i]<<" ";
	}
	//cout<<"\n";
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			cin>>c[i][j];
		}
	}
//	for(int i=0;i<n;i++){
//		for(int j=0;j<n;j++){
//			cout<<c[i][j]<<" ";
//		}
//			cout<<"\n";
//	}
	int maxmax=0;
	for(int i=n-1;i>=0;i--){
		boom(i);
		//cout<<dp[i]<<" ";
		maxA=maxmax>dp[i]?maxA:i;
		maxmax=dp[maxA];		
	}
//	for(int i=0;i<n;i++){
//		moob(i);
//		maxA=maxA>dp[i]?maxA:dp[i];	
//	}
	int cc=maxA;
	while(cc<=n-1){
		cout<<cc+1<<" ";
		cc=nxt[cc];
	}
	cout<<"\n"<<dp[maxA];
	fclose(stdin);
	return 0;
} 
