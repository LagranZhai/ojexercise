#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
using std::cin,std::ios,std::max,std::min;
template<class T>
struct Myos{
    T mys;
    Myos(T&& _s)noexcept:mys(
            std::forward<T>(_s)
            ){}
    ~Myos()noexcept{
        std::cout<<std::flush;
    };
};
template<>
Myos<std::ostringstream>::~Myos()noexcept{
    std::cout<<mys.str()<<std::flush;
}
auto&& cout = Myos<std::ostringstream>(std::ostringstream()).mys;
//auto&& cout = Myos<std::ostream&>(std::cout).mys;
constexpr int maxn=12;

int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    
    return 0;
}
