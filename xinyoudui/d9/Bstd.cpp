#include <iostream>
using namespace std;
typedef long long ll;
const int maxn=2e5+7;
const ll mod=1000000007;
int inv[maxn],e[107],s[107],fac[maxn];
ll a[107][107];
ll det(int n) {
    ll ans=1;
    int k=0;
    for(int i=0;i<n;i++) {
        for(int j=i+1;j<n;j++) {
            int x=i,y=j;
            while(a[y][i]) {
                ll t=a[x][i]/a[y][i];
                for(int l=i;l<n;l++) a[x][l]=(a[x][l]-a[y][l]*t)%mod;
                swap(x,y);
            }
            if(x!=i) {
                for(int l=0;l<n;l++) swap(a[i][l],a[x][l]);
                k^=1;
            }
        }
        if(a[i][i]==0) return 0;
        else ans=ans*a[i][i]%mod;
    }
    if(k) ans=-ans;
    return (ans+mod)%mod;
}
void init() {
    inv[0]=inv[1]=1;
    fac[0]=fac[1]=1;
    for(int i=2;i<maxn;i++) {
        fac[i]=1ll*fac[i-1]*i%mod,
        inv[i]=1ll*inv[mod%i]*(mod-mod/i)%mod;
    }
    for(int i=2;i<maxn;i++) inv[i]=1ll*inv[i-1]*inv[i]%mod;
}
ll C(ll n,ll m) {
    if(m<0) return 0;
    return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int main( ) {
    // freopen("B.in","r",stdin);
    int t;
    cin>>t;
    init();
    while(t--) {
        int n,k;
        cin>>n>>k;
        for(int i=0;i<k;i++) cin>>s[i];
        for(int i=0;i<k;i++) cin>>e[i];
        for(int i=0;i<k;i++) {
            for(int j=0;j<k;j++) {
                a[i][j]=C(n-1+e[j]-s[i],e[j]-s[i]);
            }
        }
        cout<<det(k)<<endl;
    }
    return 0;
}