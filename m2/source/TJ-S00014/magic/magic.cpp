#include<bits/stdc++.h>
using namespace std;

long long n=1e9+7;


long long p(int x)
{
	if(x==0)
	{
		return 1;
	}
	if(x==1)
	{
		return 3;
	}
	if(x==2)
	{
		return 9;
	}
	long long j=p(x/2)%n;
	if(x&1==1)
	{
		return 3*j*j;
	}
	return (j*j)%n;
}


int main()
{
	freopen("magic.in","r",stdin);
	freopen("magic.out","w",stdout);
	int q;
	cin>>q;
	int m=(int (p(q+1)-1)%n)/2;
	cout<<m;
	return 0;
} 

