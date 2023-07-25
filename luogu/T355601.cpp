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
constexpr int maxn=2e3;
#define int long long
int n,p;
int a[maxn+10];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>p;
    int ans=1;
    for(int i{1};i<=n;i++)cin>>a[i];
    for(int i{1};i<=n-1;i++){
        ans=ans*2;
        ans%=p;
    }
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}
