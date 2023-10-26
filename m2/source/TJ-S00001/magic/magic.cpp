#include<bits/stdc++.h>
using namespace std;
const int MOD=1e9;
long long n,s=1;
int main()
{
	freopen("magic.in","r",stdin);
	freopen("magic.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n+1;i++)
	{
		s*=3;
	}
	cout<<((s-1)/2)%(MOD+7);
}
