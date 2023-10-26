#include<cstdio>
#include<vector>
using namespace std;

long long bag[10010],arr[1010];
int n,d,k;
int dp(){
	for(int i=0;i<n;i++){
		for(int j=k/arr[i];j>=1;j--){
			if(bag[j]!=0)bag[j*arr[i]]+=bag[j];
		}
	}
	printf("%lld\n",bag[k]%1000000007);
	return 0;
}

int main(){
	freopen("banana.in","r",stdin);
	freopen("banana.out","w",stdout);
	scanf("%d",&d);
	while(d--){
		scanf("%d%d",&n,&k);
		for(int i=0;i<n;i++)scanf("%lld",arr+i);
		for(int i=0;i<=k;i++)bag[k]=0;
		bag[1]=1;
		dp();
	}
	return 0;
}
