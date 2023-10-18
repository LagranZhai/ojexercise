//P3807
#include<iostream>
#include<algorithm>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e5;
int n,m,p;
int fac[maxn+100],inv[maxn+100];
int qpow(int a,int b){
    int c=1;
    while(b>0){
        if(b&1)c=1ll*c*a%p;
        b>>=1;
        a=1ll*a*a%p;
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
int main(){
    ios::sync_with_stdio(false);
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m>>p;
        init(p);
        // for(int i{1};i<p;i++){
        //     cout<<inv[i]<<" ";
        // }
        cout<<lucas(n+m,n,p)<<"\n";
    }
    return 0;
}
