#include<cstdio>

long long n,ans,x;
long long fastp(long long i){
	long long k;
	if(i==0)k=1;
	else{
		x=fastp(i/2);
		k=(x*x)%1000000007;
		if(i%2)k=(k*3)%10000000007;
	}
	return k;
}

int main(){
	freopen("magic.in","r",stdin);
	freopen("magic.out","w",stdout);
	scanf("%lld",&n);
	ans=fastp(n+1);
	ans-=1;
	if(ans%2==0)printf("%lld",ans/2);
	else printf("%lld",(ans+1000000007)/2);
	return 0;
}
