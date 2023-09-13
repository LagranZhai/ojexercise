#include<iostream>
#include<algorithm>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e6;
int n,m;
int fac[maxn+100],inv[maxn+100];
int qpow(int a,int b){
    // std::cerr<<a;
    int c=1;
    while(b>0){
        // std::cerr<<b;
        if(b&1)c=1ll*c*a%m;
        b>>=1;
        a=1ll*a*a%m;
    }
    return c;
}
void init(int p){
    fac[0]=1;
    for(int i{1};i<p;i++){
        fac[i]=(1ll*fac[i-1]*i)%p;
    }
    inv[p-1]=qpow(fac[p-1],p-2);
    for(int i{p-2};i>=0;i--){
        inv[i]=1ll*inv[i+1]*(i+1)%p;
    }
}
int c(int n,int m,int p){
    if(m>n)return 0;
    return 1ll*fac[n]*inv[n-m]%p*1ll*inv[m]%p;
}
int lucas(int n,int m,int p){
    if(!m)return 1;
    return 1ll*c(n%p,m%p,p)*lucas(n/p,m/p,p)%p;
}
int dp[maxn+100];
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    init(m);
    dp[1]=1;
    dp[0]=1;
    for(int i{2};i<=n;i++){
        // std::cerr<<i<<"\n";
        int l=(1<<(std::__lg(i)))-1;
        dp[i]=1ll*lucas(i-1,l,m)*dp[l]%m*1ll*dp[i-1-l]%m;
    }
    cout<<dp[n]<<"\n";
    return 0;
}
