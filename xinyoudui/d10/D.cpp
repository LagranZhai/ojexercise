//PD
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=5000;
int n,m;
int g[maxn][maxn];
int fac[maxn],inv[maxn],f[maxn],c[maxn][maxn];
int qpow(int a,int b,int p){
    int c{1};
    while(b>0){
        if(b&1)c=c*a%p;
        a=a*a%p;
        b>>=1;
    }
    return c;
}
int chose(int a,int b){
    return fac[a]*inv[b]%m*inv[a-b]%m;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    g[0][0]=1;
    for(int i{0};i<=n;i++){
        g[i][0]=1;c[i][0]=1;
        for(int j{1};j<=i;j++){
            g[i][j]=(g[i-1][j-1]+(j+1)*g[i-1][j]%m)%m;
            c[i][j]=(c[i-1][j-1]+c[i-1][j])%m;
        }
    }
    fac[0]=fac[1]=1;
    for(int i{2};i<=maxn-1;i++){
        fac[i]=fac[i-1]*i%m;
    }
    inv[maxn-1]=qpow(fac[maxn-1],m-2,m);
    for(int i{maxn-1-1};i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%m;
    }
    // for(int i{0};i<=n;i++){
        
    // }
    int ans{0};
    for(int i{0};i<=n;i++){
        int tmp{qpow(2,n-i,m)};
        int base{1};
        int f{0};
        for(int j{0};j<=i;j++){
            f=(f+g[i][j]*base%m)%m;
            base=base*tmp%m;
        }
        f=f*qpow(2,qpow(2,n-i,m-1),m)%m;
        ans=(ans+(((i%2)?m-chose(n,i):chose(n,i)))*f%m)%m;
    }
    cout<<ans%m<<"\n";
    cout.flush();
    return 0;
}