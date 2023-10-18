#include<iostream>
#include<algorithm>
using std::cin,std::cout,std::ios;
#define int long long
constexpr int p=1e9+7,maxn=1e3;
int fac[maxn+100],a[maxn][maxn],inv[maxn];
int qpow(int a,int b){
    int c=1;
    while(b>0){
        if(b&1)c=c*a%p;
        b>>=1ll;
        a=a*a%p;
    }
    return c;
}
void init(){
    fac[0]=1;
    for(int i{1};i<=maxn;i++){
        fac[i]=fac[i-1]*i%p;
    }
    inv[maxn]=qpow(fac[maxn],p-2);
    for(int i{maxn-1};i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%p;
    }
}
int get(int n,int m){
    int ans=0;
    bool f=0;
    for(int i{0};i<=m;i++,f^=1){
        if(f){
            ans-=fac[m]*inv[m-i]%p*inv[i]%p*fac[n-i]%p;
            ans=(ans+p)%p;
        }
        else{
            ans+=fac[m]*inv[m-i]%p*inv[i]%p*fac[n-i]%p;
            ans=ans%p;
        }
    }
    return ans;
}
signed main(){
    ios::sync_with_stdio(false);
    init();
    int T;
    cin>>T;
    int n,m,k;
    for(int i{1};i<=T;i++){
        cin>>n>>m>>k;
        cout<<"Case "<<i<<": "<<fac[m]*inv[m-k]%p*inv[k]%p*get(n-k,m-k)%p<<"\n";
    }
    return 0;
}