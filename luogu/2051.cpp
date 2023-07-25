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
#define int long long
constexpr int maxn=100,p=9999973;
int dp[maxn+10][maxn+10][maxn+10];
int n,m;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>m;
    dp[0][0][0]=1;
    for(int i{1};i<=m;i++){
        for(int j{0};j<=n;j++){
            for(int k{0};k<=n;k++){
                int l=n-j-k;
                if(l<0)continue;
                dp[i][j][k]+=dp[i-1][j][k];dp[i][j][k]%=p;
                if(j>0)dp[i][j][k]+=dp[i-1][j-1][k]*(l+1);dp[i][j][k]%=p;
                if(k>0)dp[i][j][k]+=dp[i-1][j+1][k-1]*(j+1);dp[i][j][k]%=p;
                if(j>0&&k>0)dp[i][j][k]+=dp[i-1][j][k-1]*(l+1)*j;dp[i][j][k]%=p;
                if(k>1)dp[i][j][k]+=dp[i-1][j+2][k-2]*(j+2)*(j+1)/2;dp[i][j][k]%=p;
                if(j>1)dp[i][j][k]+=dp[i-1][j-2][k]*(l+2)*(l+1)/2;dp[i][j][k]%=p;
            }
        }
    }
    int ans=0;
    for(int j{0};j<=n;j++){
        for(int k{0};k<=n;k++){
            int l=n-j-k;
            if(l<0)continue;
            ans+=dp[m][j][k];ans%=p;
        }
    }
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}
