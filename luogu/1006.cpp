#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
using std::cin,std::ios,std::max,std::min;
constexpr int maxn=52;
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
int m,n,a[maxn][maxn],dp[maxn][maxn][maxn];
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>m>>n;
    int x,y,t;
    for(int i{1};i<=m;i++){
        for(int j{1};j<=n;j++){
            cin>>a[i][j];
        }
    }
    for(int i{1};i<=m;i++){
        for(int j{1};j<=n;j++){
            for(int k{1};k<=m;k++){
                if(i+j-k>n||i+j-k<1)continue;
                if(k!=i){
                    dp[i][j][k]=max(dp[i][j][k],max(max(max(dp[i-1][j][k],dp[i-1][j][k-1]),dp[i][j-1][k]),dp[i][j-1][k-1])+a[i][j]+a[k][i+j-k]);
                }
                else dp[i][j][k]=max(dp[i][j][k],max(max(max(dp[i-1][j][k],dp[i-1][j][k-1]),dp[i][j-1][k]),dp[i][j-1][k-1])+a[i][j]);
            }
        }
    }
    cout<<dp[m][n][m]<<"\n";
    return 0;
}
