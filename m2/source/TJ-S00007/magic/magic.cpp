#include<bits/stdc++.h>
using namespace std;
long long b= (1e9+7);
int main()
{
	freopen("magic.in","r",stdin);
	freopen("magic.out","w",stdout);
	long long int N,a=1,sum=1,i=2;
	cin>>N;
	do{
		sum=(sum+3*a%b)%b;
		a=3*a%b;
		i++;
	}while(i<=N+1);
	cout<<sum<<endl;
	return 0;
}
