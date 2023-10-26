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
ll n;
vector<ll> e1[maxn],e2[maxn];
bool v[maxn][maxn];
void dfs1(int now,int fa)
{
	
}
int main()
{
	freopen("climb.in","r",stdin);
	freopen("climb.out","w",stdout);
	scanf("%lld",&n);
	for(int i=1;i<n;i++)
	{
		ll x,y;
		scanf("%lld%lld",&x,&y);
		e1[x].push_back(y);
		e1[y].push_back(x);
	}
	for(int i=1;i<n;i++)
	{
		ll x,y;
		scanf("%lld%lld",&x,&y);
		e2[x].push_back(y);
		e2[y].push_back(x);
	}
	
	return 0;
}
