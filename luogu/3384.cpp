#include<iostream>
#include<sstream>
#include<algorithm>
using std::cin,std::ios;
template<typename T>
struct Myos{
    T mys;
    Myos(T&& s)noexcept:mys(std::forward<T>(s)) {}
    ~Myos()noexcept {
        mys<<std::flush;
    }
};
template<> 
Myos<std::ostringstream>::~Myos()noexcept {
    std::cout<<mys.str()<<std::flush;
};
Myos<std::ostringstream> myos{std::ostringstream()};
//Myos<std::ostream&> myos{std::cout};
auto&& cout=myos.mys;
constexpr int maxn=1e6;
int n,m,r,p;
int dp[maxn+10];
int main(){
    ios::sync_with_stdio(false);
    {
        int opt,x,y,z;
        for(int i{1};i<=m;i++){
            cin>>opt>>x>>y>>z;
        }
    }
    int x,y,z;
    return 0;
}
