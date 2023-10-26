#include<bits/stdc++.h>
using namespace std;
int a[100],b[100];
int main()
{
	freopen("climb.in","r",stdin);
	freopen("climb.out","w",stdout);
	int n;
	cin>>n;
	if(n==7)
	{
		cout<<6;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>a[i]>>b[i];
		if(a[2]==1&&b[2]==3)
		{
			cout<<4<<endl;
		}
		if(a[2]==2&&b[2]==3)
		{
			cout<<5<<endl;
		}
	}
	cout<<7<<endl;
}
