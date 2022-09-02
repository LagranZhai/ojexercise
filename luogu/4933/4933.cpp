#include<iostream>
#include<set>
//#include<string.h>
using namespace std;
int dp[1003][40010],a[1003],m[40010];
//int tdb[40010][1003];
//set< int > d[1003];
int main(){
	ios::sync_with_stdio(false);
	int n=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int td=0;
//	for(int i=1;i<1002;i++){
//		for(int j=1;j<40004;j++){
//			dp[i][j]=1;
//		}
//	}
	for(int i=1;i<=n;i++){		
		for(int j=1;j<i;j++){
			td=a[i]-a[j]+20001;
			dp[i][td]=dp[i][td]+dp[j][td]+1;
			m[td]=dp[i][td];	
//			dp[i]=(dp[i]+[&]()->int{
//				for(int k=j;k>0;k--){
//					if(tdb[td][k]){
//						tdb[td][j]=tdb[td][k];
//						return tdb[td][j];
//					}
//				}
//				tdb[td][j]=0;
//				return 0;
//			}())%998244353;
			
//			for(int k=1;k<=j;k++){
//				if(d[k].find(td)!=d[k].end()){
//					dp[i]=(dp[i]+1)%998244353;
//				}
//			}
//			int f=1;
//			for(int k=i;k>=j;k--){
//				if(tdb[td][k]){
//					tdb[td][i]=(tdb[td][k]+1)%998244353;
//					f=0;
//				}
//			}
//			if(f){
//				tdb[td][i]=1;
//			} 
		}
	}
	int ans=0;
	for(int i=1;i<40010;i++){
		ans=(ans+(m[i]*(m[i]+1))/2)%998244353;
	}
	cout<<ans;
	
	
	return 0;
}
