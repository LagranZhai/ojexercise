#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
using std::cin,std::ios,std::max,std::min;
template<typename T>
struct Myos{
    T mys;
    Myos(T&& _s)noexcept:mys(
        std::forward<T>(_s)
    ) {}
    Myos<T>& flush() {
        mys<<std::flush;
        return *this;
    }
    template<typename Traits>
    Myos<T>& operator<<(Traits&& value)noexcept {
        mys<<std::forward<Traits>(value);
        return *this;
    }
    ~Myos() {
        flush();
    }
};
template<> Myos<std::ostringstream>& Myos<std::ostringstream>::flush() {
        std::cout<<mys.str()<<std::flush;
        mys.str("");
        return *this;
}
//Myos<std::ostream&> cout{std::cout};
Myos<std::ostringstream> cout{std::ostringstream()};
constexpr int maxn=1e6;
#define int long long
int n,M,q;
int fac[maxn+100],f[maxn+100],inv[maxn+100];
int ex_gcd(int a, int b, int& x, int& y) {
  if (b == 0ll) {
    x = 1ll;
    y = 0ll;
    return a;
  }
  int d = ex_gcd(b, a % b, x, y);
  int temp = x;
  x = y;
  y = temp+M - (a / b * y)%M;y%=M;
  return d;
}

int getinv(int i){
    int inverse=0,y=0;
    int d=ex_gcd(f[i],M,inverse,y);
    inverse/=d;
    inverse%=M;
    return inverse;
}
void init(){
    // std::fill(fac,fac+maxn,0);
    // std::fill(f,f+maxn,0);
    // std::fill(inv,inv+maxn,0);
    fac[0]=f[0]=1ll;
    for(int i{1};i<=n;i++){
        fac[i]=fac[i-1]*i;
        fac[i]%=M;
    }
    for(int i{1};i<=n;i++){
        f[i]=f[i-1]*fac[i];
        f[i]%=M;
        // cout<<f[i]<<" ";
    }
    inv[0]=1;
    inv[n]=getinv(n);
    for(int i{n-1};i>=0;i--){
        inv[i]=inv[i+1]*(fac[i+1]);
        inv[i]%=M;
    }
    return ;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie();
    int T;
    cin>>T;
    while(T--){
        cin>>n>>M>>q;
        int r;
        init();
        int an=f[n];
        for(int i{1};i<=q;i++){
            cin>>r;
            int ans=(((an*inv[r])%M)*inv[n-r])%M;
            cout<<ans<<"\n";
        }
    }
    cout.flush();
    return 0;
}
