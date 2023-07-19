#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<limits>
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
constexpr int maxn=50;
int n,dp[maxn+10][maxn+10];
std::string s;
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>s;
    n=s.size();
    std::fill(dp[0],dp[0]+(maxn+10)*(maxn+10),std::numeric_limits<int >::max());
    for(int i{0};i<n;i++){
        dp[i][i]=1;
    }
    for(int l{2};l<=n;l++){
        for(int i{0};i+l-1<n;i++){
            int j=i+l-1;
            if(s[i]==s[j]){
                dp[i][j]=min(dp[i][j-1],dp[i+1][j]);
                continue;
            }
            for(int k{i};k<j;k++){
                dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
            }
        }
    }
    cout<<dp[0][s.size()-1]<<"\n";
    cout.flush();
    return 0;
}
