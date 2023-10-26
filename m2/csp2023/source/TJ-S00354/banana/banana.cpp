#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
#include<set>
#include<string>
#include<cstring>
#include<cstdio>
using namespace std;
typedef long long ll;
const ll maxn=10010,p=1000000007;
ll D,n,k,s1,ans,len,a[maxn],f[maxn],g[maxn][2],h[maxn],jc[maxn];
ll gcd(ll X,ll Y)
{
	if(Y==0) return X;
	return gcd(Y,X%Y);
}
ll ksm(ll x,ll y)
{
	if(y==0) return 1;
	if(y==1) return x%p;
	ll z=ksm(x,y/2);
	if(y%2==0) return z*z%p;
	return z*z%p*x%p;
}
ll C(ll n,ll m)
{
	if(m<0||m>n) return 0;
	if(n==m||m==0) return 1;
	return jc[n]*ksm(jc[m],p-2)%p*ksm(jc[n-m],p-2)%p;
}
void dfs(int now,int nk)
{
	if(nk==1)
	{
		ll cnt=1;
		for(int i=1;i<now;i++) cnt=cnt*C(g[i][0],h[i])%p;
		ans=(ans+cnt)%p;
		return;
	}
	if(now>len) return;
	for(int i=0;i<=g[now][0];i++)
	{
		h[now]=i;
		dfs(now+1,nk);
		if(nk%g[now][1]!=0) break;
		nk/=g[now][1];
	}
}
int main()
{
	freopen("banana.in","r",stdin);
	freopen("banana.out","w",stdout);
	scanf("%lld",&D);
	jc[0]=1;
	for(int i=1;i<maxn;i++) jc[i]=jc[i-1]*i%p;
	while(D--)
	{
		scanf("%lld%lld",&n,&k);
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&a[i]);
		}
		sort(a+1,a+n+1);
		len=0;
		s1=0;
		memset(g,0,sizeof(g));
		for(int i=1;i<=n;i++)
		{
			if(i==1||a[i]==1)
			{
				if(a[i]==1) s1++;
				else if(gcd(k,a[i])==a[i])
				{
					len++;
					g[len][1]=a[i];
					g[len][0]=1;
				}
			}
			else if(a[i]!=1&&a[i]!=a[i-1])
			{
				if(gcd(k,a[i])==a[i])
				{
					len++;
					g[len][1]=a[i];
					g[len][0]=1;
				}
			}
			else if(a[i]==a[i-1]&&g[len][1]==a[i]) g[len][0]++;
		}
		ans=0;
		dfs(1,k);
		printf("%lld\n",ans*ksm(2,s1)%p);
	}
	return 0;
}
