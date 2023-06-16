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
        //int *lower=std::lower_bound(std::begin(minoflen),std::end(minoflen),a[i]);
        dp1[i]=std::lower_bound(std::begin(minoflen),std::end(minoflen),a[i])-std::begin(minoflen);
        minoflen[dp1[i]]=min(minoflen[dp1[i]],a[i]);
    }
    std::fill(std::begin(minoflen),std::end(minoflen),std::numeric_limits<int >::max());
    minoflen[0]=0;
    //cout<<minoflen[1]<<std::endl;
    for(int i{n};i>=1;i--){
        //int *lower=std::lower_bound(std::begin(minoflen),std::end(minoflen),a[i]);
        dp2[i]=std::lower_bound(std::begin(minoflen),std::end(minoflen),a[i])-std::begin(minoflen);
        minoflen[dp2[i]]=min(minoflen[dp2[i]],a[i]);
    }
    int mmax=0;
    for(int i{1};i<=n;i++){
        mmax=max(mmax,dp1[i]+dp2[i]-1);
    }
    cout<<n-mmax<<"\n";
    return 0;
}