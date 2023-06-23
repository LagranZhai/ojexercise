#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
using std::cin,std::ios,std::max,std::min;
int fpfp(int (*fp_)()){std::cout<<fp_();return fp_();}
template<typename T>
struct Myos{
    T mys;
    Myos(T&& _s)noexcept:mys(
            std::forward<T>(_s)
            ){}
    template<typename Traits>
    Myos<T>& operator<<(Traits&& value)noexcept {
        //mys<<std::forward<Traits>(value);
        value(mys);
        return *this;
    }
    //template<typename Traits,typename CharT>
    //Myos<T>& operator<<(std::basic_ostream<CharT, Traits>& (*func)
        //(std::basic_ostream<CharT, Traits>&) ){
        //mys<<func;
        //return *this;
    //}
    ~Myos()noexcept{
        mys<<"a"<<std::flush;
    };
};
//template<typename T,typename Traits> 
//Myos<T,Traits>& Myos<T,Traits>::operator<<(Traits&& value)noexcept {
        //mys<<std::forward<Traits>(value);
        //this->mys<<value;
        //return *this;
//}
template<> Myos<std::ostringstream>::~Myos()noexcept{
    std::cout<<mys.str()<<std::flush;
}
Myos<std::ostream&> cout{std::cout};
//Myos<std::ostringstream> cout{std::ostringstream()};

constexpr int maxn=12;
int fp(){
    return 1;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie();

    cout<<std::flush;
    return 0;
}
