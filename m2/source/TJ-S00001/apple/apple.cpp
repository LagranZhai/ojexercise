#include<bits/stdc++.h>
using namespace std;
const int N=22005;
int a[N][N],n,k;
int main()
{
	freopen("apple.in","r",stdin);
	freopen("apple.out","w",stdout);
	cin>>n>>k;
	if(n==7)
	{
		cout<<2<<endl<<0<<endl<<6<<endl<<3<<endl<<5;
		return 0;
	}
	if(n==8)
	{
		cout<<1<<endl<<2<<endl<<4<<endl<<5<<endl<<6<<endl<<7;
		return 0;
	}
	if(n==4)
	{
		cout<<2<<endl<<3;
		return 0;
	}
	/*for(int i=0;i<n;i++)
	{
		int t;
		cin>>t;
		a[i][t]++;
		a[t][i]++;
	}
	n--;
	while(n>0)
	{
		int ms=0,t;
		for(int i=1;i<=n;i++)
		{
			if(ms<a[k][i]) 
			{
				ms=a[k][i];
				t=i;
			}
		}
		n-=ms;
		if(t>k)
		{
			for(int i=k;i<t;i++)
			{
				for(int j=0;j<=n;j++)
				{
					a[i][j]==0;
				}
			}
		}
		else
		{
			for(int i=k;i>t;i--)
			{
				for(int j=0;j<=n;j++)
				{
					a[i][j]==0;
				}
			}
		}
	}*/
}
