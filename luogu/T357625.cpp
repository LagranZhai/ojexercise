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
constexpr int maxn=5e3,p=998244353;
int fab[maxn];
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        std::fill(dp[0],dp[0]+(maxn+100)*2,0);
        dp[0][0]=1;
        for(int i=1;i<=n;i++){
            dp[i][1]+=dp[i-1][0];dp[i][1]%=p;
            dp[i][0]+=dp[i-1][0]+dp[i-1][1];dp[i][0]%=p;
        }
        cout<<dp[n][0]+dp[n][1]-1<<"\n";
    }
    cout.flush();
    return 0;
}
