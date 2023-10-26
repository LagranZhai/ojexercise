#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=5e5;
#define int long long
constexpr int p=998244353;
int n,k;
int fac[maxn*2],inv[maxn*2];
int qpow(int a,int b){
    int c=1;
    while(b){
        if(b&1)c=c*a%p;
        a=a*a%p;
        b>>=1;
    }
    return c;
}
void init(){
    fac[0]=1;
    for(int i{1};i<maxn*2;i++){
        fac[i]=fac[i-1]*i%p;
    }
    inv[maxn*2-1]=qpow(fac[maxn*2-1],p-2);
    for(int i{maxn*2-2};i>=1;i--){
        inv[i]=inv[i+1]*(i+1)%p;
    }
    inv[0]=1;
}
signed main(){
    ios::sync_with_stdio(false);
    cin>>n>>k;
    init();
    int res1=0;
    for(int i{k};i<=n;i++){
        res1=(res1+fac[i-1]*inv[i-k]%p)%p;
    }
    if(n>=k)res1=res1*fac[n-k]%p*(n-k);
    // cout<<res1<<"\n";
    int res2=0;
    for(int i{k+1};i<=n;i++){
        res2=(res2+fac[i-1]*inv[i-k-1]%p)%p;
    }
    if(n>k)res2=res2*(n-k)%p*fac[n-k-1]%p;
    // cout<<res2<<"\n";
    int res3=0; 
    for(int i{k};i<=n;i++){
        res3=(res3+fac[i-1]*inv[i-k]%p*(n-i)%p)%p;
    }
    if(n>k)res3=res3*(n-k)%p*fac[n-k-1]%p;
    // cout<<res3<<"\n";
    int ans=(((res1+res2)%p-res3+p)%p+fac[n])%p;
    cout<<ans<<std::endl;
    return 0;
}