     #include<iostream>
#include<cstdio>
using namespace std;
const long long p=998442353;
long long n,ttt,tt;
int main()
{
freopen("turing.in","r",stdin);
freopen("turing.out","w",stdout);
	cin>>n>>ttt>>tt;
		long long x,y,z;
		cin>>x>>y>>z;
       long long a,b,c;
		cin>>a>>b>>c;
if(y!=a) cout<<"0";
else
{
  cout<<x<<" "<<b<<" "<<z*c%p;
}
}
