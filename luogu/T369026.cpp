#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<vector>
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
using ll=long long;
constexpr int maxn=12;
int n;
std::vector<ll > a;
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n;
    ll maxa=0;
{
    ll t;
    for(int i{1};i<=n;i++){
        cin>>t;
        a.push_back(t);
        maxa=max(maxa,t);
    }
}
    for(int i{0};i<=std::__lg(maxa);i++){
        
    }
    cout.flush();
    return 0;
}
