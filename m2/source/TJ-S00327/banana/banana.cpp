#include<bits/stdc++.h>
using namespace std;
#define N 1003
#define K 10004
#define int long long
const int P=1e9+7;
int a[N],f[N][K];
signed main()
{
	freopen("banana.in","r",stdin);
	freopen("banana.out","w",stdout);
	ios::sync_with_stdio(0);
	int yqsz;
	cin>>yqsz;
	while(yqsz--)
	{
		memset(f,0,sizeof f);
		int n,k;
		cin>>n>>k;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++)
		{
			f[i][a[i]]=1;
			for(int j=a[i];j<=k;j+=a[i])
				f[i][j]+=(f[i-1][j/a[i]]+f[i-1][j])%P,f[i][j]%=P;
		}
		cout<<f[n][k]<<'\n';
	}
	return 0;
}
