#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<limits>
using std::cin,std::ios,std::max,std::min;
constexpr int maxn=100;
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
Myos<std::ostringstream> t{std::ostringstream()};
auto& cout = t.mys;
int a[maxn+10],dp1[maxn+10],minoflen[maxn+10],dp2[maxn+10];
int n;
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n;
    for(int i{1};i<=n;i++){
        cin>>a[i];
    }
    std::fill(std::begin(minoflen),std::end(minoflen),std::numeric_limits<int >::max());
    minoflen[0]=0;
    for(int i{1};i<=n;i++){
        int *lower=std::lower_bound(std::begin(minoflen),std::end(minoflen),a[i]);
        dp1[i]=lower-std::begin(minoflen)+((*lower==a[i])?0:1);
        minoflen[dp1[i]]=min(minoflen[dp1[i]],a[i]);
    }
    std::fill(std::begin(minoflen),std::end(minoflen),std::numeric_limits<int >::lowest());
    minoflen[0]=std::numeric_limits<int >::max();
    for(int i{n};i>=1;i--){
        int *lower=std::lower_bound(std::begin(minoflen),std::end(minoflen),a[i],[](int a,int b)->bool{return a>b;});
        dp2[i]=lower-std::begin(minoflen)+((*lower==a[i])?0:1);
        minoflen[dp2[i]]=min(minoflen[dp2[i]],a[i]);
    }
    cout<<
    return 0;
}
