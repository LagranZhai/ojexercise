#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int maxn=5e6;
ll a[maxn+10],ka[maxn+10];
ll n,k,p;
ll qpow(ll a,ll b){
    ll res=1;
    a%=p;
    while(b){
        if(b&1)res=res*a%p;
        a=a*a%p;
        b>>=1;
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>p>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    ka[0]=1;
    for(int i=1;i<=n;i++){
        ka[i]=ka[i-1]*k%p;
    }
    ll fz=0,fm=1;
    for(int i=1;i<=n;i++){
        fz=((fz*a[i])%p+(ka[i]*fm)%p)%p;
        fm=fm*a[i]%p;
    }
    cout<<fz*qpow(fm,p-2)%p<<endl;
    return 0;
}