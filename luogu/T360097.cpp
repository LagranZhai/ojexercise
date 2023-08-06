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
constexpr int maxn=50,p=1e9+7;
#define int long long
int n,k;
int a[maxn*2];
int dp[maxn*2][maxn*maxn*2];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>k;
    int t;
    int sum=0;
    for(int i{1};i<=n;i++){
        cin>>t;
        a[i]=std::__lg(t)+1;
        sum+=a[i];
    }
    if(sum<=k){
        int ans=1;
        for(int i{1};i<=n;i++){
            ans*=(a[i]+1);
            ans%=p;
        }
        cout<<ans-1<<"\n";
    }
    cout.flush();
    return 0;
}
