#include<bits/stdc++.h>
using namespace std;
long long int a[1001];
int main()
{
	freopen("banana.in","r",stdin);
	freopen("banana.out","w",stdout);
	int D;
	long long int n,K,sum,ans,c;
	cin>>D;
	for(int i=1;i<=D;i++)
	{
		ans=0;
		cin>>n>>K;
		for(int j=1;j<=n;j++)
		{
			cin>>a[j];
		}
		for(int h=1;h<=n;++h)
		{
			sum=1;
			c=h;
			while(c<=n)
			{
				sum*=a[c];
				if(sum==K) ans++;
				c++;
			}
		}
		cout<<ans%1000000007<<endl;
	}
	return 0;
}
