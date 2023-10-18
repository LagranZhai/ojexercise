#include<iostream>
#include<algorithm>
using std::cin,std::cout,std::ios;
#define int long long
constexpr int p=1e9+7,maxn=1e3;
int n,m;
int a[maxn+100];
int fac[maxn*3],inv[maxn*3];
int qpow(int a,int b){
    int c=1;
    while(b>0){
        if(b&1)c=c*a%p;
        b>>=1;
        a=a*a%p;
    }
    return c;
}
void init(int n=maxn*3){
    fac[0]=1;
    for(int i{1};i<=n;i++){
        fac[i]=fac[i-1]*i%p;
    }
    inv[n]=qpow(fac[n],p-2);
    for(int i{n-1};i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%p;
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i{1};i<=m;i++){
        cin>>a[i];
    }
    int ans=0;
    init();
    for(int i{0};i<=n;i++){
        int res=1;
        for(int j{1};j<=m;j++){
            res=fac[n-i+a[j]-1]*inv[n-i-1]%p*inv[a[j]]%p*res%p;
        }
        res=fac[n]*inv[n-i]%p*inv[i]%p*res%p;
        if(i%2ll==0){
            ans=(ans+res)%p;
        }
        else{
            ans=(ans-res+p)%p;
        }
    }
    cout<<ans<<"\n";
    return 0;
}