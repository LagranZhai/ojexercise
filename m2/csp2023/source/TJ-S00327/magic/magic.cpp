#include<bits/stdc++.h>
using namespace std;
#define int long long
const int P=1e9+7;
int mpow(int a,int b)
{
	if(b==1)return a;
	int tmp=mpow(a,b>>1);
	if(b&1)return tmp*tmp%P*a;
	else return tmp*tmp%P;
}
signed main()
{
	freopen("magic.in","r",stdin);
	freopen("magic.out","w",stdout);
	int n;
	cin>>n;
	cout<<(mpow(3,n+1)+P-1)%P*mpow(2,P-2)%P;
	return 0;
}
