#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<ranges>
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
constexpr int maxn=2e5;
int a[maxn+100],sum[maxn+100];
int n,m,s;
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>m>>s;
{
    for(int t{1};t<=n;t++) {
        int i,v;
        cin>>i>>v;
        a[i]=v;
    };
}
    
    cout.flush();
    return 0;
}
