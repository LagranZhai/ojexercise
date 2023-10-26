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
const ll p=1000000007;
ll n;
ll ksm(ll x,ll y)
{
	if(y==0) return 1;
	if(y==1) return x%p;
	ll z=ksm(x,y/2);
	if(y%2==0) return z*z%p;
	return z*z%p*x%p;
}
int main()
{
	freopen("magic.in","r",stdin);
	freopen("magic.out","w",stdout);
	cin>>n;
	cout<<(ksm(3,n+1)-1+p)%p*ksm(2,p-2)%p;
	return 0;
}
