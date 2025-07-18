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
constexpr int maxn=3e6;
#define int long long
int n,p;
int inv[maxn+10];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>p;
    inv[1]=1;
    cout<<inv[1]<<"\n";
    for(int i{2};i<=n;i++){
        inv[i]=p-p/i*inv[p%i]%p;
        cout<<inv[i]<<"\n";
    }
    cout.flush();
    return 0;
}
