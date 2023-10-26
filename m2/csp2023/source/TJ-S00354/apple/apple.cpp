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
const ll maxn=50010,p=1000000007;
ll n,k,cnt,f[maxn],fe[maxn],ms[maxn],ap[maxn];
vector<int> e[maxn];
void dfs1(int now,int fa)
{
	f[now]=ap[now];
	fe[now]=now;
	ms[now]=-1;
	for(int i=0;i<e[now].size();i++)
	{
		int x=e[now][i];
		if(x!=fa)
		{
			dfs1(x,now);
			if(f[x]+ap[now]>f[now])
			{
				f[now]=f[x]+ap[now];
				fe[now]=fe[x];
				ms[now]=i;
			}
			else if(f[x]+ap[now]==f[now]&&f[now]!=0&&fe[x]<fe[now])
			{
				fe[now]=fe[x];
				ms[now]=i;
			}
		}
	}
	return;
}
void dfs2(int now,int fa)
{
	if(ap[now]==1) cnt++;
	ap[now]=0;
	if(ms[now]<0)
	{
		k=now;
		return;
	}
	int x=e[now][ms[now]];
	dfs2(x,now);
}
int main()
{
	freopen("apple.in","r",stdin);
	freopen("apple.out","w",stdout);
	scanf("%lld%lld",&n,&k);
	k++;
	for(int i=1;i<n;i++)
	{
		ll x;
		scanf("%lld",&x);
		e[x+1].push_back(i+1);
		e[i+1].push_back(x+1);
	}
	for(int i=1;i<=n;i++) ap[i]=1;
	while(cnt<n)
	{
		printf("%lld\n",k-1);
		dfs1(k,0);
		dfs2(k,0);
	}
	printf("%lld\n",k-1);
	return 0;
}
