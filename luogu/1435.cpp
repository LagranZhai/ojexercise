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
//Myos<std::ostream&> t{std::cout};
//Myos<std::ostringstream> t{std::ostringstream()};
const auto& cout = Myos<std::ostringstream>(std::ostringstream()).mys;
constexpr int maxn=1000;
std::string t;
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>t;

    return 0;
}
