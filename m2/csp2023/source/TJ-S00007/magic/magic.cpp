#include<bits/stdc++.h>
using namespace std;
long long int b=1e9+7;
int main()
{
	freopen("magic.in","r",stdin);
	freopen("magic.out","w",stdout);
	long long int N,a=1,sum=1,ans,i=2;
	cin>>N;
	do{
		sum+=3*a;
		a=3*a;
		i++;
	}while(i<=N+1);
	cout<<sum%b<<endl;
	return 0;
}
