#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<deque>
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
constexpr int maxn=2000;
int T,maxp,W,ap[maxn*2],as[maxn*2],bp[maxn*2],bs[maxn*2],dp[maxn+100][maxn+100];

int main() {
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>T>>maxp>>W;
    for(int i{1};i<=T;i++){
        cin>>ap[i]>>as[i]>>bp[i]>>bs[i];
    }
    for(int i{1};i<=T;i++){
        for(int j{1};j<=as[i];j++){
            dp[i][j]=-ap[i]*j;
        }
        for(int j{1};i<=maxP;j++){
            dp[i][j]=max(dp[i][j],dp[i-1][j]);
        }
        for()
    }
    cout.flush();
    return 0;
}
