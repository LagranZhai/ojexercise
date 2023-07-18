#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<vector>
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
constexpr int maxm=2e4,maxs=100,maxn=100;
int s,n,m;
int dp[maxn+10][maxm+100];
std::vector<int > w[maxn+10];
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>s>>n>>m;
{
    int t;
    for(int i{1};i<=s;i++){
        for(int j{1};j<=n;j++){
            cin>>t;
            w[j].push_back(t*2+1);
        }
    }
}
    for(int i{1};i<=n;i++){
        std::sort(std::begin(w[i]),std::end(w[i]));
        for(int j{0};j<=m;j++){
            dp[i][j]=max(dp[i][j],dp[i-1][j]);
            for(int k{0};k<w[i].size();k++){
                if(j<w[i][k])break;
                dp[i][j]=max(dp[i][j],dp[i-1][j-w[i][k]]+(k+1)*i);
            }
        }
    }
    int ans=0;
    for(int i{0};i<=m;i++){
        ans=max(ans,dp[n][i]);
    }
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}
