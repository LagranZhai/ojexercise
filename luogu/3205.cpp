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
constexpr int maxn=1e3,p=19650827;
int dp[maxn+10][maxn+10][2];
int n,h[maxn+10];
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n;
    for(int i{1};i<=n;i++)cin>>h[i];
    for(int i{1};i<=n;i++)dp[i][i][0]=1;
    for(int l{2};l<=n;l++){
        for(int i{1};i+l-1<=n;i++){
            if(h[i]<h[i+1])dp[i][i+l-1][0]+=dp[i+1][i+l-1][0];
            if(h[i]<h[i+l-1])dp[i][i+l-1][0]+=dp[i+1][i+l-1][1];
            dp[i][i+l-1][0]%=p;
            if(h[i+l-1]>h[i])dp[i][i+l-1][1]+=dp[i][i+l-2][0];
            if(h[i+l-1]>h[i+l-2])dp[i][i+l-1][1]+=dp[i][i+l-2][1];
            dp[i][i+l-1][1]%=p;
        }
    }
    cout<<(dp[1][n][0]+dp[1][n][1])%p<<"\n";
    cout.flush();
    return 0;
}
